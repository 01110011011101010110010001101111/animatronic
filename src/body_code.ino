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

const int DIR = 12;
const int STEP = 14;
const int  steps_per_rev = 50;

WebServer server(80);

void cw() {
  digitalWrite(DIR, HIGH);
  for(int i = 0; i<steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  }

}

void ccw() {
  digitalWrite(DIR, LOW);
  for(int i = 0; i<steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
  }
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

  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);


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
  server.on("/body/up", cw);
  server.on("/body/down", ccw);

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
