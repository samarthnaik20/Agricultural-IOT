<?php
    $con = mysqli_connect("localhost", "id1779424_espmesh", "espmesh", "id1779424_espmesh");
    
    $number = $_GET['number'];
    $message = $_GET['message'];
    $status = $_GET['status'];
    $time =  date('j-n-Y-H:i:s');
    settype($time, "string");

    $statement = mysqli_prepare($con, "INSERT INTO smsinfo (number,message,status,time) VALUES (?, ?, ?, ?)");
    mysqli_stmt_bind_param($statement, "ssss",$number,$message,$status,$time);
    mysqli_stmt_execute($statement);

    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>