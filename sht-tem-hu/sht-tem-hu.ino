#include <Wire.h>
#include "SHTSensor.h"
//SHTSensor sht;
// To use a specific sensor instead of probing the bus use this command:
SHTSensor sht(SHTSensor::SHT3X);
float del;
float x1;
float x2;
unsigned long starttime;
unsigned long endtime;
void setup() {
  // put your setup code here, to run once:
  starttime = millis();
  Wire.begin();
  Serial.begin(9600);
  delay(1000); // let serial console settle
  if (sht.init()) {
      Serial.print("init(): success\n");
  } else {
      Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_HIGH); // only supported by SHT3x

}
  
void loop() {
      endtime = millis();
      if ((endtime -  starttime) > 500){
      x2 = x1;
      // Serial.println(x2, 2);
        if (sht.readSample()) {
        x1 = sht.getTemperature();
        // Serial.println(x1, 2);
        } else {
        Serial.print("Error in readSample()\n");
        }
      del = x2-x1;
      Serial.println(del, 2);
      starttime = millis(); 
   }
}
