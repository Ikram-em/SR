/* 
Hecho por:
Martín Almoina Iglesias UO300717
Sergio Fernandez-Miranda Longo UO302282
Ikram El Mabrouk Morhnane UO301848
*/

#include <Servo.h>
int NO_LINE = LOW; 
int LINE = HIGH; 
Servo servoLeft;
Servo servoRight;
int pinIrDer = 3;
int pinIrIzq = 2;
int pinServoRight = 9;
int pinServoLeft = 8;
int STOP = 90;
int BACKWARD = 180;
int FORWARD = 0;
int FORWARD_SLOW = 45;
int BACKWARD_SLOW = 135;
int currentTime = 100;
int hasReadLine=0;
int TURN_AROUND = 1800;
int counter=0;

// --- Variables de estado para reemplazar delay() por millis() ---
bool searchActive = true;        // Equivale a (hasReadLine == 0); se desactiva al ver línea
bool phaseAdvance = true;        // true: fase de avance; false: fase de giro
unsigned long phaseStart = 0;    // marca de tiempo de inicio de la fase en curso
unsigned long phaseDuration = 0; // duración objetivo de la fase actual (ms)


void startAdvancePhase() {
  phaseAdvance   = true;
  phaseStart     = millis();
  phaseDuration  = currentTime;            // la fase de avance dura currentTime ms
  servoLeft.write(BACKWARD);
  servoRight.write(FORWARD);
}

void startTurnPhase() {
  phaseAdvance   = false;
  phaseStart     = millis();
  phaseDuration  = TURN_AROUND / 2;        // un cuarto de vuelta
  servoLeft.write(BACKWARD);
  servoRight.write(STOP);
}

void setup() {
    Serial.begin(9600); // Descomentar si queréis debuguear por consola
    pinMode(pinIrDer, INPUT);
    pinMode(pinIrIzq, INPUT);
    servoLeft.attach(pinServoLeft);
    servoRight.attach(pinServoRight);
}

void loop() {

  if (searchActive) {
    // Si cualquiera de los sensores ve línea, salimos de la búsqueda
    if (digitalRead(pinIrIzq) || digitalRead(pinIrDer)) {
      searchActive = false;  // Equivale a hasReadLine = 1
      // Aquí puedes activar tu siguelíneas
      // p. ej., servoLeft.write(...); servoRight.write(...);
    } else {
      // Gestionar la fase en curso por tiempo (sin delay)
      unsigned long now = millis();
      if (now - phaseStart >= phaseDuration) {
        if (phaseAdvance) {
          // Terminó el avance -> pasamos a girar
          startTurnPhase();
        } else {
          // Terminó el giro -> completamos un ciclo: duplicar currentTime y volver a avanzar
          currentTime = currentTime + 100;
          startAdvancePhase();
        }
      }
    }
    
    
  }



  if (!searchActive) {
    if (counter=0){
      startTurnPhase();
      counter=1;
    }
if(digitalRead(pinIrIzq) && digitalRead(pinIrDer)) {
  servoLeft.write(BACKWARD);
  servoRight.write(FORWARD);
}
else if(digitalRead(pinIrIzq) && !digitalRead(pinIrDer)) {
  Serial.println("gira izquierda");
  servoLeft.write(STOP);
  servoRight.write(FORWARD);
}
else if(!digitalRead(pinIrIzq) && digitalRead(pinIrDer)) {
Serial.println("gira derecha");
  servoLeft.write(BACKWARD);
  servoRight.write(STOP);
}
else {
  startTurnPhase();
}}

}
