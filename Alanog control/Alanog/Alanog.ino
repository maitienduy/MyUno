int bientroX = A0 ; 
int bientroY = A1 ; 
int button = 2; 
int RED_PIN = 8;    // led red
int GREEN_PIN = 12; // led xanh lá
int BLUE_PIN = 13;  // led xanh dương    
void setup ()
{
     pinMode(2, INPUT);
     pinMode(A0, INPUT);
     pinMode(A1, INPUT);
     pinMode(RED_PIN, OUTPUT);
     pinMode(GREEN_PIN, OUTPUT);
     pinMode(BLUE_PIN, OUTPUT);
     Serial.begin(9600);
     
}
void loop ()
{              //digitalWrite(RED_PIN,HIGH);
              //digitalWrite(GREEN_PIN,HIGH);
              //digitalWrite(BLUE_PIN,HIGH);
              int x = analogRead(bientroX);  // doc gia tri cua truc X
              int y = analogRead(bientroY);  // doc gia tri cua truc Y
              int sw = digitalRead(button);  // doc gia tri cua nut nhan
              Serial.print("X="); Serial.println(x);
              Serial.print("Y="); Serial.println(y);
              Serial.print("SW="); Serial.print(sw); 
              Serial.println();
              if (y < 400 || y > 700){digitalWrite(RED_PIN,LOW);}else digitalWrite(RED_PIN,HIGH);
              if (x < 400 || x > 700){digitalWrite(GREEN_PIN,LOW);}else digitalWrite(GREEN_PIN,HIGH);
              digitalWrite(BLUE_PIN,!sw);
             // delay(100);
}
