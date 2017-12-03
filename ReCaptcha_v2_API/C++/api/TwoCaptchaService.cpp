#include "TwoCaptchaService.h"
#include "../http/HttpWrapper.h"

namespace com
{
	namespace twocaptcha
	{
		namespace api
		{
			using HttpWrapper = com::twocaptcha::http::HttpWrapper;

			TwoCaptchaService::TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl)
			{
				this->apiKey = apiKey;
				this->googleKey = googleKey;
				this->pageUrl = pageUrl;
				hw = new HttpWrapper();
			}

			TwoCaptchaService::TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl, const std::wstring &proxyIp, const std::wstring &proxyPort, ProxyType proxyType) : TwoCaptchaService(apiKey, googleKey, pageUrl)
			{
				this->proxyIp = proxyIp;
				this->proxyPort = proxyPort;
				this->proxyType = proxyType;
			}

			TwoCaptchaService::TwoCaptchaService(const std::wstring &apiKey, const std::wstring &googleKey, const std::wstring &pageUrl, const std::wstring &proxyIp, const std::wstring &proxyPort, const std::wstring &proxyUser, const std::wstring &proxyPw, ProxyType proxyType) : TwoCaptchaService(apiKey,googleKey,pageUrl)
			{
				this->proxyIp = proxyIp;
				this->proxyPort = proxyPort;
				this->proxyUser = proxyUser;
				this->proxyPw = proxyPw;
				this->proxyType = proxyType;
			}

			std::wstring TwoCaptchaService::solveCaptcha() throw(InterruptedException, IOException)
			{
				std::wcout << std::wstring(L"Sending recaptcha challenge to 2captcha.com") << std::endl;

				std::wstring parameters = std::wstring(L"key=") + apiKey + std::wstring(L"&method=userrecaptcha") + std::wstring(L"&googlekey=") + googleKey + std::wstring(L"&pageurl=") + pageUrl;

				if (proxyIp != L"")
				{
					if (proxyUser != L"")
					{
						parameters += std::wstring(L"&proxy=") + proxyUser + std::wstring(L":") + proxyPw + std::wstring(L"@") + proxyIp + std::wstring(L":") + proxyPort;
					}
					else
					{
						parameters += std::wstring(L"&proxy=") + proxyIp + std::wstring(L":") + proxyPort;
					}

					parameters += std::wstring(L"&proxytype=") + proxyType;
				}
				hw->get(std::wstring(L"http://2captcha.com/in.php?") + parameters);

				std::wstring captchaId = hw->getHtml().replaceAll(L"\\D", L"");
				int timeCounter = 0;

				do
				{
					hw->get(std::wstring(L"http://2captcha.com/res.php?key=") + apiKey + std::wstring(L"&action=get") + std::wstring(L"&id=") + captchaId);

					delay(1000);

					timeCounter++;
					std::wcout << std::wstring(L"Waiting for captcha to be solved") << std::endl;
				} while (hw->getHtml().find(L"NOT_READY") != std::wstring::npos);

				std::wcout << std::wstring(L"It took ") << timeCounter << std::wstring(L" seconds to solve the captcha") << std::endl;
				std::wstring gRecaptchaResponse = hw->getHtml().replaceAll(L"OK\\|", L"").replaceAll(L"\\n", L"");
				return gRecaptchaResponse;
			}

			std::wstring TwoCaptchaService::getApiKey()
			{
				return apiKey;
			}

			void TwoCaptchaService::setApiKey(const std::wstring &apiKey)
			{
				this->apiKey = apiKey;
			}

			std::wstring TwoCaptchaService::getGoogleKey()
			{
				return googleKey;
			}

			void TwoCaptchaService::setGoogleKey(const std::wstring &googleKey)
			{
				this->googleKey = googleKey;
			}

			std::wstring TwoCaptchaService::getPageUrl()
			{
				return pageUrl;
			}

			void TwoCaptchaService::setPageUrl(const std::wstring &pageUrl)
			{
				this->pageUrl = pageUrl;
			}

			std::wstring TwoCaptchaService::getProxyIp()
			{
				return proxyIp;
			}

			void TwoCaptchaService::setProxyIp(const std::wstring &proxyIp)
			{
				this->proxyIp = proxyIp;
			}

			std::wstring TwoCaptchaService::getProxyPort()
			{
				return proxyPort;
			}

			void TwoCaptchaService::setProxyPort(const std::wstring &proxyPort)
			{
				this->proxyPort = proxyPort;
			}

			std::wstring TwoCaptchaService::getProxyUser()
			{
				return proxyUser;
			}

			void TwoCaptchaService::setProxyUser(const std::wstring &proxyUser)
			{
				this->proxyUser = proxyUser;
			}

			std::wstring TwoCaptchaService::getProxyPw()
			{
				return proxyPw;
			}

			void TwoCaptchaService::setProxyPw(const std::wstring &proxyPw)
			{
				this->proxyPw = proxyPw;
			}

			ProxyType TwoCaptchaService::getProxyType()
			{
				return proxyType;
			}

			void TwoCaptchaService::setProxyType(ProxyType proxyType)
			{
				this->proxyType = proxyType;
			}
		}
	}
}
