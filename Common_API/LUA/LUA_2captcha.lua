--load required modules
local http = require("socket.http")
local url = require("socket.url")
local mime = require("mime")
local ltn12 = require("ltn12")

function vardump(value, depth, key)
  local linePrefix = ''
  local spaces = ''

  if key ~= nil then
    linePrefix = key .. ' = '
  end

  if depth == nil then
    depth = 0
  else
    depth = depth + 1
    for i=1, depth do
      spaces = spaces .. '  '
    end
  end

  if type(value) == 'table' then
    mTable = getmetatable(value)
    if mTable == nil then
      print(spaces .. linePrefix .. '(table) ')
    else
      print(spaces .. '(metatable) ')
        value = mTable
    end
    for tableKey, tableValue in pairs(value) do
      vardump(tableValue, depth, tableKey)
    end
  elseif type(value)  == 'function' or
    type(value) == 'thread' or
    type(value) == 'userdata' or
    value == nil then
      print(spaces .. tostring(value))
  elseif type(value)  == 'string' then
    print(spaces .. linePrefix .. '"' .. tostring(value) .. '",')
  else
    print(spaces .. linePrefix .. tostring(value) .. ',')
  end
end


timeout = 10 --bare minimum is 5
apiKey = 'dcd55077d6c883bb28cf79451b8689a1' --your apiKey 
apiUrl = 'https://2captcha.com/in.php'
apiResUrl = 'https://2captcha.com/res.php'
base64EncImg = "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"

local request_body = 'method=base64&key=' .. apiKey .. '&body=' .. url.escape(base64EncImg)
local response_body = {}

response_result, response_code, response_headers, response_status = http.request {
        url = apiUrl,
        method = 'POST',
        headers = { ['Content-Type'] = 'application/x-www-form-urlencoded',
		    ['Content-Length'] = tostring(#request_body)  },
        source = ltn12.source.string(request_body),
	sink = ltn12.sink.table(response_body)
}
if time_requested == nil then 
  time_requested = os.time();

_, _, current_status = response_body.1:find('(%w+)')


elseif os.time()-time_requested>timeout then 
  return("Time out and die.")
else 
  newurl=apiResUrl .. '?key=' .. apiKey .. '&action=get&id=' .. captcha_id
  print(newurl)
end
  response_result, response_code, response_headers, response_status = http.request(apiResUrl .. '?key=' .. apiKey .. '&action=get&id=' .. captcha_id )

vardump(response_result)
vardump(response_code)
vardump(response_headers)
vardump(response_body)

    
  
