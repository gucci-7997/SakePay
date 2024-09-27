#include <U8g2lib.h>

  

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

  

void setup() {

 u8g2.begin();
 u8g2.enableUTF8Print();// UTF-8エンコードされた文字列の使用を有効化
 u8g2.setFont(u8g2_font_unifont_t_japanese2);// 日本語フォントを設定
 u8g2.setFontMode(1);// テキストの背景を透明に設定
 u8g2.setDrawColor(1);// 文字色を白に設定

}

int judge = 1;//juggeは飲みすぎ、飲まなすぎの判定
int cups = 0;//cupsは杯数
int x = 0;//文字を動かすための変数
int y = 28;//文字位置(高さ)の初期値
int count_loop = 0;

void loop() {
 u8g2.clearBuffer();
 if(judge == 0){       //通常処理
  String text = " 杯数   :   " + String(cups);
  u8g2.setCursor(0, y);//文字の位置(x,y)
  u8g2.print(text);
 }else if(judge == 1){  //飲みすぎ処理  
  u8g2.setCursor(x, y);
  u8g2.print("飲みすぎ飲みすぎ飲みすぎ飲みすぎ飲みすぎ");
  x-=5;
  if(x <= -192){
    x = 0;
    count_loop++;
    if(count_loop == 3){
      count_loop = 0;
      judge = 0;
    }
  }
 }else if(judge == -1){  //飲まなすぎ処理
  u8g2.setCursor(x, y);
  u8g2.print("飲んでなくないWOWWOW飲んでなくないWOWWOW");
  x-=5;
  if(x <= -160){
    x = 0;
    count_loop++;
    if(count_loop == 3){
      count_loop = 0;
      judge = 0;
    }
  }
 }
 u8g2.sendBuffer();
 delay(100);

}


//改善点
//・フォントサイズ(多分きつい)
//・表示内容
//・judge,cupsの変数を取得

//めも
//日本語フォント16
//英語フォント8