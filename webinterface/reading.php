<?php

$conn = mysqli_connect("127.0.0.1", "sensor", "password", "SensorNet");

if (!$conn) {
    echo "Error: Unable to connect to MySQL." . PHP_EOL;
    echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
    echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
    exit;
}

//lets sanitize the GET variables.

$sensorid = mysqli_real_escape_string($conn, $_GET['sensorid']);
$value = mysqli_real_escape_string($conn, $_GET['value']);

$sql = "SELECT sensorid, sensortype FROM sensors where sensorid = '$sensorid'";
$result = mysqli_query($conn, $sql);
$rows = mysqli_num_rows($result);

if($rows==1)
{
	echo "real sensor. ";
	$row = mysqli_fetch_array($result, MYSQLI_ASSOC);
	$sensortype = $row['sensortype'];
	echo "storing data in database. ";
	$sql = "INSERT INTO `readings` ( `sensorid`, `readingtype`, `datetime`, `reading`)
		VALUES ( '$sensorid', '$sensortype', CURRENT_TIMESTAMP, '$value');";
	$result = mysqli_query($conn, $sql);
	//reading complete.
}
else
{
	//there isn't a sensor with id....
	echo "try again sensor: ".$sensorid;
}



mysqli_close($conn);
?>
