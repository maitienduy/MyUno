#include <Adafruit_Sensor.h>
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <DHT.h>
/////////////////////////////config
//LiquidCrystal_I2C Serial(0x27,16,2); //diachi-ngang-doc
const int DHTPIN = 4; //pin digital4 cho DHT
const int DHTTYPE = DHT22; //loai DHT11
DHT dht(DHTPIN, DHTTYPE); //give sensor name as dht
//// Display temp vs hum
void display(){
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(t) || isnan(h)) { display();
  } 
  else {
//    Serial.setCursor(0,0);
    Serial.print("Humi "); Serial.print(h);Serial.print(" %"); 
//    Serial.setCursor(0,1);
    Serial.print("Temp "); Serial.print(t);Serial.print(" C"); 
    delay(1000);Serial.clear();
    if (t >= 35) hot();
    if (t <= 25) cold();
  }
}
void hot(){
// Serial.setCursor(6,0);
 Serial.print("Hot");delay(1000);
}
void cold(){
// Serial.setCursor(6,0);
 Serial.print("Cold"); delay(1000);
}
void setup() {
 Serial.init();       //Powwer On Serial
 Serial.backlight();  //Backlight On
 dht.begin();      //power on DHT
 //pinMode(2, OUTPUT);//speaker output
 }
void loop() {
 display();
 delay(1000);Serial.clear();
// Serial.setCursor(4, 0);
 Serial.print("Arduino!");
// delay(1000);Serial.clear();
 //tone(2,500,500); //out - frequent- duration
}
