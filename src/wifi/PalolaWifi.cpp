#include "PalolaWifi.h"

ESP8266WiFiMulti WiFiMulti;
const char fingerprint[] PROGMEM = "44 60 CD A9 32 C1 0C F3 82 97 9A 68 50 1F BB DB 2B 12 B4 6E";

PalolaWifi::PalolaWifi() {
}

boolean PalolaWifi::isConnected () {
    return (WiFiMulti.run() == WL_CONNECTED);
}

void PalolaWifi::connectToWifi() {
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
}

void PalolaWifi::startMeal() {

}

void PalolaWifi::finishMeal(MealStatus status) {

}

Meal PalolaWifi::getPendingMeal() {
    HTTPClient* http = this->_startClient();
    if (http == nullptr) {
        return {};
    }

    int httpCode = (*http).GET();

    if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
        String payload = (*http).getString();
        Serial.println(httpCode);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);

        Meal meal = {};
        meal.group = doc["group"];
        meal.id = doc["id"];
        meal.status = -1;

        (*http).end();
        delete http;

        return meal;
    }
    else {
        Serial.println(httpCode);
        Serial.println("Falha na requisição");

        (*http).end();
        delete http;

        return {};
    }
}

HTTPClient* PalolaWifi::_startClient() {
    if (!this->isConnected()){
        Serial.println("Falha na conexão");
        return nullptr;
    }

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);
    Serial.println("connected...");

    HTTPClient* http = new HTTPClient();

    (*http).begin(*client, (String) SERVER_URL + "pendingmeal");

    (*http).addHeader("Content-Type", "application/json");
    (*http).addHeader("Authorization", SECRET_SERVER_AUTH_KEY);

    return http;
}