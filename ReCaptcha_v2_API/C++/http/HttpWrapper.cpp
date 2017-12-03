#include "HttpWrapper.h"

namespace com
{
	namespace twocaptcha
	{
		namespace http
		{

			HttpWrapper::HttpWrapper()
			{
				html = L"";
			}

			void HttpWrapper::get(const std::wstring &url)
			{

				try
				{
					URL *url_ = new URL(url);
					HttpURLConnection *conn;

					conn = static_cast<HttpURLConnection*>(url_->openConnection());
					conn->setRequestMethod(L"GET");
					conn->setAllowUserInteraction(false);
					conn->setDoOutput(false);
					conn->setInstanceFollowRedirects(false);

					conn->setRequestProperty(L"User-Agent", L"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0");
					conn->setRequestProperty(L"Accept", L"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
					conn->setRequestProperty(L"Accept-Language", L"en-US,en;q=0.8");
					conn->setRequestProperty(L"Connection", L"keep-alive");

					std::wstring headers = L"";

					if (printHeaders)
					{
						for (std::wstring key : conn->getHeaderFields().keySet())
						{
							headers += ((key != nullptr)?key + std::wstring(L": "):L"") + conn->getHeaderField(key) + std::wstring(L"\n");
						}
					}

					responseCode = conn->getResponseCode();

					InputStreamReader tempVar(new DataInputStream(conn->getInputStream()));
					BufferedReader *d = new BufferedReader(&tempVar);
					std::wstring result = L"";
					std::wstring line = L"";
					while ((line = d->readLine()) != L"")
					{
						line = std::wstring(line.getBytes(),L"UTF-8");
						result += line + std::wstring(L"\n");
					}

					d->close();

					if (printHeaders)
					{
						setHtml(headers + std::wstring(L"\n") + result);
					}
					else
					{
						setHtml(result);
					}
				}
				catch (IOException e)
				{
					IllegalStateException tempVar2(std::wstring(L"An IOException occurred:") + std::wstring(L"\n") + e->getMessage());
					throw &tempVar2;
				}
			}

			std::wstring HttpWrapper::getHtml()
			{
				return this->html;
			}

			void HttpWrapper::setHtml(const std::wstring &html)
			{
				this->html = html;
			}

			void HttpWrapper::setPrintHeaders(bool trueOrFalse)
			{
				printHeaders = trueOrFalse;
			}

			int HttpWrapper::getResponseCode()
			{
				return responseCode;
			}
		}
	}
}
