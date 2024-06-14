<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "environmentaldata";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "";

// $ir_value = $mq135_analog_value = $mq135_digital_value = $timestamp = "";

$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if (isset($_POST["ir_value"]) && isset($_POST["mq135_analog_value"]) && isset($_POST["mq135_digital_value"])) {
    $ir_value = $_POST["ir_value"];
    $mq135_analog_value = $_POST["mq135_analog_value"];
    $mq135_digital_value = $_POST["mq135_digital_value"];

    $sql = "INSERT INTO sensordata (ir_value, mq135_analog_value, mq135_digital_value) VALUES (" . $ir_value . "," . $mq135_analog_value . "," . $mq135_digital_value . ")";

    // Execute the SQL query and check if it was successful
    if ($conn->query($sql) === TRUE) {
        echo "Values inserted in MySQL database table.";
    } else {
        // If the query execution failed, print the error
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

?>