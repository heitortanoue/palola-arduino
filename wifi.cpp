// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <ESP8266WiFiMulti.h>
// #include <WiFiClientSecureBearSSL.h>
// #include <Wire.h>
// #include <WiFiClient.h>
// #include "ArduinoJson.h"
// #include "Secrets.h"

// ESP8266WiFiMulti WiFiMulti;
// const char fingerprint[] PROGMEM = "44 60 CD A9 32 C1 0C F3 82 97 9A 68 50 1F BB DB 2B 12 B4 6E";
// char json[400] = {0};
// StaticJsonDocument<256> doc;

// // Replace with the URL of the server you want to send the request to
// const char* serverUrl = "https://palola.vercel.app/api/mealgroups";

// void setup() {
//   //1 - Para testar, vamos usar a serial
//   Serial.begin(9600);

//   //2 - iniciamos a conexão WiFi...
//   WiFi.mode(WIFI_STA);
//   WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

//   //3 - acesse arduinojson.org/v6/assistant e passe uma amostra pra calcular a capacidade
//   const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(8) + 146;
//   DynamicJsonDocument doc(capacity);

// }

// void loop() {
//   Serial.println("loop started...");
//         if ((WiFiMulti.run() == WL_CONNECTED)){
//           std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
//           client->setFingerprint(fingerprint);
//           Serial.println("connected...");
//           //WiFiClient client;

//           HTTPClient http;

//         //3 - iniciamos a URL alvo, pega a resposta e finaliza a conexão
//         if (http.begin(*client, serverUrl)){
//           Serial.println("http.begin ok");
//         }

//         http.addHeader("Content-Type", "application/json");
//         http.addHeader("authorization", SERVER_AUTH_KEY);
//         int httpCode = http.GET();
        
//         if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
//             String payload = http.getString();
//             Serial.println(httpCode);
//             Serial.println(payload);
//             //resultOfGet(payload);
//         }
//         else {
//           Serial.println(httpCode);
//             Serial.println("Falha na requisição");
//         }
//         http.end();
//         }
//         delay(20000);
// }
