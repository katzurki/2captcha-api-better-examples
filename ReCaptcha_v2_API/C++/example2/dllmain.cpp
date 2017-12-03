#define _CRT_SECURE_NO_WARNINGS
#include "WinHttpClient.h"



enum ProxyType
{
    HTTP,
    HTTPS,
    SOCKS4,
    SOCKS5
}pt;
/// <summary>
/// Sends a solve request and waits for a response
/// </summary>
/// <param name="APIKey">Your API Key</param>
/// <param name="_googleKey">The "sitekey" value from site your captcha is located on</param>
/// <param name="_pageUrl">The page the captcha is located on</param>
/// <param name="proxy">The proxy used, format: "username:password@ip:port</param>
/// <param name="proxyType">The type of proxy used</param>
/// <param name="_result">If solving was successful this contains the answer</param>
/// <returns>Returns true if solving was successful, otherwise false</returns>
__declspec(dllexport) int SoleWith2Captha(wchar_t* _APIKey, wchar_t* _googleKey, wchar_t* _pageUrl, wchar_t* _proxy, ProxyType _proxyType, wchar_t* result)
{
	wstring  APIKey = _APIKey, googleKey = _googleKey, pageUrl = _pageUrl, proxy = _proxy;

	wstring requestUrl = wstring(L"http://2captcha.com/in.php?key=") + APIKey + wstring(L"&method=userrecaptcha&googlekey=") + googleKey + wstring(L"&pageurl=") + pageUrl + wstring(L"&proxy=") + proxy + wstring(L"&proxytype=");
	
	switch (_proxyType) 
	{
	case ProxyType::HTTP:
		requestUrl = requestUrl + wstring(L"HTTP");
		break;
				
		case ProxyType::HTTPS:
		requestUrl = requestUrl + wstring(L"HTTPS");
		break;
				
		case ProxyType::SOCKS4:
		requestUrl = requestUrl + wstring(L"SOCKS4");
		break;
				
		case ProxyType::SOCKS5:
		requestUrl = requestUrl + wstring(L"SOCKS5");
		break;
	}
	
	WinHttpClient client(requestUrl);
	client.SendHttpRequest();
	wstring httpResponseContent = client.GetResponseContent();

	if(httpResponseContent.length() < 3 || 
		(httpResponseContent.substr(0,3).find(L"OK|") == std::string::npos))
	{
		wcscpy(result, httpResponseContent.c_str());
        return false;
	}

	wstring captchaID = httpResponseContent.erase(0, 3);

	for (int i = 0; i < 24; i++)
	{
		requestUrl = wstring(L"http://2captcha.com/res.php?key=") + APIKey + wstring(L"&action=get&id=") + captchaID;
		client.UpdateUrl(requestUrl);
		client.SendHttpRequest();
		httpResponseContent = client.GetResponseContent();

		if(httpResponseContent.length() < 3)
		{
			wcscpy(result, httpResponseContent.c_str());
			return false;
		}
		else
		{
			if (httpResponseContent.substr(0,3).find(L"OK|") != std::string::npos)
			{
				wcscpy(result, httpResponseContent.erase(0, 3).c_str());
				return true;
			}
			else if (httpResponseContent.find(L"CAPCHA_NOT_READY"))
			{
				wcscpy(result, httpResponseContent.c_str());
				return false;
			}
		}
		Sleep(5000);
	}

	result = L"Unknown error";
	return false;
}

void main()
{
	wchar_t result[3072];
    int succeeded = SoleWith2Captha(L"APIKEY", L"6Le-wvkSAAAAAPBMRTvw0Q4Muexq9bi0DJwx_mJ-", L"https://www.google.com/recaptcha/api2/demo", L"proxy", ProxyType::HTTP, result);

    printf("result: %s, Succeeded: %d",result, succeeded); // for succeeded (0 failed, 1 succeeded)
    getchar();
}