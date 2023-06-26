#include <Wire.h>
#include <Servo.h>


int trigPin = 8; 
int echoPin = 9;
int p1score = 0, p2score = 0;
int led1 = 4, led2 = 5, led3 = 6;
float duration, distance, distance2;

Servo myservo1;
Servo myservo2;
int buttonpin1 = 2;
int buttonpin2 = 3;
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {
  myservo1.attach(12);
  myservo2.attach(13);
  pinMode(buttonpin1,INPUT);
  pinMode(buttonpin2,INPUT);
  
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
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
  myservo1.write(-180);
  myservo2.write(180);
  delay(100);
  myservo1.write(90);
  myservo2.write(90);
  }
  digitalWrite(trigPin, HIGH); delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
  if(distance > 6 && distance2 <= 6 && distance != 0) {
    p1score++;
    Serial.print("p1 : ");
    Serial.println(p1score);
    Serial.print("p2 : ");
    Serial.println(p2score);
  }
  if(distance != 0) {
    distance2 = distance;
  }
  delay(50);
  if(p2score == 1) {
    digitalWrite(led1, HIGH);
  }
  else if(p2score == 2) {
   digitalWrite(led2, HIGH);
  }
  else if(p2score == 3) {
    digitalWrite(led3, HIGH);
  }
}

void receiveEvent() {
  p2score = Wire.read();
  Serial.print("p1 : ");
    Serial.println(p1score);
    Serial.print("p2 : ");
    Serial.println(p2score);
}
void requestEvent() {
  Wire.write(p1score);
}
