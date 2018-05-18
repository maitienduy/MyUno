#include <SPI.h>
#include "RF24.h"
#include "DHT.h"
#include"Arduino.h"
#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTPIN 2 //pin sensor AM2302 D2
#define DHTTYPE DHT22 //loai cho AM2302

const uint64_t pipeSend = 0xF0F0F0F0E1LL; // địa chỉ để phát
const uint64_t pipeReceived = 0xE7E7E7E7E7LL; // dia chi de nhan

//config
const int ID_NODE=1;
const int ID_TEM=2;
const int ID_HUM=3;
const int ID_AIR=1;
const int ID_MUSIC=4;
const int ID_FAN=5;

const long TIME_UPLOAD=5*60000;


const int RED_PIN = 3;    // led red
const int GREEN_PIN = 4; // led xanh lá
const int BLUE_PIN = 5;  // led xanh dương

const int MUSIC_PIN=6;
const int FAN_PIN=7;


byte msgSend [3];
byte msgReceived[3];
int temLate;
int humLate;
int airLate;
int fanstatus=0;
long temTimeUp=0;
long humTimeUp=0;
long airTimeUp=0;
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

RF24 radio(9,10); ///////setpin RF

DHT dht(DHTPIN, DHTTYPE);  ///////// D4 vs 5v

/////////Thread
Thread temThread = Thread();
Thread humThread = Thread();
Thread airThread = Thread();
Thread recThread = Thread();
ThreadController controllThread = ThreadController();

//////doc nhiet do
int readTem(){
   float t = dht.readTemperature();
  if (isnan(t)) {
    return -1;
  } else {
    return t;
  }
}

/////doc do am
int readHum(){
   float h = dht.readHumidity();
  if (isnan(h)) {
    return -1;
  } else {
    return h;
  } 
 }
 
 /////doc chat luong khong khi
int readAir(){
   int a=analogRead(A0);
   if(a>0){
     a=a/10;
     a=a+1;
    }else{
     a=0; 
    }
  return a; 
 }

//call back Tempture
void temCallback(){
  boolean up=(millis()-temTimeUp >= TIME_UPLOAD);
  msgSend[1]=ID_TEM;
  int tem=readTem();
  lcd.setCursor(0,0);
  lcd.print("Temperature "); lcd.print(tem);lcd.write(1);lcd.print("C"); 
  if(temLate!=tem || up){
    msgSend[2]=tem;
    sendData(msgSend,3);
    temLate=tem;
    temTimeUp=millis();
  }
}
//callback Humidity
void humCallback(){
  boolean up=millis()-humTimeUp >= TIME_UPLOAD+1000;
   msgSend[1]=ID_HUM;
  int hum=readHum();
   lcd.setCursor(0,1);
   lcd.print("Humility "); lcd.print(hum);lcd.print(" %"); 
   delay(4000);lcd.clear();
  int sub=hum-humLate;
  if(sub>2 || sub<-2 || up){
    msgSend[2]=hum;
    sendData(msgSend,3);
    humLate=hum;
     humTimeUp=millis();
  }
}
//callback Airquality
void airCallback(){
  boolean up=millis()-airTimeUp >= TIME_UPLOAD;
  msgSend[1]=ID_AIR;
  int air=readAir();
  lcd.setCursor(0,0);
  lcd.print("Condition Status ");
  if(0<air && air<=30){
    lcd.setCursor(6,1);
    lcd.print("Good");
    onGreen();
    if (fanstatus == 1){digitalWrite(FAN_PIN, LOW);fanstatus=0;}
  }else if(30 <air && air<= 70){
    lcd.setCursor(5,1);
    lcd.print("Average"); 
    digitalWrite(FAN_PIN, HIGH);
    fanstatus =1;
    onBlue();
  }else if(air >70){
    lcd.setCursor(4,1);
    lcd.print("Warning!!!");
    digitalWrite(FAN_PIN, HIGH);
    tone(MUSIC_PIN, 800);
    fanstatus =1;
    onRed();
  }else{
    lcd.setCursor(5,1);
    lcd.print("Error!!!");onRed();
  }
  delay(4000);lcd.clear();
    int sub=air-airLate;
  if(air!=airLate || up){
    msgSend[2]=air;
    sendData(msgSend,3);
    airLate=air;
     airTimeUp=millis();
  }
}

