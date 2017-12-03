using System;
using TwoCaptcha_API;

namespace Example
{
    class Program
    {
        static void Main(string[] args)
        {
            TwoCaptchaClient client = new TwoCaptchaClient("apikey");

            string result;
            bool succeeded = client.SolveRecaptchaV2("6Le-wvkSAAAAAPBMRTvw0Q4Muexq9bi0DJwx_mJ-", "https://www.google.com/recaptcha/api2/demo", "username:password@ip:port", ProxyType.HTTP, out result);

            Console.WriteLine(result);
            Console.WriteLine(succeeded);
            Console.ReadKey();
        }
    }
}
