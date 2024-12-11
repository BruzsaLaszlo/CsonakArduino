#include <HTTPClient.h>

static void updateDomain(){

        HTTPClient http;

        String serverPath = "https://httpbin.org/ip";

        // Your Domain name with URL path or IP address with path
        http.begin(serverPath.c_str());

        // If you need Node-RED/server authentication, insert user and password below
        //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode>0) {
            deserializeJson(jsonDocument, http.getString());
            String ip = jsonDocument["origin"];
            Serial.print("Ip: ");
            Serial.println(ip);
        }
        else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();

}
