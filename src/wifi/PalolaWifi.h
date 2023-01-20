#ifndef __PALOLA_WIFI_H__
#define __PALOLA_WIFI_H__

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include "../../Secrets.h"
#include "../../Types.h"

#define SERVER_URL "https://palola.vercel.app/api/"

class PalolaWifi {
    public:
        PalolaWifi();

        void connectToWifi();
        boolean isConnected();

        Meal getPendingMeal();
        void finishMeal(Meal meal, float weight);
    private:

};

#endif