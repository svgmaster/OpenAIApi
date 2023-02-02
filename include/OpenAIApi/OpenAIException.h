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


/*
 * OpenAIException.h
 *
 * This is the exception being thrown in case the api call was not successful
 */

#include <string>
#include <stdexcept> /* we use std::exception */

class  OpenAIException
    : public std::exception
{
public:
    OpenAIException(int errorCode
        , const std::string& message) : 
        m_Message(message),
        m_ErrorCode(errorCode)
    {};

    ~OpenAIException() = default;

    int getErrorCode() { return m_ErrorCode; };
    std::string getMessage() const { return m_Message; };

protected:
    std::string m_Message;
    int m_ErrorCode;
};
