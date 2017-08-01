<?php
    $con = mysqli_connect("localhost", "id1779424_espmesh", "espmesh", "id1779424_espmesh");
    
    $type = $_GET['type'];
    $chip = $_GET['chip'];
    $moisture = $_GET['moisture'];
    $gas = $_GET['gas'];
    $humidity = $_GET['humidity'];
    $temp = $_GET['temp'];
    $smoke = $_GET['smoke'];
    $time =  date('j-n-Y-H');
    settype($time, "string");

    $statement = mysqli_prepare($con, "SELECT time FROM mesh WHERE chip = ?");
    mysqli_stmt_bind_param($statement, "s", $chip);
    mysqli_stmt_execute($statement);

    mysqli_stmt_store_result($statement);
    mysqli_stmt_bind_result($statement, $time1);
    
    $response1 = array();
    while(mysqli_stmt_fetch($statement)){
        $response1["success1"] = true;
        $response1["time2"] = $time1; 
    }
    
    if ((string)$response1["time2"] == $time) {
    
        $statement = mysqli_prepare($con, "UPDATE mesh SET type = ?, moisture = ?, gas = ?, humidity = ?, temp = ?, smoke = ? WHERE chip = ? and time = ?");
        mysqli_stmt_bind_param($statement, "ssssssss",$type, $moisture, $gas, $humidity, $temp, $smoke, $chip,$time);
        mysqli_stmt_execute($statement);
    } else {

        $statement = mysqli_prepare($con, "INSERT INTO mesh (time, type, chip, moisture, gas, humidity, temp, smoke) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        mysqli_stmt_bind_param($statement, "ssssssss",$time, $type, $chip, $moisture, $gas, $humidity, $temp, $smoke);
        mysqli_stmt_execute($statement);

    }

    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>