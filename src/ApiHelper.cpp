/**************************************************************************************\
*								         	       *
*   	MIT License								       *
*										       *
*   	Community-maintained OpenAI API Library for modern C++			       *
*										       *
*   	Copyright (c) 2023 Stanislav Gadzhov					       *
*								      		       *
*   	Permission is hereby granted, free of charge, to any person obtaining a copy   *
*	of this software and associated documentation files (the "Software"), to deal  *
*	in the Software without restriction, including without limitation the rights   *
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
*	copies of the Software, and to permit persons to whom the Software is	       *
*	furnished to do so, subject to the following conditions:		       *
*										       *
*	The above copyright notice and this permission notice shall be included in all *
*	copies or substantial portions of the Software.				       *
*								 		       *
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	       *
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
*	SOFTWARE.								       *
*										       *
\**************************************************************************************/

#include <iostream>

#include "ApiHelper.h"

std::map<std::string, std::string> m_formMap = {};
std::string m_responseBody = {};
int m_httpCode = 1;

size_t 
_write_buf(char* ptr, size_t size, size_t nmemb, void* buffer) 
{
	std::string* response = (std::string*)buffer;
	response->append(ptr, size * nmemb);
	return size * nmemb;
}

int 
sendRequest(std::string& url,		/* Valid Url Address */
			std::string& type,		/* HTTP Request Type */
			const char* payload,	/* JSON Payload */
			size_t length,			/* JSON String lenght */
			std::string& api_key,	/* API Key */
			std::string& org_key,   /* Organization Key */
			std::string content_type,
			bool post_form)
{
	CURL* curl = curl_easy_init();

	std::string response;

	if (curl) {
		/* Build an HTTP form */
		curl_mime* mime = curl_mime_init(curl);
		curl_mimepart* part = curl_mime_addpart(mime);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, content_type.c_str());
		
		if (api_key != "")
			headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
		if (org_key != "")
			headers = curl_slist_append(headers, ("OpenAI-Organization: " + org_key).c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		if (post_form == true) {

			for (auto& val : m_formMap) {	
				std::cout << val.first.c_str() << std::endl;
				std::cout << val.second.c_str() << std::endl;

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
			&& post_form == false) {

			if(length > 0)
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
			if (payload != 0)
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_buf);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		
		CURLcode res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			throw std::runtime_error("Error: " + std::string(curl_easy_strerror(res)));
			m_responseBody = "";
			return 	1;
		}

		long response_code;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

		/* Clean-up. */
		curl_easy_cleanup(curl);
		curl_mime_free(mime);
		m_formMap.clear();

		m_responseBody = response;

		return response_code;
	}
	return 	1;
}

void 
addFormParam(std::string key, std::string value)
{
	m_formMap.insert({ key, value });
}

json 
stringToJson(std::string response) 
{
	if (json::accept(response)) {
		json j = json::parse(response);
		if (j.contains("error")) {
			/* if response contains error throw message */
			throw std::runtime_error("Error: " + std::string(j["error"]["message"]));
			return j;
		}
		return j;
	}
	return {};
}
