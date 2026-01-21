#include <Servo.h>

int joystickX = A0;
int joystickY = A1;
int joystickBoton = 9;
int pinServo = 3;
int pinFinalDer = 4;
int pinFinalIzq = 8;


int xValue = 0;
int finalD = 0;
int finalI = 0;
int boton = 0;
int lastBoton = HIGH; // Para detectar flancos


Servo servo;

void setup() {
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);

  pinMode(joystickBoton, INPUT_PULLUP);
  pinMode(pinFinalDer, INPUT_PULLUP);
  pinMode(pinFinalIzq, INPUT_PULLUP);

  servo.attach(pinServo);
  servo.write(90);

  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(joystickX);
  finalD = digitalRead(pinFinalDer);
  finalI = digitalRead(pinFinalIzq);
  boton = digitalRead(joystickBoton);

  // Detectar flanco de bajada (HIGH → LOW)
  if (lastBoton == HIGH && boton == LOW) {
   // manual = !manual; // Cambiar de modo
   // Serial.println(manual ? "Modo manual" : "Modo automático");
    delay(200); // Pequeño anti-rebote
  }
  lastBoton = boton;

  // Mostrar datos de depuración

  // Ejecutar modo correspondiente
  

    manualMode();
  

  delay(50);
}

void manualMode() {
  if (xValue > 400 && finalI == HIGH) {
    servo.write(0);
  } 
  else if (xValue > 300 && xValue < 400 && finalI == HIGH) {
    servo.write(80);
  } 
  else if (xValue < 200 && xValue > 100 && finalD == HIGH) {
    servo.write(100);
  } 
  else if (xValue < 100 && finalD == HIGH) {
    servo.write(180);
  } 
  else {
    servo.write(90);
  }
}
