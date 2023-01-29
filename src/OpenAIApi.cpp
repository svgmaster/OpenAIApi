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

#include <string> /* we use std::strings */
#include <sstream> /* this is need for std::stringstream */

#include <OpenAIApi/Client.h> /* define all functions, and use nlohmann/json */

#include "EndPoints.h" /* getOpenAIUrl */
#include "ApiHelper.h" /* sendRequest, stringToJson */

using namespace OpenAIApi;

json
Client::cancelFineTune(std::string fineTuneId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::CancelFineTune, fineTuneId);

	std::string payload = "";
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createCompletion(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Completions);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createEdit(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Edit);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createEmbedding(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Embeddings);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createFile(std::string file, std::string purpose)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::UploadFiles);

	addFormParam("file", file);
	addFormParam("purpose", purpose);

	std::string payload = "";
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey, "Content-Type : application/x-www-form-urlencoded", true);

	return stringToJson(m_responseBody);
}

json
Client::createFineTune(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::FineTunes);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createImage(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesGenerations);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::createImageEdit(std::string image, std::string prompt, std::string mask, int n,
	std::string size, std::string responseFormat, std::string user)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesEdits);

	addFormParam("image", image);
	addFormParam("mask", mask);
	addFormParam("prompt", prompt);
	addFormParam("n", std::to_string(n));
	addFormParam("size", size);
	addFormParam("response_format", responseFormat);
	addFormParam("user", user);

	std::string payload = "";
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey, "Content-Type: application/x-www-form-urlencoded", true);

	return stringToJson(m_responseBody);
}

json
Client::createImageVariation(std::string image, int n, std::string size, std::string responseFormat, 
	std::string user)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesVariations);

	addFormParam("image", image);
	addFormParam("n", std::to_string(n));
	addFormParam("size", size);
	addFormParam("response_format", responseFormat);
	addFormParam("user", user);

	std::string payload = "";
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()),
		payload.length(), m_apikey, m_orgkey, "Content-Type: application/x-www-form-urlencoded", true);

	return stringToJson(m_responseBody);
}

json
Client::createModeration(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Moderation);

	std::stringstream ss;
	ss << jsonRequest;

	std::string payload = ss.str();
	std::string type = "POST";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::deleteFile( std::string fileId )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::DeleteFiles, fileId);

	std::string payload = "";
	std::string type = "DELETE";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()),
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::deleteModel( std::string model )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::DeleteFineTuneModel, model);

	std::string payload = "";
	std::string type = "DELETE";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()),
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::downloadFile( std::string fileId )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFileContent, fileId);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::listFiles()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFiles);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()),
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::listFineTuneEvents(std::string fineTuneId, bool stream)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFineTuneEvents, fineTuneId);

	addFormParam("stream", std::to_string(stream));

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey,"Content - Type: application / json", true);

	return stringToJson(m_responseBody);
}

json
Client::listFineTunes()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFineTunes);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::listModels()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Models);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::retrieveFile(std::string fileId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFile, fileId);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::retrieveFineTune(std::string fineTuneId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFineTune, fineTuneId);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()), 
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

json
Client::retrieveModel(std::string model)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Model, model);

	std::string payload = "";
	std::string type = "GET";

	m_httpCode = sendRequest(url, type, reinterpret_cast<const char*>(payload.c_str()),
		payload.length(), m_apikey, m_orgkey);

	return stringToJson(m_responseBody);
}

std::string Client::getResponseBody() { return m_responseBody; }

int Client::getResponseCode() { return m_httpCode; }
