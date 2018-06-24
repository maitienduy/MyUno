//Setup : SDA => A4/ SCL A5 VCC 5v
#include <Wire.h>
#include "i2c.h"
#include "i2c_BMP280.h"
BMP280 bmp280;

void setup()
{
    Serial.begin(9600);

    Serial.print("Probe BMP280: ");
    if (bmp280.initialize()) Serial.println("Sensor found");
    else
    {
        Serial.println("Sensor missing");
        while (1) {}
    }

    // onetime-measure:
    bmp280.setEnabled(0);
    bmp280.triggerMeasurement();
}

void loop()
{
    bmp280.awaitMeasurement();

    float temperature;
    bmp280.getTemperature(temperature);

    float pascal;
    bmp280.getPressure(pascal);

   // static float meters, metersold;
   // bmp280.getAltitude(meters); /**<  gives the number of meters above sea level */
   // metersold = (metersold * 10 + meters)/11;

    bmp280.triggerMeasurement();

   // Serial.print(" HeightPT1: ");
   // Serial.print(metersold);
   // Serial.print(" m; Height: ");
   // Serial.print(meters);
    Serial.print(" Pressure: ");
    Serial.print(pascal);
    Serial.print(" Pa; T: ");
    Serial.print(temperature);
    Serial.println(" C");
}