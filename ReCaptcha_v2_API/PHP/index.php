<html>
  <head>

    <title>spicedinc </title>
    <script src='https://www.google.com/recaptcha/api.js'></script>
  </head>
  <body style="font-family:Verdana;">
    <h1>Google reCAPTHA Demo</h1>
    <form id="comment_form" action="form.php" method="post">
      <input type="email" placeholder="Type your email" name="email"size="40"><br><br>
      <textarea name="comment" rows="8" cols="39"></textarea><br><br>
<input type="submit" name="submit" value="Post comment"><br><br>
      <div class="g-recaptcha" data-sitekey="6Lc6MwsUAAAAAP813-674bEeF7gMBj4s858xpp4H"></div>

    </form>
  </body>
<?php
$retrieve= file_get_contents("http://2captcha.com/in.php?key=220f63ac9ed69a6e486f5625ecb5edf8&method=userrecaptcha&googlekey=6Lc6MwsUAAAAAP813-674bEeF7gMBj4s858xpp4H");

$first = array($retrieve);
$result = explode('OK|',$first[0]);
$hello = $result[1];
$con="http://2captcha.com/res.php?key=220f63ac9ed69a6e486f5625ecb5edf8&action=get&id=".$hello;
 
sleep(23);

$getting = file_get_contents($con);
$second = array($getting);
$secondresult = explode('OK|',$second[0]);

echo $secondresult[1];



?>
</html>
