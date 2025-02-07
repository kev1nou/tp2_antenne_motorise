//Kevin Heng
//TP2 - Antenne motorisée


#include <Servo.h>

Servo myServo;

void setup() {
myServo.attach(3);
myServo.writeMicroseconds(2100); //Vitesse max CCW
delay(3000);
myServo.writeMicroseconds(1510); //Vitesse moyenne CCW
delay(3000);
myServo.writeMicroseconds(1490); //Stop
delay(3000);
myServo.writeMicroseconds(900); //Vitesse max CW
delay(3000);
myServo.writeMicroseconds(1475); //Vitesse moyenne CW
delay(3000);
myServo.writeMicroseconds(1490); //Stop
}

void loop() {

}
