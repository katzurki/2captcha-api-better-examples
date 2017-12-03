#pragma once

#include <string>

namespace com
{
	namespace twocaptcha
	{
		namespace http
		{


			/// <summary>
			/// This class can be used for easy GET requests to a server
			/// I removed a lot of things to make it as simple as possible and modified 
			/// it for the use with the 2captcha.com API
			/// 
			/// @author Pieter Hiele
			/// @author modified and shrinked by Chillivanilli
			/// 
			/// </summary>

			class HttpWrapper
			{

			private:
				bool printHeaders = false;
				std::wstring html;
				int responseCode = 0;

				/// <summary>
				/// Default constructor
				/// </summary>
			public:
				HttpWrapper();

				/// <summary>
				/// A method to get the content and headers (if set) of a given page, with a given referer.
				/// </summary>
				/// <param name="url">
				///          The given URL. </param>
				/// <param name="referer">
				///          The given referer. </param>
				/// <exception cref="IllegalStateException">
				///          Whenever an IO-related problem occurs.
				/// @post
				///          new.getHtml() will return the headers and content of the given URL. </exception>

				virtual void get(const std::wstring &url);


				/// <summary>
				/// Return the html content that this Wrapper has last retrieved from a request.
				/// </summary>
				virtual std::wstring getHtml();

				/// <summary>
				/// Set the html content of this HttpWrapper.
				/// </summary>
				/// <param name="html">
				///          The new html content. </param>
			private:
				void setHtml(const std::wstring &html);

				/// <summary>
				/// Set if headers should be print above the content or not </summary>
				/// <param name="trueOrFalse"> </param>
			public:
				virtual void setPrintHeaders(bool trueOrFalse);

				/// <summary>
				/// Returns the response code of the request
				/// @return
				/// </summary>
				virtual int getResponseCode();

			};
		}
	}
}
