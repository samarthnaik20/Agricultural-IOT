<?php
    $con = mysqli_connect("localhost", "id1779424_espmesh", "espmesh", "id1779424_espmesh");
    
    $number = $_GET['number'];
    $status = "sent";

    $statement = mysqli_prepare($con, "UPDATE smsinfo SET status = ? WHERE number = ?");
    mysqli_stmt_bind_param($statement, "ss",$status, $number);
    mysqli_stmt_execute($statement);
  
    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>