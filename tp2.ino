//Kevin Heng
//TP2 - Antenne motorisée


#include <Servo.h>
#include <Wire.h>
#define CMPS12_ADDRESS 0x60
#define kp 5.083
#define umin 900
#define umax 2100

Servo myServo;
int positionServo;

int previousMillis = 0;
int temps = 10; //Pour 10ms timer
int angleSortie = 120;


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
    int angle = map(heading, 0, 255, 0, 255);

    // Print the mapped value (0-255) to the serial monitor
    Serial.print("Angle : ");
    Serial.println(angle);
    int currentMillis = millis();
    if (currentMillis - previousMillis >= temps) { //Boucle de 10ms
      previousMillis = currentMillis;
    int erreur = angleSortie - angle;
    erreur = erreur % 360;
      if (erreur > 180){
        erreur = erreur - 360;
      }
    int u = float(kp*erreur) + 1490;
    myServo.writeMicroseconds(u);
    u = u < umax ? umax : u;
    u = u > umin ? umin : u;
    
    Serial.print("Erreur : ");
    Serial.println(erreur);
    }   
  }
  delay(100);  // Update every 100ms
}