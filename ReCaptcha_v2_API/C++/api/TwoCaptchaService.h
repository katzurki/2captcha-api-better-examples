#pragma once

#include "ProxyType.h"
#include <string>
#include <iostream>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace com { namespace twocaptcha { namespace http { class HttpWrapper; } } }

namespace com
{
	namespace twocaptcha
	{
		namespace api
		{


			using HttpWrapper = com::twocaptcha::http::HttpWrapper;

			class TwoCaptchaService
			{

				/// <summary>
				/// This class is used to establish a connection to 2captcha.com 
				/// and receive the token for solving google recaptcha v2
				/// 
				/// @author Chillivanilli
				/// @version 1.0
				/// 
				/// If you have a custom software requests, please contact me 
				/// via forum: http://thebot.net/members/chillivanilli.174861/
				/// via eMail: chillivanilli@chillibots.com
				/// via skype: ktlotzek
				/// </summary>


				/// <summary>
				/// Your 2captcha.com captcha KEY
				/// </summary>
			private:
				std::wstring apiKey;


				/// <summary>
				/// The google site key from the page you want to solve the recaptcha at
				/// </summary>
				std::wstring googleKey;


				/// <summary>
				/// The URL where the recaptcha is placed.
				/// For example: https://www.google.com/recaptcha/api2/demo
				/// </summary>
				std::wstring pageUrl;

				/// <summary>
				/// The proxy ip if you want a worker to solve the recaptcha through your proxy
				/// </summary>
				std::wstring proxyIp;

				/// <summary>
				/// The proxy port
				/// </summary>
				std::wstring proxyPort;

				/// <summary>
				/// Your proxy username, if your proxy uses user authentication
				/// </summary>
				std::wstring proxyUser;

				/// <summary>
				/// Your proxy password, if your proxy uses user authentication
				/// </summary>
				std::wstring proxyPw;

				/// <summary>
				/// Your proxy type, for example ProxyType.HTTP
				/// </summary>
				ProxyType proxyType = static_cast<ProxyType>(0);

				/// <summary>
				/// The HttpWrapper which the requests are made with
				/// </summary>
				HttpWrapper *hw;


				/// <summary>
				/// Constructor if you don't use any proxy </summary>
				/// <param name="apiKey"> </param>
				/// <param name="googleKey"> </param>
				/// <param name="pageUrl"> </param>
			public:
				TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl);

				/// <summary>
				/// Constructor if you are using a proxy without user authentication </summary>
				/// <param name="apiKey"> </param>
				/// <param name="googleKey"> </param>
				/// <param name="pageUrl"> </param>
				/// <param name="proxyIp"> </param>
				/// <param name="proxyPw"> </param>
				/// <param name="proxyType"> </param>
				TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl, const std::wstring &proxyIp, const std::wstring &proxyPort, ProxyType proxyType);

				/// <summary>
				/// Constructor if you are using a proxy with user authentication </summary>
				/// <param name="apiKey"> </param>
				/// <param name="googleKey"> </param>
				/// <param name="pageUrl"> </param>
				/// <param name="proxyIp"> </param>
				/// <param name="proxyPort"> </param>
				/// <param name="proxyUser"> </param>
				/// <param name="proxyPw"> </param>
				/// <param name="proxyType"> </param>
				TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl, const std::wstring &proxyIp, const std::wstring &proxyPort, const std::wstring &proxyUser, const std::wstring &proxyPw, ProxyType proxyType);

				/// <summary>
				/// Sends the recaptcha challenge to 2captcha.com and 
				/// checks every second if a worker has solved it
				/// </summary>
				/// <returns> The response-token which is needed to solve and submit the recaptcha </returns>
				/// <exception cref="InterruptedException">, when thread.sleep is interrupted </exception>
				/// <exception cref="IOException">, when there is any server issue and the request cannot be completed </exception>
				virtual std::wstring solveCaptcha() throw(InterruptedException, IOException);

				/// 
				/// <returns> The 2captcha.com captcha key </returns>
				virtual std::wstring getApiKey();

				/// <summary>
				/// Sets the 2captcha.com captcha key </summary>
				/// <param name="apiKey"> </param>
				virtual void setApiKey(const std::wstring &apiKey);

				/// 
				/// <returns> The google site key </returns>
				virtual std::wstring getGoogleKey();

				/// <summary>
				/// Sets the google site key </summary>
				/// <param name="googleKey"> </param>
				virtual void setGoogleKey(const std::wstring &googleKey);

				/// 
				/// <returns> The page url </returns>
				virtual std::wstring getPageUrl();

				/// <summary>
				/// Sets the page url </summary>
				/// <param name="pageUrl"> </param>
				virtual void setPageUrl(const std::wstring &pageUrl);

				/// 
				/// <returns> The proxy ip </returns>
				virtual std::wstring getProxyIp();

				/// <summary>
				/// Sets the proxy ip </summary>
				/// <param name="proxyIp"> </param>
				virtual void setProxyIp(const std::wstring &proxyIp);

				/// 
				/// <returns> The proxy port </returns>
				virtual std::wstring getProxyPort();

				/// <summary>
				/// Sets the proxy port </summary>
				/// <param name="proxyPort"> </param>
				virtual void setProxyPort(const std::wstring &proxyPort);

				/// 
				/// <returns> The proxy authentication user </returns>
				virtual std::wstring getProxyUser();

				/// <summary>
				/// Sets the proxy authentication user </summary>
				/// <param name="proxyUser"> </param>
				virtual void setProxyUser(const std::wstring &proxyUser);

				/// 
				/// <returns> The proxy authentication password </returns>
				virtual std::wstring getProxyPw();

				/// <summary>
				/// Sets the proxy authentication password </summary>
				/// <param name="proxyPw"> </param>
				virtual void setProxyPw(const std::wstring &proxyPw);

				/// 
				/// <returns> The proxy type </returns>
				virtual ProxyType getProxyType();

				/// <summary>
				/// Sets the proxy type </summary>
				/// <param name="proxyType"> </param>
				virtual void setProxyType(ProxyType proxyType);
			};

		}
	}
}
