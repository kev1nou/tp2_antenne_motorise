//Kevin Heng //
//TP2 - Antenne motorisée //


#include <Servo.h>
#include <Wire.h>
#define CMPS12_ADDRESS 0x60
Servo myServo;
int positionServo;

void setup() {
  Serial.begin(9600);  // Start serial communication
  Wire.begin();  // Start I2C communication
}

void loop() {
  // Request heading data from CMPS12
  Wire.beginTransmission(CMPS12_ADDRESS);
  Wire.write(0x01);  // Register for 0-255 
  Wire.endTransmission();
  
  Wire.requestFrom(CMPS12_ADDRESS,1);
  if (Wire.available()){
    int value = Wire.read();
    Serial.println(value);
  }
  delay(100);  // Update every 100ms
}
