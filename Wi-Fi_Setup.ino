#include <WiFi.h>

const char* ssid     = "hidetosh-2.4"; //角部屋のWi-Fiのやつなので今後変更予定あり
const char* password = "inaina117J1N"; //角部屋のWi-Fiのやつなので今後変更予定あり

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop(){
}