#include "secrets.h"
#include <WiFi.h>
#include <WiFiUdp.h>

//Define these in secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiUDP Udp;
const unsigned int localPort = 8080;  // local port to listen for UDP packets (here's where we send the packets)

void setup() {
  //-------------------------- Serial Setup
  Serial.begin(115200);
  // We need to make sure we have the serial ready
  // so we can read the connected port
  if (!Serial) delay(3000);

  //-------------------------- I/O Setup

  pinMode(LED_BUILTIN, OUTPUT);

  //-------------------------- Connect to WiFi Network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { //Wait until connected to the WiFi
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");

  Serial.println(localPort);
}

void loop() {
}
