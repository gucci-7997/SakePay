#include "HX711.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "RDlab_24"; //Your SSID
const char* password = "e2iz6uvd"; //Your Password

// google spread sheet script
const String url = "https://script.google.com/macros/s/AKfycbwjv2X7s-WY6P5Ypoos1aDCDTsAMG6mDoTnEoM1VBDtdutNeSM53f4SP8kWOpmWGkk-/exec";

// google spread sheet
int id = 0;

// Pin
const int DT_PIN = 32;
const int SCK_PIN = 33;
const int SW_PIN = 0;
const int SA_PIN = 34;
long count = 0;

// init
HX711 scale;
long offset = 587973;
double gradient = 0.0024329871;
double baseWeight = 230.0;

void setup() {
  Serial.begin(115200);

  // connect wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(2000);
      Serial.print(".");
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  // connect pin
  Serial.println("start");
  scale.begin(DT_PIN, SCK_PIN);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(SA_PIN, INPUT_PULLUP);
}

int swLowCount = 0;
void loop() {

  // get weight
  long value = scale.read_average(5);
  double weight = (double)(value - offset) * gradient;
  Serial.printf("weight: %.1f[g]\n", weight );

  if ( digitalRead(SA_PIN) == HIGH ){
    Serial.print("Offset value measuring..."); 
      offset = scale.read_average(50); 
      Serial.printf(" Done. Offset value = %ld\n", offset);
  }  

  if ( digitalRead(SW_PIN) == LOW )
    swLowCount++;
  else
  {
    //short push(2sec) and release is enter the Offset value measuring mode
    if ( swLowCount > 0 && swLowCount < 4) { 
      Serial.print("Offset value measuring..."); 
      offset = scale.read_average(50); 
      Serial.printf(" Done. Offset value = %ld\n", offset);
    }
    //long push(6sec) and release is enter the Gradient value measuring mode
    if ( swLowCount > 6 )
    {
      Serial.print("Gradient value measuring...");
      long baseValue = scale.read_average(50);
      baseValue -= offset;
      gradient = baseWeight / (double)baseValue;
      Serial.printf(" Done. Gradient value = %.10fd\n", gradient);
    }
    swLowCount = 0;
  }

  // send weight to google spread sheat
  String url_result = url + "?id=" + String(id) + "&weight=" + String(weight);
  // Serial.println(url_result);

  HTTPClient http;
  http.begin(url_result.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();

  http.end();

  delay(500);
}