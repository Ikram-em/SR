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
int pinIrDerFuera = 11;
int pinIrIzqFuera = 10;
int pinServoRight = 9;
int pinServoLeft = 8;

int STOP = 90;
int BACKWARD = 0;
int FORWARD = 180;
int FORWARD_SLOW = 135;
int BACKWARD_SLOW = 45;

int TURN_AROUND = 1800;
int TURN_CORNER = 900;
int counter = 0;

bool foundRight = false;
bool continua = true;
void setup(){
Serial.begin(9600); // Descomentar si quer�is debuguear por consola
pinMode(pinIrDer, INPUT);
pinMode(pinIrIzq, INPUT);
servoLeft.attach(pinServoLeft);
servoRight.attach(pinServoRight);
}
void loop(){
  if(continua) {
    if(digitalRead(pinIrIzq) && digitalRead(pinIrDer)  && digitalRead(pinIrIzqFuera)) {
       delay(50);
       if(!digitalRead(pinIrDerFuera)) {
        delay(250);
         if(!digitalRead(pinIrIzq) && !digitalRead(pinIrDer) && !digitalRead(pinIrDerFuera) && !digitalRead(pinIrIzqFuera)) {
            servoLeft.write(BACKWARD);
            servoRight.write(BACKWARD);
            delay(TURN_CORNER);
         }
       }
       
    }
    if (foundRight && !digitalRead(pinIrDerFuera)){

      delay(100);
      foundRight=false;
      
      giraDerecha();
    }
    
  if(digitalRead(pinIrIzq) && digitalRead(pinIrDer)) {
    if(digitalRead(pinIrDerFuera)){
      wait();

    }
   
    
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
     servoLeft.write(FORWARD);
    servoRight.write(FORWARD);
    delay(TURN_AROUND);
    
  }
  }
   


}

void wait() {
  delay(300);
  if(digitalRead(pinIrIzqFuera) && digitalRead(pinIrDerFuera)) {
   // finish
   servoLeft.write(STOP);
   servoRight.write(STOP);
   continua = false;
   exit(0);
  }
  else {
    foundRight = true;
  }
}

void giraDerecha(){

    Serial.println("gira derecha");
    servoLeft.write(FORWARD);
    servoRight.write(FORWARD);
    delay(TURN_CORNER);

}
