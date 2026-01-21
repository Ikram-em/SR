#include <Servo.h>

int joystickX =A0;
int joystickY=A1;
int joystickBoton=9;
int pinServo=8;
int pinFinalDer=7;
int pinFinalIzq=6;
 int xValue =0;
Servo servo;


void setup(){
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);

  // Botón del joystick como entrada con resistencia pull-up
  pinMode(joystickBoton, INPUT_PULLUP);

  // Pines de los finales de carrera como entradas (con pull-up si son NC)
  pinMode(pinFinalDer, INPUT_PULLUP);
  pinMode(pinFinalIzq, INPUT_PULLUP);

  // Pin del servo como salida
  servo.attach(pinServo);

  // Comunicación opcional para depuración
  Serial.begin(9600);
}

void loop(){
  xValue = analogRead(joystickX); // Lee el eje X del joystick (0–1023)
  Serial.println(xValue);

   servo.write(90);


  // Control del actuador según posición del joystick
  if (xValue > 300 ) {
    // Mover hacia fuera (extender)

  servo.write(0);
  } 
  else if (xValue < 200 ) {
    // Mover hacia dentro (retraer)
        servo.write(180);

  } 
  else {
    // En zona muerta o botón presionado → detener
    servo.write(90);

  }

  delay(100);

}