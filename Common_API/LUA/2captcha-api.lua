--load required modules
wtime = nil
local http = require("socket.http")
local url = require("socket.url")
local mime = require("mime")
local ltn12 = require("ltn12")

timeout = 20 --bare minimum is 5
apiKey = '' --your apiKey
apiUrl = 'https://2captcha.com/in.php'
apiResUrl = 'https://2captcha.com/res.php'
base64EncImg = '' --please don't forget to sanitize your input

function submitCaptcha()
local request_body = 'method=base64&key=' .. apiKey .. '&body=' .. url.escape(base64EncImg)
local response_body = {}
response_result, response_code, response_headers, response_status = http.request{ 
    url = apiUrl,
    method = 'POST',
    headers = { ['Content-Type'] = 'application/x-www-form-urlencoded',
      ['Content-Length'] = tostring(#request_body) },
    source = ltn12.source.string(request_body),
    sink = ltn12.sink.table(response_body)
}
  
  status, captcha_id = response_body[1]:match("([^|]+)\|([^|]+)")
  if status == nil then
    status = response_body[1] --either we return ERROR_TEXT entirely as one string
  end
return {status,captcha_id} --or our regex matched and we know it is a success
end

function wait(waitTime)
  timer = os.time()
   repeat until os.time() > timer + waitTime
end

function checkForCaptcha(captcha_id)
      response_result, response_code, response_headers, response_status = http.request(apiResUrl .. '?key=' .. apiKey .. '&action=get&id=' .. captcha_id )
      status, captchaResult = response_result:match("([^|]+)\|([^|]+)")
      if (captchaResult) then return captchaResult end
    return false
end

function die (msg)
  io.stderr:write(msg,'\n')
  os.exit(1)
end

try = submitCaptcha()
if try[1] == 'OK' then
 if not wtime then 
  wait(5)
  wtime = 5
 end
else 
  die('Server returned error or empty response: ' .. try[1])
end

while wtime < timeout do 
  end_result = checkForCaptcha(try[2])
  if end_result then break end
  wtime = wtime + 1
end

print(end_result)

