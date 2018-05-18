#include "UART_ARDUINO.h"
UART vietnam;
void setup()
{
  vietnam.begin(9600); // baud: 200 -> 250,000.
  pinMode(13, 1); //led
  pinMode(5, INPUT_PULLUP); // nut button
}
void nhap_nhay()
{
  for (byte i = 0; i < 3; i++) {
    digitalWrite(13, 1);
    delay(200);
    digitalWrite(13, 0);
    delay(200);
  }
}
char t = 'A'; // truyền 1 kí tự trong bảng ASCII
void loop()
{
  if (digitalRead(5) == 0) {
    nhap_nhay();
    vietnam.write_char(t);
  }

  if (Serial.available() >= 1) {
    if (vietnam.read_char() == 'A') {

      nhap_nhay();
      vietnam.write_char(t);
    }
  }
}
