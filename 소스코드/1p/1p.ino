#include <LiquidCrystal_I2C.h>
#include <Servo.h>  
#include <Wire.h>


Servo myservo1;
Servo myservo2;


int buttonpin1 = 2;
int buttonpin2 = 3;
int buttonState1 = 0;
int buttonState2 = 0;

int trigPin = 8; 
int echoPin = 9;
int p1score = 0, p2score = 0;
int led1 = 4, led2 = 5, led3 = 6;
float duration, distance, distance2;

LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzer = 7;
int temp;

void setup() {
  
  myservo1.attach(12);
  myservo2.attach(13);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // 출력 핀으로 설정
  pinMode(echoPin, INPUT); // 신호를 받는 핀 입력 설정
  pinMode(led1,OUTPUT); digitalWrite(led1, LOW);
  pinMode(led2,OUTPUT); digitalWrite(led2, LOW);
  pinMode(led3,OUTPUT); digitalWrite(led3, LOW);
  Serial.println("Start");
}
void loop() { 
  
  Serial.println(distance);
  buttonState1 = digitalRead(buttonpin1);
  if (buttonState1 == HIGH) {
  myservo1.write(180);
  myservo2.write(-180);
  delay(100);
  myservo1.write(90);
  myservo2.write(90);
  }

  lcd.setCursor(0,0); 
  lcd.print("player1 score:");
  lcd.print(p1score);
  lcd.setCursor(0,1); 
  lcd.print("player2 score:");
  lcd.print(p2score);
  
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
 if(distance > 6 && distance2 <= 6 && distance != 0) {
    p2score++;
    Wire.beginTransmission(8);
    Wire.write(p2score);
    Wire.endTransmission();
    Serial.write(p2score);
    Serial.print("p1 : ");
    Serial.println(p1score);
    Serial.print("p2 : ");
    Serial.println(p2score);
    goal();
  } 
  if(distance != 0) {
   distance2 = distance;
  }
  delay(50);
  if(p1score == 1) {
    digitalWrite(led1, HIGH);
  }
  else if(p1score == 2) {
   digitalWrite(led2, HIGH);
  }
  else if(p1score == 3) {
    digitalWrite(led3, HIGH);
  }
  Wire.requestFrom(8,1);
  while(Wire.available()) {
    p1score = Wire.read();
    if(temp != p1score) {
      Serial.print("p1 : ");
      Serial.println(p1score);
      Serial.print("p2 : ");
      Serial.println(p2score);
      goal();
    }
    temp = p1score;
  }
}

void goal() {
  tone(buzer, 523, 100);
  delay(100);
  tone(buzer, 587, 100);
  delay(100);
  tone(buzer, 659, 100);
  delay(100);
  tone(buzer, 698, 100);
  delay(100);
}
