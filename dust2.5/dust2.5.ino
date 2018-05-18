/*******************************
*
* DESCRIPTION
* Arduino Dust Sensor for Shinyei PPD42NS
* connect the sensor as follows :
*         Pin 1 of dust sensor          -> Ground
*          Pin 2 of dust sensor PM2.5    -> Digital 6 (PWM)
*          Pin 3 of dust sensor          -> +5V
*         Pin 4 of dust sensor PM1      -> Digital 3 (PMW)
*    
*  Based on: http://www.howmuchsnow.com/arduino/airquality/grovedust/
*  Authors: Chris Nafis Apris 2012
* Datasheet:  http://www.sca-shinyei.com/pdf/PPD42NS.pdf
* Contribution: epierre
*
* The dust sensor used (see purchase guide for latest link):
*/

#define DUST_SENSOR_DIGITAL_PIN_PM10  3
#define DUST_SENSOR_DIGITAL_PIN_PM25  6

unsigned long SLEEP_TIME = 30*1000; // Sleep time between reads (in milliseconds)
//VARIABLES
int val = 0;           // variable to store the value coming from the sensor
float valDUSTPM25 =0.0;
float lastDUSTPM25 =0.0;
float valDUSTPM10 =0.0;
float lastDUSTPM10 =0.0;
unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
long concentrationPM25 = 0;
long concentrationPM10 = 0;
int temp=20; //external temperature, if you can replace this with a DHT11 or better 
long ppmv;
 


void setup()  
{
 
 pinMode(DUST_SENSOR_DIGITAL_PIN_PM10,INPUT);
 pinMode(DUST_SENSOR_DIGITAL_PIN_PM25,INPUT);
 Serial.begin(115200);  
}

void loop()      
{    

 //get PM 2.5 density of particles over 2.5 μm.
 concentrationPM25=getPM(DUST_SENSOR_DIGITAL_PIN_PM25);
 Serial.print("PM25: ");
 Serial.println(concentrationPM25);
 Serial.print("\n");
 //ppmv=mg/m3 * (0.08205*Tmp)/Molecular_mass
 //0.08205   = Universal gas constant in atm·m3/(kmol·K)
 ppmv=(concentrationPM25*0.0283168/100/1000) *  (0.08205*temp)/0.01;

 if ((ceil(concentrationPM25) != lastDUSTPM25)&&((long)concentrationPM25>0)) {
     lastDUSTPM25 = ceil(concentrationPM25);
 }
//get PM 1.0 - density of particles over 1 μm.
 concentrationPM10=getPM(DUST_SENSOR_DIGITAL_PIN_PM10);
 Serial.print("PM10: ");
 Serial.println(concentrationPM10);
 Serial.print("\n");
 //ppmv=mg/m3 * (0.08205*Tmp)/Molecular_mass
 //0.08205   = Universal gas constant in atm·m3/(kmol·K)
 ppmv=(concentrationPM10*0.0283168/100/1000) *  (0.08205*temp)/0.01;
 
 if ((ceil(concentrationPM10) != lastDUSTPM10)&&((long)concentrationPM10>0)) {
     lastDUSTPM10 = ceil(concentrationPM10);
 }

delay(25000);
 
}

float conversion25(long concentrationPM25) {
 double pi = 3.14159;
 double density = 1.65 * pow (10, 12);
 double r25 = 0.44 * pow (10, -6);
 double vol25 = (4/3) * pi * pow (r25, 3);
 double mass25 = density * vol25;
 double K = 3531.5;
 return (concentrationPM25) * K * mass25;
}

float conversion10(long concentrationPM10) {
 double pi = 3.14159;
 double density = 1.65 * pow (10, 12);
 double r10 = 0.44 * pow (10, -6);
 double vol10 = (4/3) * pi * pow (r10, 3);
 double mass10 = density * vol10;
 double K = 3531.5;
 return (concentrationPM10) * K * mass10;
}

long getPM(int DUST_SENSOR_DIGITAL_PIN) {

 starttime = millis();

 while (1) {
 
   duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
   lowpulseoccupancy += duration;
   endtime = millis();
   
   if ((endtime-starttime) > sampletime_ms)
   {
   ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100
   long concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
   Serial.print("lowpulseoccupancy:");
   Serial.print(lowpulseoccupancy);
   Serial.print("\n");
   Serial.print("ratio:");
   Serial.print(ratio);
   Serial.print("\n");
   Serial.print("PPDNS42:");
   Serial.println(concentration);
   Serial.print("\n");
   
   lowpulseoccupancy = 0;
   return(concentration);    
   }
 }  
}
