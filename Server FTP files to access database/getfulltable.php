<?php

$servername = "localhost";
$username = "id1779424_espmesh";
$password = "espmesh";
$dbname = "id1779424_espmesh";


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT time, type, chip, moisture,gas,humidity,temp,smoke FROM mesh";
$result = $conn->query($sql);

$response = array();
$response["rows"] = $result->num_rows;


if ($result->num_rows > 0) {
    // output data of each row
    $i = 1;
    while($row = $result->fetch_assoc()) {
        
        $j = (string)$i;
        $s0 = "time" . $j;
        $s1 = "type" . $j;
        $s2 = "chip" . $j;
        $s3 = "moisture" . $j;
        $s4 = "gas" . $j;
        $s5 = "humidity" . $j;
        $s6 = "temp" . $j;
        $s7 = "smoke" . $j;

        $response[$s0] = $row["time"];        
        $response[$s1] = $row["type"];
        $response[$s2] = $row["chip"];
        $response[$s3] = $row["moisture"];
        $response[$s4] = $row["gas"];
        $response[$s5] = $row["humidity"];
        $response[$s6] = $row["temp"];
        $response[$s7] = $row["smoke"];
        
        $i = $i + 1;
    }
} else {
    $response["rows"] = 0;
}

echo json_encode($response);
$conn->close();
?>