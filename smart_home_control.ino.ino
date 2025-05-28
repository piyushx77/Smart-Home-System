#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h> // Needed for tone()

// Replace with your WiFi credentials
const char* ssid = "GESTURE";
const char* password = "123456789";

// Web server on port 80
ESP8266WebServer server(80);

// Pin Definitions
const int ledPins[3] = {D1, D2};
const int btnPins[3] = {D5, D6, D7};
const int buzzerPin = D3;
const int buzzerBtnPin = D8;

// State tracking
bool ledStates[3] = {false, false, false};
bool buzzerState = true;

void setup() {
  Serial.begin(115200);

  // Pin setup
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(btnPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerBtnPin, INPUT_PULLUP);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected. IP: " + WiFi.localIP().toString());

  // Web Routes
  server.on("/", handleRoot);

  // LED toggle routes
  for (int i = 0; i < 3; i++) {
    server.on(("/toggleLED" + String(i)).c_str(), [i]() {
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i]);
      server.sendHeader("Location", "/", true);
      server.send(302, "text/plain", "");
    });
  }

  // Buzzer toggle route
  server.on("/toggleBuzzer", []() {
    buzzerState = !buzzerState;
    if (buzzerState) {
      tone(buzzerPin, 1000);  // 1kHz tone
    } else {
      noTone(buzzerPin);
    }
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();

  // Physical button handling for LEDs
  for (int i = 0; i < 3; i++) {
    if (digitalRead(btnPins[i]) == LOW) {
      delay(200); // Debounce
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i]);
    }
  }

  // Buzzer push button handling
  if (digitalRead(buzzerBtnPin) == HIGH) {
    delay(200); // Debounce
    buzzerState = buzzerState;
    if (buzzerState) {
      tone(buzzerPin, 1000);  // Start buzzer
    } else {
      noTone(buzzerPin);      // Stop buzzer
    }
  }
}

void handleRoot() {
  String html = "<html><head><title>Home Control</title></head><body>";
  html += "<h2>Web Control Panel</h2>";
  html += "<p><a href='/toggleLED0'><button>Toggle LED 1</button></a></p>";
  html += "<p><a href='/toggleLED1'><button>Toggle LED 2</button></a></p>";
  html += "<p><a href='/toggleLED2'><button>Toggle Buzzer</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
} 