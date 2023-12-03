#include <Servo.h>

#define gas_sensor      A0
#define buzzer          8
#define fireSensorPin   2
#define motorPin1       9
#define motorPin2       7

int sensorPin = A0;
int sensorThreshold = 400;
int sensor_value;
Servo gasSensorServo;
Servo fireSensorServo;

void setup() {
  Serial.begin(9600);
  
  
  pinMode(sensorPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  gasSensorServo.attach(9);  // Servo for gas sensor
  gasSensorServo.write(2);
  
  fireSensorServo.attach(7); // Servo for fire sensor
  fireSensorServo.write(0);
}

void loop() {
  // Gas Sensor
  if (analogRead(sensorPin) > sensorThreshold) {
    Serial.println("Gas Leakage detected");
  }
  
  sensor_value = analogRead(gas_sensor);
  Serial.println(sensor_value);
  
  if (sensor_value > 400) {
    digitalWrite(buzzer, HIGH);
    gasSensorServo.write(130);
  } else {
    digitalWrite(buzzer, LOW);
    //gasSensorServo.write(5);
  }
  
  // Fire Sensor
  int fireValue = digitalRead(fireSensorPin);
  Serial.println(fireValue);

  if (fireValue == 0) {  // Fire is detected
    //digitalWrite(buzzer, HIGH);
   digitalWrite(motorPin2, LOW);
   fireSensorServo.write(0);
  } 
  else {

    //digitalWrite(buzzer, LOW);
    digitalWrite(motorPin2, HIGH);
    //analogWrite(motorPin2, 0);
    fireSensorServo.write(130);  // You need to specify the angle for the fire sensor servo
  }
    delay(500);
}
