/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "Sonic-8a3e";          // your network SSID (name)
char pass[] = "61e99a0bca";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,42,6);        // remote IP of your computer
const unsigned int outPort = 8000;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

int threshold = 30;
int del = 500;

bool touch3detected = false;
bool touch5detected = false;
bool touch6detected = false;
bool touch7detected = false;
bool touch8detected = false;
bool touch9detected = false;


void gotTouch3() {
  touch3detected = true;
}

void gotTouch5() {
  touch5detected = true;
}

void gotTouch6() {
  touch6detected = true;
}

void gotTouch7() {
  touch7detected = true;
}

void gotTouch8() {
  touch8detected = true;
}

void gotTouch9() {
  touch9detected = true;
}


void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
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
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif

  Serial.println("ESP32 Touch OSC");
  touchAttachInterrupt(T3, gotTouch3, threshold);
  touchAttachInterrupt(T5, gotTouch5, threshold);
  touchAttachInterrupt(T6, gotTouch6, threshold);
  touchAttachInterrupt(T7, gotTouch7, threshold);
  touchAttachInterrupt(T8, gotTouch8, threshold);
  touchAttachInterrupt(T9, gotTouch9, threshold);

}

void loop() {

  if (touch3detected) {
    Serial.println("Touch 3 detected");
    OSCMessage msg("/touch");
    msg.add("/3");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch3detected = false;
  }
  if (touch5detected) {
    OSCMessage msg("/touch");
    msg.add("/5");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch5detected = false;
  }
  if (touch6detected) {
    Serial.println("Touch 6 detected");
    OSCMessage msg("/touch");
    msg.add("/6");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch6detected = false;
  }
  if (touch7detected) {
    Serial.println("Touch 7 detected");
    OSCMessage msg("/touch");
    msg.add("/7");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch7detected = false;
  }
  if (touch8detected) {
    Serial.println("Touch 8 detected");
    OSCMessage msg("/touch");
    msg.add("/8");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch8detected = false;
  }
  if (touch9detected) {
    Serial.println("Touch 9 detected");
    OSCMessage msg("/touch");
    msg.add("/9");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(del);
    touch9detected = false;
  }

  delay(10);

}
