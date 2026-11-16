#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>


// Replace with your network credentials
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

// servo!
Servo eyesServo;
const int eyesOutputPin = 21;
int prevEyesPos = 10;

Servo mouthServo;
const int mouthOutputPin = 22;

Servo candyServo;
const int candyOutputPin = 23;

WebServer server(80);

void eyesQ1() {
  prevEyesPos = 10;
  eyesServo.write(prevEyesPos);
}

void eyesQ2() {
  prevEyesPos = 55;
  eyesServo.write(prevEyesPos);
}

void eyesQ3() {
  prevEyesPos = 100;
  eyesServo.write(prevEyesPos);
}

void eyesQ4() {
  prevEyesPos = 145;
  eyesServo.write(prevEyesPos);
}

void candyClose() {
  candyServo.write(10);
}

void candyOpen() {
  candyServo.write(170);
}

void hoot() {
  mouthServo.write(30);
  delay(100);
  mouthServo.write(90);
  delay(100);
  mouthServo.write(150);
  delay(100);

}

// Ping pong test
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<body><h1>Success!</h1>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  eyesServo.setPeriodHertz(50); // PWM frequency for SG90
  eyesServo.attach(eyesOutputPin, 500, 2400); // Minimum and maximum pulse width (in µs) to go from 0° to 180

  mouthServo.setPeriodHertz(50); // PWM frequency for SG90
  mouthServo.attach(mouthOutputPin, 500, 2400); // Minimum and maximum pulse width (in µs) to go from 0° to 180

  candyServo.setPeriodHertz(50); // PWM frequency for SG90
  candyServo.attach(candyOutputPin, 500, 2400); // Minimum and maximum pulse width (in µs) to go from 0° to 180


  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/eyes/q1", eyesQ1);
  server.on("/eyes/q2", eyesQ2);
  server.on("/eyes/q3", eyesQ3);
  server.on("/eyes/q4", eyesQ4);

  server.on("/candy/open", candyOpen);
  server.on("/candy/close", candyClose);

  // Mouth
  server.on("/mouth/hoot", hoot);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
  // Open this on the web!
  // Serial.println(WiFi.localIP());

}
