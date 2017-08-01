<?php
    $con = mysqli_connect("localhost", "id1779424_espmesh", "espmesh", "id1779424_espmesh");

    $statement = mysqli_prepare($con, "TRUNCATE TABLE  mesh");
    mysqli_stmt_execute($statement);
  
    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>