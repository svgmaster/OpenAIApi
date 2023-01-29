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

#include <OpenAIApi/Client.h>
using namespace OpenAIApi;

int main()
{
    std::string apiKey = getenv("OPENAI_API_KEY"); // get API key for authentication
    std::string apiOrg = getenv("OPENAI_ORG_KEY"); // optional specify which organization is used for an API request

    try {
        Client* client = new Client( apiKey, apiOrg );

        std::string response = client->createCompletion({
            {"model", "text-davinci-002"},
            {"prompt" , "Somebody once told me the world is gonna roll me"},
            {"temperature", 0},
            {"max_tokens", 10}
            })
            ["choices"][0]["text"];

        delete client; // free up memory

        std::cout << response << std::endl;

        return 0;

    } catch ( std::runtime_error e ) {

        std::cout << e.what() << std::endl;

        return 1;
    }
}
