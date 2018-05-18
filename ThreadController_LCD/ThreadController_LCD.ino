#include <Thread.h>
#include <ThreadController.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>


LiquidCrystal_I2C lcd(0x27,16,2);
// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

// callback for myThread
void niceCallback(){
	lcd.print("COOL! I'm running on: ");
	lcd.println(millis());
}

// callback for hisThread
void boringCallback(){
	lcd.println("BORING...");
}

void setup(){
	Serial.begin(9600);
  lcd.init();       //Powwer On LCD
  lcd.backlight(); 

	// Configure myThread
	myThread->onRun(niceCallback);
	myThread->setInterval(10500);

	// Configure myThread
	hisThread.onRun(boringCallback);
	hisThread.setInterval(250);

	// Adds both threads to the controller
	controll.add(myThread);
	controll.add(&hisThread); // & to pass the pointer to it
}

void loop(){
	// run ThreadController
	// this will check every thread inside ThreadController,
	// if it should run. If yes, he will run it;
	controll.run();

	// Rest of code
	float h = 3.1415;
	h/=2;
}
