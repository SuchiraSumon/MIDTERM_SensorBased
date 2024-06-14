#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Lenovo Tab";
const char* password = "abcde123";
const char* serverUrl = "http://192.168.39.60/MidTerm/data.php"; // Replace with your server URL

#define IR_SENSOR_PIN D1
#define MQ135_AO_PIN A0
#define MQ135_DO_PIN D2
#define LED_PIN D5

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(MQ135_AO_PIN, INPUT);
  pinMode(MQ135_DO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read IR sensor value
  int irValue = digitalRead(IR_SENSOR_PIN);
  irValue = !irValue; // Invert irValue (0 becomes 1, and 1 becomes 0)

  // Read MQ135 sensor values
  int mq135AnalogValue = analogRead(MQ135_AO_PIN);
  int mq135DigitalValue = digitalRead(MQ135_DO_PIN);

  // Prepare data to send to PHP script
  String postData = "ir_value=" + String(irValue) +
                    "&mq135_analog_value=" + String(mq135AnalogValue) +
                    "&mq135_digital_value=" + String(mq135DigitalValue);

  // Send HTTP POST request to PHP script
  HTTPClient http;
  WiFiClient wclient;
  http.begin(wclient, serverUrl); // Replace with your PHP script URL
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData); // Send the actual POST request
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString(); // Get the response from the server
    Serial.println(response); // Print the response
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end(); // Free resources
  delay(10000); // Delay between readings
}