//Kevin Heng
//TP2 - Antenne motorisée


#include <Servo.h>
#include <Wire.h>
#define CMPS12_ADDRESS 0x60
Servo myServo;
int positionServo;

int previousMillis = 0;
int temps = 10; //Pour 10 ms timer

void setup() {
  Serial.begin(9600);  // Start serial communication
  Wire.begin();  // Start I2C communication
  myServo.attach(3);
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

    // Print the mapped value (0-255) to the serial monitor
    Serial.println(mappedValue);
    int currentMillis = millis();
    if (currentMillis - previousMillis >= temps) { //Boucle de 1 seconde
      previousMillis = currentMillis;
      if (mappedValue <= 120){ //Si l'angle est de moins ou egal a 120 degres
        myServo.writeMicroseconds(900); //CCW MAX
      }
      else if (mappedValue >= 0){ //Si l'angle est plus grand ou egal a 0 degres
        myServo.writeMicroseconds(2100); //CW MAX
      } 
    }   
  }
  delay(100);  // Update every 100ms
}