#define CONTROL 7
#define resistor 10

float capacity=0, value=0,voltage,current, time=0;

void measure (void) {

  value= analogRead(0); Serial.println(value);

  voltage=value/1023*5.0;

  current = voltage/resistor;

  capacity=capacity+current/3600;

  time++;

  Serial.print("Voltage= ");
  Serial.print(voltage);

  Serial.print("V Current= ");
  Serial.print(current);

  Serial.print("A Capacity= ");
  Serial.print(capacity);
  Serial.print("Ah ");

  Serial.print("Discharging time= ");
  Serial.print(time);
  Serial.print("s ");

  Serial.print("\n");
}

boolean x=false;

ISR(TIMER1_OVF_vect) {
  TCNT1=0x0BDC;
  x=!x;

  measure();

}

void setup() {

  pinMode(CONTROL, OUTPUT);

  TIMSK1=0x01; // enabled global and timer overflow interrupt;
  TCCR1A = 0x00; // normal operation page 148 (mode0);
  TCNT1=0x0BDC; // set initial value to remove time error (16bit counter register)
  TCCR1B = 0x04; // start timer/ set clock

  Serial.begin(9600);

};

void loop () {

  digitalWrite(CONTROL, x);

};


