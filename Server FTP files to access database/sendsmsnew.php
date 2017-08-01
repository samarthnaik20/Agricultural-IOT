<?php
$number = $_GET["number"];
$status = $_GET["status"];
$servername = "localhost";
$username = "id1779424_espmesh";
$password = "espmesh";
$dbname = "id1779424_espmesh";

settype($status,"string");

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT message FROM smsinfo WHERE status='{$status}' and number='{$number}'";
$result = $conn->query($sql);

$response = array();

$s2 = "nan";
$response[$s2] = "0";
if ($result->num_rows > 0) {
    // output data of each row
    $i = 1;
    while($row = $result->fetch_assoc()) {
        
        $j = (string)$i;
       
        $s2 = "m" . $j;
        
        
       
        $response[$s2] = $row["message"];
       
        
        $i = $i + 1;
    }
} else {
    
    $response[$s2] = "nan";
}

echo ($response[$s2]);
$conn->close();
?>