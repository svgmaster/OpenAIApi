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
#include <future> /* this is need for std::future */

#include <OpenAIApi/Client.h> /* define all functions, and use nlohmann/json */

#include "EndPoints.h" /* getOpenAIUrl */
#include "ApiHelper.h" /* request, getResponse */

using namespace OpenAIApi;

ApiHelper* api = nullptr;

Client::Client(std::string apiKey, std::string organizationKey)
{
	api = new ApiHelper(apiKey, organizationKey);
	m_apikey = apiKey, m_orgkey = organizationKey;
};


Client::~Client()
{
	delete api;
	api = nullptr;
}

std::future< Response< json >>
Client::cancelFineTune(std::string fineTuneId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::CancelFineTune, fineTuneId);
	std::string type = "POST";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createCompletion(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Completions);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createEdit(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Edit);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createEmbedding(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Embeddings);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createFile(std::string file, std::string purpose)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::UploadFiles);
	std::string type = "POST";

	api->addFormParam("file", file);
	api->addFormParam("purpose", purpose);
	api->request(url, type, "Content-Type : application/x-www-form-urlencoded");

	return api->getResponse();
}

std::future< Response< json >>
Client::createFineTune(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::FineTunes);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createImage(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesGenerations);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::createImageEdit(std::string image, std::string prompt, std::string mask, int n,
	std::string size, std::string responseFormat, std::string user)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesEdits);
	std::string type = "POST";

	api->addFormParam("image", image);
	api->addFormParam("mask", mask);
	api->addFormParam("prompt", prompt);
	api->addFormParam("n", std::to_string(n));
	api->addFormParam("size", size);
	api->addFormParam("response_format", responseFormat);
	api->addFormParam("user", user);

	api->request(url, type, "Content-Type: application/x-www-form-urlencoded");

	return api->getResponse();
}

std::future< Response< json >>
Client::createImageVariation(std::string image, int n, std::string size, std::string responseFormat, 
	std::string user)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ImagesVariations);
	std::string type = "POST";

	api->addFormParam("image", image);
	api->addFormParam("n", std::to_string(n));
	api->addFormParam("size", size);
	api->addFormParam("response_format", responseFormat);
	api->addFormParam("user", user);

	api->request(url, type, "Content-Type: application/x-www-form-urlencoded");

	return api->getResponse();
}

std::future< Response< json >>
Client::createModeration(json jsonRequest)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Moderation);
	std::string type = "POST";

	api->setJsonRequest(jsonRequest);
	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::deleteFile( std::string fileId )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::DeleteFiles, fileId);
	std::string type = "DELETE";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::deleteModel( std::string model )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::DeleteFineTuneModel, model);
	std::string type = "DELETE";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::downloadFile( std::string fileId )
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFileContent, fileId);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::listFiles()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFiles);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::listFineTuneEvents(std::string fineTuneId, bool stream)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFineTuneEvents, fineTuneId);

	api->addFormParam("stream", std::to_string(stream));
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::listFineTunes()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::ListFineTunes);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::listModels()
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Models);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::retrieveFile(std::string fileId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFile, fileId);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::retrieveFineTune(std::string fineTuneId)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::RetrieveFineTune, fineTuneId);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}

std::future< Response< json >>
Client::retrieveModel(std::string model)
{
	std::string url = getOpenAIUrl(OpenAIEndpoint::Model, model);
	std::string type = "GET";

	api->request(url, type);

	return api->getResponse();
}
