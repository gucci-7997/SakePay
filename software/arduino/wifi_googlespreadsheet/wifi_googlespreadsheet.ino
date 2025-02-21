#include <WiFi.h>
#include <HTTPClient.h>
//Wi-Fi

const char* ssid     = ""; //Your SSID
const char* password = ""; //Your Password

//Google Spreadsheet
// const String url = "";
const String url = "";


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
