#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "mpu.h"
#include "sensor.h"

void handleRoot() ;

void setupWebServer();

void handleWebServer();

boolean wifiConnected();