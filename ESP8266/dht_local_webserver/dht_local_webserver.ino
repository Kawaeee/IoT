//dht_local_webserver = DHT11 temperature and humidity + ESP8266 webserver
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

// define pin and dht type
#define DHTPIN D2
#define DHTTYPE DHT11

// define access point
#ifndef APSSID
#define APSSID "Kawae_AP"
#define APPSK  "11111111"
#endif

// define ssid,password
const char *ssid = APSSID;
const char *password = APPSK;

float temp;
float humid;
String ledState = "OFF";

DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Kawae Access Point + DHT11");

  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  // default as off
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Access Point -> IP address: ");
  Serial.println(myIP);

  server.on("/", handle_OnConnect);
  // led state
  server.on("/LED=on", handleLEDon);
  server.on("/LED=off", handleLEDoff);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  temp = dht.readTemperature(); // read temperature.
  humid = dht.readHumidity(); // read humidity
  server.send(200, "text/html", renderPage(temp, humid, ledState));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void handleLEDon() {
  ledState = "ON";
  temp = dht.readTemperature(); // read temperature.
  humid = dht.readHumidity(); // read humidity
  digitalWrite(LED_BUILTIN, LOW); //LED on
  server.send(200, "text/html", renderPage(temp, humid, ledState));
}

void handleLEDoff() {
  ledState = "OFF";
  temp = dht.readTemperature(); // read temperature.
  humid = dht.readHumidity(); // read humidity
  digitalWrite(LED_BUILTIN, HIGH); //LED off
  server.send(200, "text/html", renderPage(temp, humid, ledState));
}

// main page
String renderPage(float temp, float humid, String ledState) {

  String contents = "<!DOCTYPE html> <html>\n";

  // header
  contents += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  contents += "<title>Kawae DHT11 Station</title>\n";
  contents += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  contents += "body{margin-top: 50px;} h1 {color: #ffffff;margin: 50px auto 30px;}\n";
  contents += "p {font-size: 24px;color: #ffffff;margin-bottom: 10px;}\n";

  contents += "</style>\n</head>\n<body style=\"background-color:grey;\">\n";

  contents += "<h1>Kawae DHT11 Station</h1>\n";

  contents += "<p>Temperature: ";
  contents += temp;
  contents += " *C</p>";

  contents += "<p>Humidity: ";
  contents += humid;
  contents += " %</p>";

  contents += "<p>NodeMCU LED State: ";
  contents += ledState;
  contents += " </p>";
  contents += "<a href=\"/LED=on\"><button type=\"button\">Turn on</button></a>&nbsp;&nbsp;";
  contents += "<a href=\"/LED=off\"><button type=\"button\">Turn off</button></a>";

  contents += "</body>\n</html>\n";

  return contents;
}
