#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RELAY_PIN   4   // D2 - przekaźnik Power SW
#define STATUS_PIN  5   // D1 - odczyt Power LED

const char* ssid = "WPISZ NAZWE SIECI WIFI";
const char* password = "WPISZ HASLO DO SIECI WIFI";

ESP8266WebServer server(80);

bool isPCOn() {
  return digitalRead(STATUS_PIN) == LOW;
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(STATUS_PIN, INPUT);

  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print(F("Łączenie z: "));
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\nPołączono!"));
  Serial.print(F("IP: http://"));
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/power", handlePower);
  server.begin();

  Serial.println(F("Serwer uruchomiony"));
}

void handleRoot() {
  String html = F(
    "<!DOCTYPE html>"
    "<html lang='pl'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>ESP8266 Remote Power</title>"
    "<style>"
    "body {"
    "  font-family: 'Segoe UI', Arial, sans-serif;"
    "  background: linear-gradient(135deg, #0f0f1e, #1a1a2e);"
    "  color: #eee;"
    "  margin: 0;"
    "  min-height: 100vh;"
    "  display: flex;"
    "  justify-content: center;"
    "  align-items: center;"
    "}"
    ".container {"
    "  text-align: center;"
    "}"
    "h1 {"
    "  color: #00d4ff;"
    "  margin-bottom: 10px;"
    "  font-size: 1.8em;"
    "}"
    ".subtitle {"
    "  color: #888;"
    "  margin-bottom: 35px;"
    "  font-size: 1.1em;"
    "}"
    "button {"
    "  font-size: 1.3em;"
    "  padding: 16px 40px;"
    "  margin: 12px;"
    "  border: none;"
    "  border-radius: 12px;"
    "  cursor: pointer;"
    "  width: 300px;"
    "  transition: all 0.3s;"
    "}"
    ".btn-on { background: #28a745; color: white; }"
    ".btn-on:hover { background: #34c04a; transform: translateY(-3px); }"
    ".btn-off { background: #dc3545; color: white; }"
    ".btn-off:hover { background: #e44a5b; transform: translateY(-3px); }"
    ".btn-refresh { background: #0a84ff; color: white; }"
    ".info {"
    "  margin-top: 30px;"
    "  color: #666;"
    "  font-size: 0.95em;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<div class='container'>"
    "<h1>ESP8266 Remote Power Switch</h1>"
    "<p class='subtitle'>Zdalne włączanie komputera</p>"

    "<button class='btn-on' onclick=\"sendCommand('short')\">Włącz</button><br>"
    "<button class='btn-off' onclick=\"sendCommand('long')\">Wymuś wyłączenie (5 sekund)</button><br>"
    "<button class='btn-refresh' onclick=\"location.reload()\">Odśwież teraz</button>"

    "<div class='info'>Automatyczne odświeżanie co 3 sekundy</div>"

    "</div>"

    "<script>"
    "function sendCommand(action) {"
    "  fetch('/power?action=' + action)"
    "    .then(response => response.text())"
    "    .then(text => {"
    "      alert(text);"
    "      setTimeout(() => location.reload(), 800);"
    "    });"
    "}"
    "setInterval(() => location.reload(), 3000);"
    "</script>"

    "</body>"
    "</html>"
  );

  server.send(200, "text/html", html);
}

void handlePower() {
  String action = server.arg("action");

  if (action == "short") {
    digitalWrite(RELAY_PIN, HIGH);
    delay(400);
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "text/plain", "✓ Wysłano impuls włączenia");
  } 
  else if (action == "long") {
    digitalWrite(RELAY_PIN, HIGH);
    delay(5200);
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "text/plain", "✓ Wymuszony shutdown (5+ sekund)");
  }
}

void loop() {
  server.handleClient();
}