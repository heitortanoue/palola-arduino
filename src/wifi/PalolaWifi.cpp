#include "PalolaWifi.h"

ESP8266WiFiMulti WiFiMulti;
const char fingerprint[] PROGMEM = "44 60 CD A9 32 C1 0C F3 82 97 9A 68 50 1F BB DB 2B 12 B4 6E";

PalolaWifi::PalolaWifi() {
}

boolean PalolaWifi::isConnected () {
    return (WiFiMulti.run() == WL_CONNECTED);
}

void PalolaWifi::connectToWifi() {
    if (this->isConnected()) {
        return;
    }
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
}

// makes a post request to 'finishmeal' with body {id, status, weight}
void PalolaWifi::finishMeal(Meal meal, float weight) {
    Serial.println("[FUNCTION] finishMeal");
    if (!this->isConnected()) {
        Serial.println("Not connected to WiFi");
        return;
    }

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient http;

    if (http.begin(*client, "https://palola.vercel.app/api/finishmeal")){
        Serial.println("HTTPClient began");
    }

    http.addHeader("Content-Type", "application/json");
    http.addHeader("authorization", SECRET_SERVER_AUTH_KEY);

    DynamicJsonDocument postDoc(1024);
    postDoc["id"] = meal.id;
    postDoc["status"] = meal.status;
    postDoc["weight"] = weight;

    Serial.println("Posting to finish meal...");
    String body;
    serializeJson(postDoc, body);
    int httpCode = http.POST(body);
    Serial.println((String) "Finished meal, status: " + (String) httpCode);

    if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
        String payload = http.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        Serial.println((String) "Got response: " + (String) doc["status"]);

        if (httpCode != 200 || doc["status"] != "sucess") {
            Serial.println("Failed requisition");
            Serial.println("Message: " + (String) doc["message"]);
        }
    }
    else {
        Serial.println((String) "Failed to finish meal, status code: " + (String) httpCode);
    }

    http.end();
}

Meal PalolaWifi::getPendingMeal() {
    Serial.println("[FUNCTION] getPendingMeal");
    if (!this->isConnected()) {
        Serial.println("Not connected to WiFi");
        return {
            .status = MEAL_STATUS_REJECTED
        };
    }

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient http;

    if (http.begin(*client, "https://palola.vercel.app/api/pendingmeals")){
        Serial.println("HTTPClient began");
    }

    http.addHeader("Content-Type", "application/json");
    http.addHeader("authorization", SECRET_SERVER_AUTH_KEY);

    Serial.println("Getting pending meal...");
    int httpCode = http.GET();
    Serial.println((String) "Made connection, status: " + (String) httpCode);

    if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
        String payload = http.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        Serial.println((String) "Got response: " + (String) doc["status"]);

        if (httpCode != 200 || doc["status"] != "sucess") {
            Serial.println("Failed requisition, status: " + (String) doc["status"]);
            if (doc["message"]) {
                Serial.println("Message: " + (String) doc["message"]);
            }
            http.end();
            return {
                .status = MEAL_STATUS_REJECTED
            };
        }

        Meal meal = {};
        meal.id = doc["id"];
        meal.foodQuantity = (float) doc["foodQuantity"];
        meal.status = MEAL_STATUS_PENDING;
        Serial.println((String) "Got pending meal, id: " + (String) meal.id);

        http.end();

        return meal;
    }
    else {
        Serial.println((String) "Failed to get pending meal, status code: " + (String) httpCode);
        http.end();
        return {
            .status = MEAL_STATUS_REJECTED
        };
    }
}