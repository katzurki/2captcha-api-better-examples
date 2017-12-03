#2captha RUBY API
require 'net/http'

module ProxyType
  HTTP = 1
  HTTPS = 2
  SOCKS4 = 3
  SOCKS5 = 4
end

def SolveRecaptchaV2(_APIKey, googleKey, pageUrl, proxy, ptype)
    
    requestUrl = 'http://2captcha.com/in.php?key=' + _APIKey + '&method=userrecaptcha&googlekey=' + googleKey + '&pageurl=' + pageUrl + '&proxy=' + proxy + '&proxytype='
    
        case ptype
            when ProxyType::HTTP
              requestUrl = requestUrl + 'HTTP'
            when ProxyType::HTTPS
              requestUrl = requestUrl + 'HTTPS'
            when ProxyType::SOCKS4
              requestUrl = requestUrl + 'SOCKS4'
            when ProxyType::SOCKS5
              requestUrl = requestUrl + 'SOCKS5'
        end
    
    url = URI.parse(requestUrl)
    req = Net::HTTP::Get.new(url.to_s)
    res = Net::HTTP.start(url.host, url.port) {|http|
      http.request(req)
    }
    result = res.body.to_s
    
    if(result.length < 3 || result[0..2] != 'OK|')
        return result
    end
    
    captchaID = result[3..-1]
    
    for i in 0..24       
        requestUrl = 'http://2captcha.com/res.php?key=' + _APIKey + '&action=get&id=' + captchaID   
        url = URI.parse(requestUrl)
        req = Net::HTTP::Get.new(url.to_s)
        res = Net::HTTP.start(url.host, url.port) {|http|
          http.request(req)
        }
        result = res.body.to_s

        
        if(result.length < 3)
            return result
        
        else
            if(result[0..2] == 'OK|')
                return result[3..-1]
            
            elseif (result != 'CAPCHA_NOT_READY')
                return result
            end
        end  
        sleep(5)
    end
    return result
end

#usage example
puts SolveRecaptchaV2('APIKey','6Le-wvkSAAAAAPBMRTvw0Q4Muexq9bi0DJwx_mJ-','https://www.google.com/recaptcha/api2/demo','username:password@ip:port',1)