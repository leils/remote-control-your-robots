#include "secrets.h"
//#include <WiFi.h> // for ESP32
#include <WiFiNINA.h>  //for Nano IOT 33
#include <WiFiUdp.h>

#include <OSCMessage.h>
OSCErrorCode error;

// Define these in secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiUDP Udp;
const unsigned int localPort = 8080;  // local port to listen for UDP packets (here's where we send the packets)

void setup() {
  //-------------------------- Serial Setup -----------------//
  Serial.begin(115200);
  // We need to make sure we have the serial ready
  // so we can read the connected port
  if (!Serial) delay(3000);

  //-------------------------- I/O Setup -------------------//

  pinMode(LED_BUILTIN, OUTPUT);

  //-------------------------- Connect to WiFi Network ----//
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { // Wait until connected to the WiFi
    delay(300);
    Serial.print(".");
  }
  Serial.println("");

  // Print network connection to serial
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");

  Serial.println(localPort);
}

void loop() {
  //----------------------------------- Handle incoming OSC Messages -----------------//
  OSCMessage msg;
  int size = Udp.parsePacket(); // Get what size the OSC packet is

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read()); // Read the entire packet
    }
    if (!msg.hasError()) {
      msg.dispatch("/ping", ping); // For any messages in the "ping" channel, use our "ping" function
    } else {
      error = msg.getError();
      Serial.print("OSC error: ");
      Serial.println(error);
    }
  }
}

// Handles OSC messages from the ping channel
void ping(OSCMessage &msg) {
  Serial.println("ping received");
}