//functrion controll
void controll(){
  //msgReceived[]
  //2 on- 1 off
  if(msgReceived[1]==ID_MUSIC && msgReceived[2]==2){
    //turn on music

    for(int i = 0; i < 5; i++){
      for(int j=0; j<3;j++){
        tone(MUSIC_PIN, 800);
        onRed();
        delay(300);
        noTone(MUSIC_PIN);
        delay(300);
      }
       delay(1000);
    }
  }

  if((msgReceived[1]==ID_FAN && msgReceived[2]==2)){
    digitalWrite(FAN_PIN, HIGH);
   }
   if((msgReceived[1]==ID_FAN && msgReceived[2]==1)){
    digitalWrite(FAN_PIN, LOW);
   }
}

//function send data to PI
void sendData(byte message[],int size){
  
  boolean sent=false;
  byte rec[1]={5};
  int count=0;
  while(!sent){
    radio.stopListening();
    radio.write(message,size);
    radio.startListening();

    if(radio.isAckPayloadAvailable()){
   //   Serial.print("ACK PayLoad: ");
      radio.read(rec,sizeof(rec));
    //  Serial.println(rec[0]);
      if(rec[0]==ID_NODE){
        sent=true;
      //  Serial.print("Sent success........"); 
      }
    }else{
     // Serial.print("No return payload---");
    }
    //radio.startListening();
    delay(1000);
    count++;
    if (count==3){
    //  Serial.println("Dont send.............");
      return;
    }
  }
 // Serial.println("");
}

//function receive data from Pi
void receivedData(){
  byte rec[1]={ID_NODE};
  if(radio.available()){
    radio.read(msgReceived, 3);
  //  Serial.print("Receivied: ");
 //   Serial.print(msgReceived[0]);
 //   Serial.print(msgReceived[1]);
 //   Serial.println(msgReceived[2]);
    if(msgReceived[0]==ID_NODE){
      radio.writeAckPayload( 1, rec,1);
      controll();
    }
  }
}

void onRed(){
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);  
}
void onGreen(){
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);  
}
void onBlue(){
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);  
}
void setup(){ 
  Serial.begin(9600);

  //============================================OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  onGreen();
  pinMode(FAN_PIN, OUTPUT);

  //============================================Module NRF24
  radio.begin();
  radio.setAutoAck(true);     
  radio.enableDynamicPayloads();
  radio.enableAckPayload();
  radio.setRetries(15,15);                 
  radio.setDataRate(RF24_250KBPS);    // Tốc độ truyền
  radio.setPALevel(RF24_PA_MIN);      // Dung lượng tối đa
  radio.setChannel(0x76);               // Đặt kênh
  radio.openWritingPipe(pipeSend);        // mở kênh
  radio.openReadingPipe(1,pipeReceived);
  radio.powerUp();  
  radio.startListening();
  radio.stopListening();
  radio.startListening();
  
  //=========================================LCD
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);
  
  //=========================================Module DHT AM2302
  dht.begin();
  
  msgSend[0] =ID_NODE;
  //==========================================Thread
  temThread.onRun(temCallback);
  temThread.setInterval(4000);
  
  humThread.onRun(humCallback);
  humThread.setInterval(3000);

  airThread.onRun(airCallback);
  airThread.setInterval(3500);

  recThread.onRun(receivedData);
  recThread.setInterval(1);

  controllThread.add(&temThread);
  controllThread.add(&humThread);
  controllThread.add(&airThread);
  controllThread.add(&recThread);
  
}

 boolean run=true;
//loop
void loop(){
  controllThread.run();
}

