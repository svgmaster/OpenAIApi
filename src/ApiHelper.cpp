/**************************************************************************************\
*								         	       
*   MIT License								       
*										       
*   Community-maintained OpenAI API Library for modern C++			       
*										       
*   Copyright (c) 2023 Stanislav Gadzhov					       
*								      		       
*   Permission is hereby granted, free of charge, to any person obtaining a copy   
*	of this software and associated documentation files (the "Software"), to deal  
*	in the Software without restriction, including without limitation the rights   
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      
*	copies of the Software, and to permit persons to whom the Software is	       
*	furnished to do so, subject to the following conditions:		       
*										       
*	The above copyright notice and this permission notice shall be included in all 
*	copies or substantial portions of the Software.				       
*								 		       
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	       
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  
*	SOFTWARE.								       
*										       
\**************************************************************************************/

#include <iostream>

#include <OpenAIApi/Client.h> /* OpenAIException */

#include "ApiHelper.h"

using namespace OpenAIApi;

ApiHelper::ApiHelper( std::string apiKey, std::string organizationKey )
{
	if (apiKey.empty())
		throw OpenAIException(401,"Incorrect API key provided");

	if (!organizationKey.empty())
		m_orgId = organizationKey;

	m_apiKey = apiKey;
	m_formMap = {};
	m_httpCode = 1;
	m_responseBody = {};
}

size_t 
_write_buf(char* ptr, size_t size, size_t nmemb, void* buffer)
{
	std::string* response = reinterpret_cast<std::string*>(buffer);
	response->append(ptr, size * nmemb);
	return size * nmemb;
}

int 
ApiHelper::request(std::string& url,	/* Valid Url Address */
			std::string& type,			/* HTTP Request Type */
			std::string content_type)
{
	CURL* curl = curl_easy_init();

	if (curl) {

		/* Build an HTTP form */
		curl_mime* mime = curl_mime_init(curl);
		curl_mimepart* part = curl_mime_addpart(mime);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, content_type.c_str());
		
		if (!m_apiKey.empty())
			headers = curl_slist_append(headers, ("Authorization: Bearer " + m_apiKey).c_str());

		if (!m_orgId.empty())
			headers = curl_slist_append(headers, ("OpenAI-Organization: " + m_orgId).c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		if (is_formRequest == true) {

			for (auto& val : m_formMap) {	

				part = curl_mime_addpart(mime);
				curl_mime_name(part, val.first.c_str());

				if(val.first != "file" || "image" || "mask")
					curl_mime_data(part, val.second.c_str(), CURL_ZERO_TERMINATED);
				else
					curl_mime_filedata(part, val.second.c_str());

			}

			/* Set the form info */
			curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
		}

		if ((type == "POST" || type == "PUT" || type == "DELETE") 
			&& is_formRequest == false && is_JsonRequest == true) {

			size_t length = m_payload.length();
			const char* payload = m_payload.c_str();

			if(length > 0)
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
			if (payload != 0)
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_buf);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_responseBody);
		
		CURLcode res = curl_easy_perform(curl);

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_httpCode);

		/* Clean-up. */
		curl_easy_cleanup(curl);

		curl_mime_free(mime);

		m_formMap.clear();

		if (res != CURLE_OK) {
			throw OpenAIException(m_httpCode, std::string(curl_easy_strerror(res)));
			
			m_responseBody = "";

			return 	m_httpCode;
		}

		// 1xx - informational : OK
		// 2xx - successful    : OK
		// 3xx - redirection   : OK
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (m_httpCode > 399) {
			std::string message = std::string(curl_easy_strerror(res));

			if (json::accept(m_responseBody)) {
				json j = json::parse(m_responseBody);

				if (j.contains("error")) {
					message = "Error " + std::to_string(m_httpCode) + ": " + std::string(j["error"]["message"]);
				}

			}
				
			throw OpenAIException(m_httpCode, message);
			
			return m_httpCode;
		}

		return m_httpCode;
	}
	return 	1;
}

void 
ApiHelper::addFormParam(std::string key, std::string value)
{
	is_formRequest = true;
	is_JsonRequest = false;
	m_formMap.insert({ key, value });
}

json 
ApiHelper::stringToJson(std::string response)
{
	if (json::accept(response)) {
		return json::parse(response);
	}
	return {};
}

void 
ApiHelper::setJsonRequest(json jsonRequest) 
{
	is_formRequest = false;
	is_JsonRequest = true;

	std::stringstream ss;
	ss << jsonRequest;

	m_payload = ss.str();
}

//template<class T>
std::future<Response<json>> ApiHelper::getResponse()
{
	return std::async(std::launch::async, [=]
	{
		ServerResponse res = { m_responseBody, m_httpCode };
		return Response<json>(json::parse(m_responseBody), res);	
	});
}
