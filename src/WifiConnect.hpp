#include <WiFiManager.h>

const int selected = 3;
const char *ssid[] = {"Oneplus 6", "AndroidAP", "TP-Link_DC90", "KossuthNet"};
const char *password[] = {"Lacika007", "Nagyponty21", "53745309", "InterNyet17"};

static void connectWifi() {

    WiFiClass::hostname("Csonak_ESP");
    WiFiClass::mode(WIFI_STA);

    WiFiManager wm;
    bool res = wm.autoConnect("KossuthNet", "InterNyet17"); // password protected ap
    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    }
    else {
        Serial.println("Connected!");
    }

    // WiFi.setAutoConnect(true);
    // WiFi.begin(ssid[selected], password[selected]);
    // Serial.print("Connecting...");
    // while (WiFiClass::status() != WL_CONNECTED) {
    //     Serial.print(".");
    //     delay(1000);
    // }


    IPAddress gateWay = WiFi.gatewayIP();
    //long rssi = WiFi.RSSI();
    Serial.print("\nMyName: ");
    Serial.println(WiFiClass::getHostname());
    Serial.print("local IP: ");
    Serial.println(WiFi.localIP().toString());
    Serial.print("Csatlakozva: ");
    Serial.println(ssid[selected]);
}
