#include "HX711.h"
const int DT_PIN = 32;
const int SCK_PIN = 33;
const int SW_PIN = 0;
const int SA_PIN = 34;
long count = 0;

HX711 scale;
long offset = 587973;
double gradient = 0.0024329871;
double baseWeight = 230.0;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  scale.begin(DT_PIN, SCK_PIN);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(SA_PIN, INPUT_PULLUP);
}

int swLowCount = 0;
void loop() {
  long value = scale.read_average(5);

  double weight = (double)(value - offset) * gradient;
  Serial.printf("重さ:%.1f[g]\n", weight );

  //Serial.printf("%ld\t offset:%ld\t gradient:%.10f\t weight:%.2f[g]\n", value - offset, offset, gradient, weight );

  if ( digitalRead(SA_PIN) == HIGH ){
    Serial.print("Offset value measuring..."); 
      offset = scale.read_average(50); 
      Serial.printf(" Done. Offset value = %ld\n", offset);
  }
    
    // Serial.printf("%ld\n",count); 
  

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

  delay(500);
}