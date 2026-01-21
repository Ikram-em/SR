/* 
Hecho por:
Martín Almoina Iglesias UO300717
Sergio Fernandez-Miranda Longo UO302282
Ikram El Mabrouk Morhnane UO301848
*/

#include <Servo.h>
int NO_LINE = LOW; // Tambi�n podr�a ponerse 0
int LINE = HIGH; // Tambi�n podr�a ponerse 1
Servo servoLeft;
Servo servoRight;
int pinIrDer = 3;
int pinIrIzq = 2;
int pinServoRight = 9;
int pinServoLeft = 8;
int STOP = 90;
int BACKWARD = 0;
int FORWARD = 180;
int FORWARD_SLOW = 135;
int BACKWARD_SLOW = 45;

int TURN_AROUND = 1800;
void setup(){
Serial.begin(9600); // Descomentar si quer�is debuguear por consola
pinMode(pinIrDer, INPUT);
pinMode(pinIrIzq, INPUT);
servoLeft.attach(pinServoLeft);
servoRight.attach(pinServoRight);
}
void loop(){
if(digitalRead(pinIrIzq) && digitalRead(pinIrDer)) {
	servoLeft.write(FORWARD);
	servoRight.write(BACKWARD);
}
else if(digitalRead(pinIrIzq) && !digitalRead(pinIrDer)) {
	Serial.println("gira izquierda"); 
	servoLeft.write(STOP);
	servoRight.write(BACKWARD);
}
else if(!digitalRead(pinIrIzq) && digitalRead(pinIrDer)) {
Serial.println("gira derecha");
	servoLeft.write(FORWARD);
	servoRight.write(STOP);
}
else {
	servoLeft.write(STOP);
	servoRight.write(STOP);
}

}
