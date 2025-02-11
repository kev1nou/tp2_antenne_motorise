//Kevin Heng
//TP2 - Antenne motorisée


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
  Wire.write(0x01);  // Register 0-255
  Wire.endTransmission();
  

  Wire.requestFrom(CMPS12_ADDRESS, 1);
  if (Wire.available()) {
    int heading = Wire.read();

    // Map the heading (0-255)
    int mappedValue = map(heading, 0, 255, 0, 255);

    // Print the mapped value (0-360) to the serial monitor
    Serial.println(mappedValue);
  }
  delay(100);  // Update every 100ms
}