#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer server(80);
StaticJsonDocument<1024> jsonDocument;
char buffer[1024];

void handlePost() {
    if (server.hasArg("plain") == false) {
        //handle error here
    }
    String body = server.arg("plain");
    deserializeJson(jsonDocument, body);

    // Get RGB components
    float led1Status = jsonDocument["led1Status"];
    float led2Status = jsonDocument["led2Status"];

    Serial.println(led1Status);
    Serial.println(led2Status);


    // Respond to the client
    server.send(200, "application/json", "{}");
}

void createJson(const String& name, float value, const String& unit) {
    jsonDocument.clear();
    jsonDocument["name"] = name;
    jsonDocument["value"] = value;
    jsonDocument["unit"] = unit;
    serializeJson(jsonDocument, buffer);
}

void addJsonObject(const String &name, float value, const String &unit) {
    JsonObject obj = jsonDocument.createNestedObject();
    obj["name"] = name;
    obj["value"] = value;
    obj["unit"] = unit;
}

void getValues() {
    Serial.println("Get all values");
    jsonDocument.clear(); // Clear json buffer
    addJsonObject("temperature", 22, "°C");
    addJsonObject("humidity", 80, "%");
    addJsonObject("led1Status", 0, "%");
    addJsonObject("led2Status", 0, "boolean");

    serializeJson(jsonDocument, buffer);
    server.send(200, "application/json", buffer);
}

void sayHello() {
    Serial.println("Hello!");
    jsonDocument.clear(); // Clear json buffer
    addJsonObject("temperature", 22, "°C");
    serializeJson(jsonDocument, buffer);
    server.send(200, "application/json", buffer);
}

void setupApi() {
    server.on("/", sayHello);
    server.on("/getValues", getValues);
    server.on("/setStatus", HTTP_POST, handlePost);

    // start server
    server.begin();
}

#include <Domain.hpp>
#include <WifiConnect.hpp>

void setup() {
    Serial.begin(115200);
    delay(1500);

    connectWifi();

    updateDomain();

    setupApi();

}

void loop() {
    server.handleClient();
}