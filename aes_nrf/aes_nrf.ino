#include<SPI.h>
#include<RF24.h>
#include <AES.h>

// CE, CSN pins
RF24 radio(9, 10);
const uint64_t pipeSend = 0xF0F0F0F0E1LL; // địa chỉ để phát
const uint64_t pipeReceived = 0xE7E7E7E7E7LL; // dia chi de nhan
void setup(void){
  Serial.begin(9600);

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
}
int i =0;
const char text[] = "Text From Arduino";
void loop(void){
//////RECEIVE
delay(500);
radio.startListening();
  Serial.println("Receiving..");
  //char receivedMessage[32] = {0};
  char receivedMessage[32];
  if(radio.available()){
   Serial.print("GOT : ");
   radio.read(&receivedMessage,32);
   //radio.read(receivedMessage, sizeof(receivedMessage));
   Serial.println(receivedMessage);
   // Serial.println(sizeof(receivedMessage));
   }
delay(500);
//////SEND
radio.stopListening();delay(200);
      Serial.println("Sending...");     
      radio.write(text, sizeof(text));
      delay(100);
      radio.startListening();
      if ( radio.isAckPayloadAvailable() ) {      
      Serial.println("We sent our message.");}
}
