<?php

$list   = get_defined_constants(TRUE);
$list   = preg_grep('/^CURLE_/', array_flip($list['curl']));
$result = array();

foreach ($list as $const) {
    $result[$const] = array
    (
        'code'    => constant($const),
        'message' => curl_strerror(constant($const))
    );
}

echo "<pre>";
echo print_r($result, TRUE);
echo "</pre>";
