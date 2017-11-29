<?php

  /* 2Captcha API sample implementation for PHP:cURL
  *   
  *  Please note that 2Captcha does not support remote captcha image retrieval
  *  as in some cases it can invalidate the previously issued captcha/
  *  You need to save the image that the captcha server sent to your client and pass it on without modifications.
  *
  *  Main arguments:
  *
  *  (string) $filename     -  Local path to the image that you received and will be sending on
  *  (string) $apikey       -  Your API key 
  *     (int) $rtimeout     -  Time in seconds to wait before polling 2Captcha's servers again
  *     (int) $mtimeout     -  Time in seconds to wait before giving up all hope
  *    (bool) $is_verbose   -  TRUE for increased verbosity/logging, FALSE for silent (default)
  *
  *    Additional captcha-related arguments:
  *
  *     (bool) $is_phrase    -  TRUE if the captcha image contains two words or more;
  *                             FALSE if one word or numbers only
  *
  *     (bool) $is_regsense  -  TRUE if the captcha is case-sensitive
  *                             FALSE if not
  *      (int) $is_numeric   -  0 (default) setting not applicable
  *                             1 - captcha contains numbers only
  *                             2 - captcha contains letters only
  *                             3 - captcha may be alphanumeric
  *
  *      (int) $min_len      -  if unset or 0 (default), argument not applicable; otherwise sets minimum answer length
  *      (int) $max_len      -  if unset or 0 (default), argument not applicable; otherwise sets maximum answer length
  *      (int) $language     -  if unset or 0, parameter not applicable (default)
  *                             1 - answer may contain non-ASCII entities (Cyrillic)
  *                             2 - answer not expected to contain non-ASCII entities (alphanumeric)  
  * 
  *  Usage examples:
  *
  *     $text = recognize("captcha.jpg", $apikey);
  *
  *     $text = recognize("/path/to/file/captcha.jpg", $apikey, TRUE);
  *  
  *     $text = recognize("/path/to/file/captcha.jpg", $apikey, FALSE, 1, 10, 0, 5);
  *  
  */


  function recognize($filename, $apikey, $is_verbose = FALSE, $rtimeout = 5, $mtimeout = 120, $is_phrase = 0, $is_regsense = 1, $is_numeric = 0, $min_len = 0, $max_len = 0, $language = 0)
    {


    /* This seems to be the most universally accepted method for determinining whether we have a legit image */

     if(@is_array(getimagesize($filename))){
        $is_valid_image = TRUE;
           } else {
        if($is_verbose) 
           echo "File $filename not found or not an image\n";
        return($is_valid_image = FALSE);
     }

      $postdata = array(
          'method' => 'POST',
          'key' => $apikey,
          'file' => new CurlFile($filename, mime_content_type($filename), 'file'),
          'phrase' => $is_phrase,
          'regsense' => $is_regsense,
          'numeric' => $is_numeric,
          'min_len' => $min_len,
          'max_len' => $max_len,
          'language' => $language
      );
      $ch            = curl_init();
      curl_setopt($ch, CURLOPT_URL, "http://2captcha.com/in.php");
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($ch, CURLOPT_TIMEOUT, 60);
      curl_setopt($ch, CURLOPT_POST, 1);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $postdata);
      $result        = curl_exec($ch);
      if (curl_errno($ch))
        {
          if ($is_verbose)
              echo "CURL returned error: " . curl_error($ch) . "\n";
          return FALSE;
        }
      curl_close($ch);
      if (strpos($result, "ERROR") !== FALSE)
        {
          if ($is_verbose)
              echo "Server returned error: $result\n";
          return FALSE;
        }
      else
        {
          $ex         = explode("|", $result);
          $captcha_id = $ex[1];
          if ($is_verbose)
              echo "Captcha sent, got captcha ID $captcha_id\n";
          $waittime = 0;
          if ($is_verbose)
              echo "Waiting for $rtimeout seconds and trying again\n";
          sleep($rtimeout);
          while (TRUE)
            {
              $result = file_get_contents("http://2captcha.com/res.php?key=" . $apikey . '&action=get&id=' . $captcha_id);
              if (strpos($result, 'ERROR') !== FALSE)
                {
                  if ($is_verbose)
                      echo "Server returned error: $result\n";
                  return FALSE;
                }
              if ($result == "CAPCHA_NOT_READY")
                {
                  if ($is_verbose)
                      echo "Captcha not yet ready\n";
                  $waittime += $rtimeout;
                  if ($waittime > $mtimeout)
                    {
                      if ($is_verbose)
                          echo "Out of time: $mtimeout seconds reached\n";
                      break;
                    }
                  if ($is_verbose)
                      echo "Waiting for another $rtimeout seconds...\n";
                  sleep($rtimeout);
                }
              else
                {
                  $ex = explode('|', $result);
                  if (trim($ex[0]) == 'OK')
                      return trim($ex[1]);
                }
            }
          return FALSE;
        }
    }
?>
