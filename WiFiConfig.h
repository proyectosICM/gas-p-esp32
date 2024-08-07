#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "Config.h"

void setupWiFi();
WiFiServer& getServer();

#endif