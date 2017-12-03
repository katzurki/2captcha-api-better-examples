#include "HowToUse.h"
#include "../api/ProxyType.h"
#include "../api/TwoCaptchaService.h"

namespace com
{
	namespace twocaptcha
	{
		namespace example
		{
			using ProxyType = com::twocaptcha::api::ProxyType;
			using TwoCaptchaService = com::twocaptcha::api::TwoCaptchaService;

			void HowToUse::main(std::vector<std::wstring> &args)
			{

				std::wstring apiKey = L"Your 2captcha.com captcha key";
				std::wstring googleKey = L"6Le-wvkSAAAAAPBMRTvw0Q4Muexq9bi0DJwx_mJ-";
				std::wstring pageUrl = L"https://www.google.com/recaptcha/api2/demo";
				std::wstring proxyIp = L"183.38.231.131";
				std::wstring proxyPort = L"8888";
				std::wstring proxyUser = L"username";
				std::wstring proxyPw = L"password";

				/// <summary>
				/// With proxy and user authentication
				/// </summary>
				TwoCaptchaService *service = new TwoCaptchaService(apiKey, googleKey, pageUrl, proxyIp, proxyPort, proxyUser, proxyPw, ProxyType::HTTP);

				/// <summary>
				/// Without proxy and user authentication
				/// TwoCaptchaService service = new TwoCaptchaService(apiKey, googleKey, pageUrl);
				/// </summary>

				try
				{
					std::wstring responseToken = service->solveCaptcha();
					std::wcout << std::wstring(L"The response token is: ") << responseToken << std::endl;
				}
				catch (InterruptedException e)
				{
					std::wcout << std::wstring(L"ERROR case 1") << std::endl;
					e->printStackTrace();
				}
				catch (IOException e)
				{
					std::wcout << std::wstring(L"ERROR case 2") << std::endl;
					e->printStackTrace();
				}
			}
		}
	}
}
