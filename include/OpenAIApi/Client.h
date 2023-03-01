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

#ifndef OPENAIAPI_CLIENT_H
#define OPENAIAPI_CLIENT_H

#include <list>
#include <string>
#include <future>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/* Error Handler */
#include  "OpenAIException.h"

/* Response class */
#include  "Response.h"


namespace OpenAIApi {

	/**
	 *  Class OpenAI API Client
	 *	
	 */
	class Client {

	public:
		Client( std::string apiKey, std::string organizationKey = std::string() );

		virtual ~Client();

		/**
		* Immediately cancel a fine-tune job. .
		*
		*
		* \param fineTuneId The ID of the fine-tune job to cancel  *Required*
		*/
		std::future< Response< json >>
		cancelFineTune( std::string fineTuneId );

		/**
		* Creates a completion for the provided prompt and parameters.
		*
		*
		* \param createCompletionRequest  *Required*
		*/
		std::future< Response< json >>
		createCompletion( json jsonRequest );

		/**
		* Creates a new edit for the provided input, instruction, and parameters.
		*
		*
		* \param createEditRequest  *Required*
		*/
		std::future< Response< json >>
		createEdit( json jsonRequest );

		/**
		* Creates an embedding vector representing the input text..
		*
		*
		* \param createEmbeddingRequest  *Required*
		*/
		std::future< Response< json >>
		createEmbedding( json jsonRequest );

		/**
		* Upload a file that contains document(s) to be used across various endpoints/features. Currently, the size of all the files uploaded by one organization can be up to 1 GB. Please contact us if you need to increase the storage limit. .
		*
		*
		* \param file Name of the [JSON Lines](https://std::future< Response< json >>lines.readthedocs.io/en/latest/) file to be uploaded.  If the `purpose` is set to \\\"fine-tune\\\", each line is a JSON record with \\\"prompt\\\" and \\\"completion\\\" fields representing your [training examples](/docs/guides/fine-tuning/prepare-training-data).  *Required*
		* \param purpose The intended purpose of the uploaded documents.  Use \\\"fine-tune\\\" for [Fine-tuning](/docs/api-reference/fine-tunes). This allows us to validate the format of the uploaded file.  *Required*
		*/
		std::future< Response< json >>
		createFile( std::string file, std::string purpose );

		/**
		* Creates a job that fine-tunes a specified model from a given dataset.  Response includes details of the enqueued job including job status and the name of the fine-tuned models once complete.  [Learn more about Fine-tuning](/docs/guides/fine-tuning) .
		*
		*
		* \param createFineTuneRequest  *Required*
		*/
		std::future< Response< json >>
		createFineTune( json jsonRequest );

		/**
		* Creates an image given a prompt..
		*
		*
		* \param createImageRequest  *Required*
		*/
		std::future< Response< json >>
		createImage( json jsonRequest );

		/**
		* Creates an edited or extended image given an original image and a prompt..
		*
		*
		* \param image The image to edit. Must be a valid PNG file, less than 4MB, and square. If mask is not provided, image must have transparency, which will be used as the mask. *Required*
		* \param prompt A text description of the desired image(s). The maximum length is 1000 characters. *Required*
		* \param mask An additional image whose fully transparent areas (e.g. where alpha is zero) indicate where `image` should be edited. Must be a valid PNG file, less than 4MB, and have the same dimensions as `image`.
		* \param n The number of images to generate. Must be between 1 and 10.
		* \param size The size of the generated images. Must be one of `256x256`, `512x512`, or `1024x1024`.
		* \param responseFormat The format in which the generated images are returned. Must be one of `url` or `b64_std::future< Response< json >>`.
		* \param user A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse. [Learn more](/docs/guides/safety-best-practices/end-user-ids).
		*/
		std::future< Response< json >>
		createImageEdit( std::string image, std::string prompt, std::string mask, int n, std::string size, 
			std::string responseFormat, std::string user );

		/**
		* Creates a variation of a given image..
		*
		*
		* \param image The image to use as the basis for the variation(s). Must be a valid PNG file, less than 4MB, and square. *Required*
		* \param n The number of images to generate. Must be between 1 and 10.
		* \param size The size of the generated images. Must be one of `256x256`, `512x512`, or `1024x1024`.
		* \param responseFormat The format in which the generated images are returned. Must be one of `url` or `b64_std::future< Response< json >>`.
		* \param user A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse. [Learn more](/docs/guides/safety-best-practices/end-user-ids).
		*/
		std::future< Response< json >>
		createImageVariation( std::string image, int n, std::string size, std::string responseFormat, std::string user);

		/**
		* Classifies if text violates OpenAI's Content Policy.
		*
		*
		* \param createModerationRequest  *Required*
		*/
		std::future< Response< json >>
		createModeration( json jsonRequest );

		/**
		* Delete a file..
		*
		*
		* \param fileId The ID of the file to use for this request *Required*
		*/
		std::future< Response< json >>
		deleteFile( std::string fileId );

		/**
		* Delete a fine-tuned model. You must have the Owner role in your organization..
		*
		*
		* \param model The model to delete *Required*
		*/
		std::future< Response< json >>
		deleteModel( std::string model );

		/**
		* Returns the contents of the specified file.
		*
		*
		* \param fileId The ID of the file to use for this request *Required*
		*/
		std::future< Response< json >>
		downloadFile( std::string fileId );
		
		/**
		* Lists the currently available (non-finetuned) models, and provides basic information about each one such as the owner and availability..
		*
		* The Engines endpoints are deprecated.
		*/
		//std::future< Response< json >>
		//listEngines();

		/**
		* Returns a list of files that belong to the user's organization..
		*
		*
		*/
		std::future< Response< json >> 
		listFiles();

		/**
		* Get fine-grained status updates for a fine-tune job. .
		*
		*
		* \param fineTuneId The ID of the fine-tune job to get events for.  *Required*
		* \param stream Whether to stream events for the fine-tune job. If set to true, events will be sent as data-only [server-sent events](https://developer.mozilla.org/en-US/docs/Web/API/Server-sent_events/Using_server-sent_events#Event_stream_format) as they become available. The stream will terminate with a `data: [DONE]` message when the job is finished (succeeded, cancelled, or failed).  If set to false, only events generated so far will be returned.
		*/
		std::future< Response< json >>
		listFineTuneEvents( std::string fineTuneId, bool stream );

		/**
		* List your organization's fine-tuning jobs .
		*
		*
		*/
		std::future< Response< json >>
		listFineTunes();

		/**
		* Lists the currently available models, and provides basic information about each one such as the owner and availability..
		*
		*
		*/
		std::future< Response< json >>
		listModels();

		/**
		* Returns information about a specific file..
		*
		*
		* \param fileId The ID of the file to use for this request *Required*
		*/
		std::future< Response< json >>
		retrieveFile( std::string fileId );

		/**
		* Gets info about the fine-tune job.  [Learn more about Fine-tuning](/docs/guides/fine-tuning) .
		*
		*
		* \param fineTuneId The ID of the fine-tune job  *Required*
		*/
		std::future< Response< json >>
		retrieveFineTune( std::string fineTuneId );

		/**
		* Retrieves a model instance, providing basic information about the model such as the owner and permissioning..
		*
		*
		* \param model The ID of the model to use for this request *Required*
		*/
		std::future< Response< json >>
		retrieveModel( std::string model );

	private:
		std::string m_apikey;
		std::string m_orgkey;

	};

}

#endif /* !OPENAIAPI_CLIENT_H */
