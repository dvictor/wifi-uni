#include <Arduino.h>
#include <Hash.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

int n = 0;

void event(const char * payload, size_t length) {
  //USE_SERIAL.printf("got message: %s\n", payload);
  char buff[50];
  sprintf(buff, "%i", n);
  webSocket.emit("event-a", buff);
  n++;
}

void setup() {
    USE_SERIAL.begin(115200);

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("SecuniA-2G", "!Lego2Secunia!");


    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.on("event", event);
    webSocket.begin("10.0.0.119", 8005);
}

void loop() {
    webSocket.loop();
}
