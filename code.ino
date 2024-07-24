#include <Servo.h>

Servo myservo;

int LDRInput=A0;
int pinled = 11;
int pos = 0;
bool clicked = false;
int clickTime = 0;
int interval = 300;
int threshold = 0;    // 780
long long int backGround = 0;
long long int obstacle = 0;
bool darkmode = false;

void setup() {
  Serial.begin(9600);
	pinMode(pinled, OUTPUT);     
  pinMode(LDRInput,INPUT);
  myservo.attach(9);
  myservo.write(pos = 90);
  delay(1000);
  for (int i = 0; i < 20; i++) {
    digitalWrite(pinled, HIGH); 
		delay(100);
		digitalWrite(pinled, LOW);
    delay(100);    
  }
  digitalWrite(pinled, HIGH);
  for (int i = 0; i < 40; i++) {
    int value=analogRead(LDRInput);
    Serial.println("background value reading: " + String(value));
    backGround += value;
    delay(50);
  }
  digitalWrite(pinled, LOW);
  backGround /= 40;
  Serial.println("Final background Calibration: " + String(int(backGround)));


  for (int i = 0; i < 20; i++) {
    digitalWrite(pinled, HIGH);
		delay(100);
		digitalWrite(pinled, LOW);
    delay(100);    
  }
  digitalWrite(pinled, HIGH);
  for (int i = 0; i < 40; i++) {
    int value=analogRead(LDRInput);
    Serial.println("obstacle value reading: " + String(value));
    obstacle += value;
    delay(50);
  }
  digitalWrite(pinled, LOW);
  obstacle /= 40;
  Serial.println("Final Obstacle Calibration: " + String(int(obstacle)));

  darkmode = obstacle > backGround;
  threshold = (obstacle + backGround) / 2;

  Serial.println("Darkmode is " + String(darkmode) + " and threshold is set at " + String(threshold) + "\n");
  delay(2000);
}

void loop() {     
  int value=analogRead(LDRInput);
  Serial.println("LDR reading: " + String(value));
  if((!darkmode && value<threshold) || (darkmode && value>threshold))
  {
    Serial.println(String(value));
    if (!clicked) {
        pos = 135;
        myservo.write(pos);
        delay(150);         
        pos = 90;
        myservo.write(pos);
        clickTime = millis();
        clicked = true;
    }
  }
  else if (millis() - clickTime >= interval) {
    clicked = false;
  }
}