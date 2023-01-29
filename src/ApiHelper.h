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

#ifndef OPENAIAPI_API_HELPER_H
#define OPENAIAPI_API_HELPER_H 1

#include <map> /* std::map */
#include <string> /* std::string */

/* Define when libcurl is build with static library */
//#define CURL_STATICLIB
#include <curl/curl.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/* write callback */
size_t _write_buf(char* ptr, size_t size, size_t nmemb, void* buffer);

/* this function doing all magic */
int sendRequest(std::string& url, std::string& type, const char* payload, size_t length, 
	std::string& api_key, std::string& org_key, std::string content_type = "Content-Type: application/json",
	bool post_form = false);

/* add form */
void addFormParam(std::string key, std::string value);

/* convert response string to json object */
json stringToJson(std::string response);

extern std::map<std::string, std::string> m_formMap;
extern std::string m_responseBody;
extern int m_httpCode;

#endif /* !OPENAIAPI_API_HELPER_H */
