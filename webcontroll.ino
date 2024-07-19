#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "RJ-2022";
const char* password = "RJ989898";

WebServer server(80);

// Define the servo
Servo myservo;

// Define the servo pin
const int servoPin = 18;

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Servo Control</h1>";
  html += "<div style='text-align:center;'>";
  html += "<button onclick=\"fetch('/forward').then(response => response.text()).then(text => document.getElementById('status').innerHTML = text);\">Forward</button>";
  html += "<button onclick=\"fetch('/back').then(response => response.text()).then(text => document.getElementById('status').innerHTML = text);\">Back</button>";
  html += "<button onclick=\"fetch('/stop').then(response => response.text()).then(text => document.getElementById('status').innerHTML = text);\">Stop</button>";
  html += "<p id='status'></p>";
  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void moveServo(int angle) {
  myservo.attach(servoPin);
  myservo.write(angle);
  delay(1000); // Allow time for the servo to reach the position
  myservo.detach(); // Detach the servo to stop it from holding the position
}

void handleForward() {
  moveServo(10); // Move the servo forward by 10 degrees
  server.send(200, "text/plain", "Moved Forward");
}

void handleBack() {
  moveServo(170); // Move the servo backward by 10 degrees
  server.send(200, "text/plain", "Moved Back");
}

void handleStop() {
  myservo.detach(); // Detach the servo to stop it
  server.send(200, "text/plain", "Servo Stopped");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/back", handleBack);
  server.on("/stop", handleStop);

  server.begin();
}

void loop() {
  server.handleClient();
}
