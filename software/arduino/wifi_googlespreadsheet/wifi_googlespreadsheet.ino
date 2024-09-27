#include <WiFi.h>
#include <HTTPClient.h>
//Wi-Fi

const char* ssid     = "RDlab_24"; //Your SSID
const char* password = "e2iz6uvd"; //Your Password

//Google Spreadsheet
// const String url = "https://script.google.com/macros/s/AKfycbzGz0BU80cTa-HkQcWN8ebx2G8M3c6p-Se7q7R_0S1iLWMLQ3W9fC_F-W_Gqbvmp_Lz/exec";
const String url = "https://script.google.com/macros/s/AKfycbwjv2X7s-WY6P5Ypoos1aDCDTsAMG6mDoTnEoM1VBDtdutNeSM53f4SP8kWOpmWGkk-/exec";


int id = 0;         //コースターID
float weight = 0.0; //コースターの重さ

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
  id = random(0, 5);
  weight = random(0, 100);

  Serial.print("id: ");
  Serial.print(id);
  Serial.print("\t");
  Serial.print("weight: ");
  Serial.print(weight);
  Serial.println("g");

  // Google SpreadSheet
  String url_result = url + "?id=" + String(id) + "&weight=" + String(weight);
  Serial.println(url_result);

  HTTPClient http;
  http.begin(url_result.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);

  // getting response from google sheet
  String payload;
  if(httpCode > 0){
    payload = http.getString();
    Serial.println("payload: " + payload);
  }
  http.end();

  delay(2000);
}