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

#ifndef OPENAIAPI_API_HELPER_H
#define OPENAIAPI_API_HELPER_H

#include <map> /* std::map */
#include <string> /* std::string */
#include <future> /* std::future */

/* Define when libcurl is build with static library */
#define CURL_STATICLIB
#include <curl/curl.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <OpenAIApi/Response.h>
using namespace OpenAIApi;

/* write callback */
size_t _write_buf(char* ptr, size_t size, size_t nmemb, void* buffer);

class ApiHelper
{

public:

	ApiHelper( std::string apiKey, std::string organizationKey = "" );

	~ApiHelper() = default;

	/* this function doing all magic */
	int request(std::string& url, std::string& type, std::string content_type = "Content-Type: application/json");

	/* add form */
	void addFormParam(std::string key, std::string value);

	/* convert response string to json object */
	json stringToJson(std::string response);

	void setJsonRequest(json jsonRequest);

	//template<class T>
	std::future< Response < json >> getResponse();

protected:

	int m_httpCode;
	bool is_JsonRequest;
	bool is_formRequest; 
	std::string m_orgId;
	std::string m_apiKey;
	std::string m_payload;
	std::string m_responseBody;
	std::map<std::string, std::string> m_formMap;

};

#endif /* !OPENAIAPI_API_HELPER_H */
