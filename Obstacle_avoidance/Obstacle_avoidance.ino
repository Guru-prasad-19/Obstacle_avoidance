#include <ESP32Servo.h>
#define SOUND_SPEED 0.034
48 const int trigPin = 5;
const int echoPin = 18;
const int servoPin = 13;
Servo servo;
#define IN_1 5 // L298N in1 motors Right GPIO0(D3)
#define IN_2 4 // L298N in2 motors Right GPIO2(D4)
#define IN_3 0 // L298N in3 motors Left GPIO12(D6)
#define IN_4 2 // L298N in4 motors Left GPIO13(D7)
long duration;
float distance;
void forward(){ //forword
digitalWrite(IN_1, HIGH); //Right Motor forword Pin
digitalWrite(IN_2, LOW); //Right Motor backword Pin
digitalWrite(IN_3, HIGH); //Left Motor backword Pin
digitalWrite(IN_4, LOW); //Left Motor forword Pin
}
void backward(){ //backword
digitalWrite(IN_1, LOW); //Right Motor forword Pin
digitalWrite(IN_2, HIGH); //Right Motor backword Pin
digitalWrite(IN_3, LOW); //Left Motor backword Pin
digitalWrite(IN_4, HIGH); //Left Motor forword Pin
}
void turnRight(){ //turnRight
digitalWrite(IN_1, LOW); //Right Motor forword Pin
digitalWrite(IN_2, HIGH); //Right Motor backword Pin
digitalWrite(IN_3, HIGH); //Left Motor backword Pin
digitalWrite(IN_4, LOW); //Left Motor forword Pin
}
void turnLeft(){ //turnLeft
digitalWrite(IN_1, HIGH); //Right Motor forword Pin
digitalWrite(IN_2, LOW); //Right Motor backword Pin
digitalWrite(IN_3, LOW); //Left Motor backword Pin
digitalWrite(IN_4, HIGH); //Left Motor forword Pin
}
void stop(){ //stop
digitalWrite(IN_1, LOW); //Right Motor forword Pin
digitalWrite(IN_2, LOW); //Right Motor backword Pin
digitalWrite(IN_3, LOW); //Left Motor backword Pin
digitalWrite(IN_4, LOW); //Left Motor forword Pin
}
void setup() {
  Serial.begin(115200);  // Starts the serial communication
  servo.attach(servoPin);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
}
void loop() {
  servo.write(90);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * SOUND_SPEED / 2;
  if (distance <= 10) {
    servo.write(0);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long durationL = pulseIn(echoPin, HIGH);
    float distanceL = durationL * SOUND_SPEED / 2;
    Serial.println(distanceL);
    delay(1000);
    servo.write(180);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long durationR = pulseIn(echoPin, HIGH);
    float distanceR = durationR * SOUND_SPEED / 2;
    Serial.println(distanceR);
    if (distanceR > distanceL) {
      Serial.println("Turning Right");
      stop();
      turnRight();
    } else if (distanceR < distanceL) {
      Serial.println("Turning Left");
      stop();
      turnLeft();
    } else {
      stop();
      Serial.println("Move Back");
      backward();
    }
  } else {
    Serial.print("Distance (cm): ");
    Serial.println(distance);
    Serial.println("Going Forward ");
    forward();
  }
  delay(1000);
}
