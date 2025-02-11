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
  Wire.write(0x02);  // Register 0-360
  Wire.endTransmission();
  
  // Get the heading value (2 bytes)
  Wire.requestFrom(CMPS12_ADDRESS, 2);
  if (Wire.available() == 2) {
    int heading = Wire.read() << 8 | Wire.read();  // Combine the two bytes into one integer
    heading = heading & 0xFFF;  // Ensure it's in the range 0-360 (CMPS12 outputs 12-bit data)

    // Map the heading (0-360) to 0-3599 range
    int mappedValue = map(heading, 0, 360, 0, 360);

    // Print the mapped value (0-360) to the serial monitor
    Serial.println(mappedValue);
  }
  delay(100);  // Update every 100ms
}