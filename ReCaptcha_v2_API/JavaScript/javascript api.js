function SolveRecaptchaV2(APIKey, googleKey, pageUrl, proxy, proxyType){
			var requestUrl = "http://2captcha.com/in.php?key=" + APIKey + "&method=userrecaptcha&googlekey=" + googleKey + "&pageurl=" + pageUrl + "&proxy=" + proxy + "&proxytype=";
			
			switch (proxyType) {
				case 'HTTP':
				requestUrl = requestUrl + "HTTP";
				break;
				
				case 'HTTPS':
				requestUrl = requestUrl + "HTTPS";
				break;
				
				case 'SOCKS4':
				requestUrl = requestUrl + "SOCKS4";
				break;
				
				case 'SOCKS5':
				requestUrl = requestUrl + "SOCKS5";
				break;
			}
			
			$.ajax({url: "requestUrl", success: function(result){
        		if(result.length < 3){
					return false;
				}else{
					if(result.substring(0, 3) == "OK|"){
						var captchaID = result.substring(3);
						
						for(var i=0; i<24; i++){
							var ansUrl = "http://2captcha.com/res.php?key=" + APIKey + "&action=get&id=" + captchaID;	
							
							$.ajax({url: "ansUrl", success: function(ansresult){
									if(ansresult.length < 3){
										return ansresult;
									}else{
										if(ansresult.substring(0, 3) == "OK|"){
											return ansresult;
										}else if (ansresult != "CAPCHA_NOT_READY"){
                                            return ansresult;
                                        }
									}
								}
							});
							 await sleep(5000);
						}
						
					}else{
						return ansresult;	
					}
				}
    		},
			fail: function(){
				return "";
				}
			});
			
		}
