/**************************************************************************************\
*
*   MIT License
*
*   Community-maintained OpenAI API Library for modern C++
*
*   Copyright (c) 2023 Stanislav Gadzhov
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*	  of this software and associated documentation files (the "Software"), to deal
*	  in the Software without restriction, including without limitation the rights
*	  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	  copies of the Software, and to permit persons to whom the Software is
*	  furnished to do so, subject to the following conditions:
*
*	  The above copyright notice and this permission notice shall be included in all
*	  copies or substantial portions of the Software.
*
*	  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*	  SOFTWARE.
*
\**************************************************************************************/

#ifndef OPENAIAPI_RESPONSE_H
#define OPENAIAPI_RESPONSE_H

#include <string>
#include <future>

namespace OpenAIApi {

	struct ServerResponse
	{
		std::string header; // Get string from response
		int statusCode; // Get HTTP response code from request
	};

	template<class ResponseModel>
	class Response : public std::future<ResponseModel>
	{
	public:

		Response(ResponseModel model, ServerResponse serverData) :
			m_Model(model),
			m_ServerData(serverData)
		{	};

		// Get response model
		ResponseModel Model() { return m_Model; };

		// Get server data from response
		ServerResponse ServerData() { return m_ServerData; };

	protected:

		ResponseModel m_Model;
		ServerResponse m_ServerData;
	};

}; // end of namespace OpenAIApi


#endif // !OPENAIAPI_RESPONSE_H
