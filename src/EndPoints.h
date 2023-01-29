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

#ifndef OPENAIAPI_ENDPOINTS_H
#define OPENAIAPI_ENDPOINTS_H 1

#include <string>

std::string openAI_baseApi = "https://api.openai.com/v1/";

enum class OpenAIEndpoint {
	// Given a prompt and an instruction, the model will return an edited version of the prompt.
	Edit,
	// Retrieves a model instance, providing basic information about the model such as the owner and permissioning. {model}
	Model,
	// List and describe the various models available in the API.
	Models,
	// Given a prompt, the model will return one or more predicted completions.
	Completions,
	// Given a prompt and/or an input image, the model will generate a new image.
	ImagesGenerations,
	// Creates an edited or extended image given an original image and a prompt.
	ImagesEdits,
	// Creates a variation of a given image.
	ImagesVariations,
	// Get a vector representation of a given input that can be easily consumed by machine learning models and algorithms.
	Embeddings,
	// Files are used to upload documents that can be used with features like Fine-tuning.
	ListFiles,
	/* Upload a file that contains document(s) to be used across various endpoints / features.
	   Currently, the size of all the files uploaded by one organization can be up to 1 GB.
	   Please contact us if you need to increase the storage limit.
	*/
	UploadFiles,
	// Delete a file. { file_id }
	DeleteFiles,
	// Returns information about a specific file. { file_id }
	RetrieveFile,
	// Returns the contents of the specified file. { file_id }
	RetrieveFileContent,
	// Manage fine-tuning jobs to tailor a model to your specific training data.
	FineTunes,
	// List your organization's fine-tuning jobs
	ListFineTunes,
	// Gets info about the fine-tune job. {fine_tune_id}
	RetrieveFineTune,
	// Immediately cancel a fine-tune job. {fine_tune_id}
	CancelFineTune,
	// Get fine - grained status updates for a fine - tune job. {fine_tune_id}
	ListFineTuneEvents,
	// Delete a fine-tuned model. You must have the Owner role in your organization. {model}
	DeleteFineTuneModel,
	// Given a input text, outputs if the model classifies it as violating OpenAI's content policy.
	Moderation,
	// The Engines endpoints are deprecated.
	//ListEngines, 
	// Set custom web url parameter
	Custom
};

/*
 * This function provides url endpoint to OpenAI APIs from OpenAIEndpoint enum
 * 
 * In situation to use other url outside base endpoint, you can choose Custom enum, 
 * and pass different url in param
 * 
 * \param endpoint Choose which endpoint want *Required*
 * \param param Special parameter for request
 * \return string with endpoint
 */
std::string getOpenAIUrl(OpenAIEndpoint endpoint, std::string param = "") {
	switch (endpoint) {
	case OpenAIEndpoint::Edit:
		return openAI_baseApi + "edits";
	case OpenAIEndpoint::Models:
		return openAI_baseApi + "models";
	case OpenAIEndpoint::Model:
		return openAI_baseApi + "models/" + param; /* {model_id} */
	case OpenAIEndpoint::Completions:
		return openAI_baseApi + "completions";
	case OpenAIEndpoint::ImagesGenerations:
		return openAI_baseApi + "images/generations";
	case OpenAIEndpoint::ImagesEdits:
		return openAI_baseApi + "images/edits";
	case OpenAIEndpoint::ImagesVariations:
		return openAI_baseApi + "images/variations";
	case OpenAIEndpoint::Embeddings:
		return openAI_baseApi + "embeddings";
	case OpenAIEndpoint::ListFiles:
	case OpenAIEndpoint::UploadFiles:
		return openAI_baseApi + "files";
	case OpenAIEndpoint::DeleteFiles:
	case OpenAIEndpoint::RetrieveFile:
		return openAI_baseApi + "files/" + param; /* {file_id} */
	case OpenAIEndpoint::RetrieveFileContent:
		return openAI_baseApi + "files/" + param + "/content"; /* {file_id} */
	case OpenAIEndpoint::FineTunes:
	case OpenAIEndpoint::ListFineTunes:
		return openAI_baseApi + "fine-tunes";
	case OpenAIEndpoint::RetrieveFineTune:
		return openAI_baseApi + "fine-tunes/" + param; /* {fine_tune_id} */
	case OpenAIEndpoint::CancelFineTune:
		return openAI_baseApi + "fine-tunes/" + param + "/cancel"; /* {fine_tune_id} */
	case OpenAIEndpoint::DeleteFineTuneModel:
		return openAI_baseApi + "models/" + param; /* {model_id} */
	case OpenAIEndpoint::Moderation:
		return openAI_baseApi + "moderations";
	case OpenAIEndpoint::Custom:
		return param;
	default:
		return openAI_baseApi + param;
	}
}

#endif /* !OPENAIAPI_ENDPOINTS_H */
