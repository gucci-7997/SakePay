#include "HX711.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = ""; //Your SSID
const char* password = ""; //Your Password

// google spread sheet script
const String url = "";

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

//HACK intervalは何ミリ秒ごとにloopが実行されるか(正確にはdelayで待つか)を決定する。
int interval = 5000; 
int timer = 0;// 現在開始から何ミリ秒後か
double weight;
double jug_weight=750.0;
double over_weight=2500.0;
int first_arrived = 0; // 0:false 1:true
int cups_count = 0;

int prev_weight;

void setup(){
    Serial.begin(115200);
    Serial.println("Program beginnig...")
}

void loop(){
    if(timer < 7000){
        weight = 0;
    }
    if(timer < 7500){
        weight = over_weight;
    }
    if(timer < 18000){
        weight = jug_weight+400;
    }
    if(timer < 28000){
        weight = 0;
    }
    if(timer < 29000){
        weight = over_weight+250;
    }
    if(timer < 110000){
        weight = jug_weight+250;
    }
    if(timer < 120000){
        weight = 0;
    }
    if(timer < 121000){
        weight = over_weight;
    }
    if(timer < 250000){
        weight = jug_weight; 
    }
    if(timer < 260000){
        weight = 0;
    }
    if(timer < 260500){
        weight = over_weight;
    }
    if(timer < 280000){
        weight = jug_weight+400;
    }
    if(timer < 285000){
        weight = 0;
    }
    if(timer < 288000){
        weight = over_weight;
    }
    if(timer < 300000){
        weight = jug_weight+100;
    }
    else{
        weight = -10000;
    }

    if(first_arrived==0){
        if(500 < weight && weight <= 1500){
            first_arrived = 1;
            cups_count = cups_count+1;
            prev_weight = weight;
        }
    }else{
        if(weight <= 2000){//HACK 重量がオーバーしていない場合の処理...重量オーバーの判断がだいぶあやふやなので改善したい
            if(weight < prev_weight){//前回より重量が減っていれば"前回の重量"を更新
                prev_weight = weight;
            }
            else if(prev_weight < weight && jug_weight+200 < weight){//HACK 前回より重量が増えていて、かつ半分以上中身が入っていれば杯数を更新
                prev_weight = weight;
                cups_count = cups_count + 1;
                //ここのif分の中身、prev_weight < weightじゃなくてweight - prev_weight > 20みたいに、一定以上重さに変化があった場合(ノイズ除去のため)だけ条件式が成立するようにしたほうがいいかも
                //TODO その場合下のelseはエラーじゃなくてノイズらしきものを検出した旨のメッセージに変えること
            }
            else{//以上条件に満たない場合に遭遇したならエラーとしてシリアルに出力する
                Serial.println("Something went wrong. check the cups count statement");
            }
        }else{
            Serial.println("Noise?");//重量オーバー時には読み飛ばす。デバッグメッセージを出力しているが正式版では消してよし
            //TODO というか消したほうがよさそう
        }
    }

    timer = timer + interval;//現在時刻を更新しdelay
    delay(interval);
}
