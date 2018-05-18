#include <LiquidCrystal.h>
 
//Khởi tạo với các chân
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() {
  //Thông báo đây là LCD 1602
  lcd.begin(16, 2);
 }
 
void loop() {
  // In ra dong chu
  lcd.setCursor(0, 0);
  lcd.print("Toi yeu Arduino!");
  lcd.setCursor(0, 1);
  lcd.print("   Arduino.VN");
 delay(1500);
 lcd.setCursor(0, 0);
  lcd.print("TestPage2!");
  lcd.setCursor(0, 1);
  lcd.print("   Arduino.VN");
  delay(1500);
}
