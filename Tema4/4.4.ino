 #include <Servo.h>

int joystickX =A0;
int joystickY=A1;
int joystickBoton=9;
int pinServo=8;
int pinFinalDer=10;
int pinFinalIzq=11;
 int xValue =0;
 int finalD=0;
 int finalI=0;
Servo servo;


void setup(){
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);

  // Botón del joystick como entrada con resistencia pull-up
  pinMode(joystickBoton, INPUT_PULLUP);

  // Pines de los finales de carrera como entradas (con pull-up si son NC)
  pinMode(pinFinalDer, INPUT);
  pinMode(pinFinalIzq, INPUT);

  // Pin del servo como salida
  servo.attach(pinServo);

  // Comunicación opcional para depuración
  Serial.begin(9600);
}

void loop(){
  xValue = analogRead(joystickX); // Lee el eje X del joystick (0–1023)
  finalD= digitalRead(pinFinalDer);
  finalI=digitalRead(pinFinalIzq);
  Serial.println(xValue);

  Serial.println("Sensor Crash:"+String(digitalRead(pinFinalDer)));
  Serial.println("Sensor Crash:"+String(digitalRead(pinFinalIzq)));


   servo.write(90);
   




  if (xValue > 400  && finalI== HIGH ) {
    servo.write(0);
  } 
  else if (xValue >300 && xValue <400 && finalI== HIGH) {
    servo.write(80);

  } 
  else if (xValue < 200 && xValue>100  && finalD==HIGH ) {
        servo.write(100);

  } 
   else if (xValue < 100 && finalD==HIGH  ) {
        servo.write(180);

  } 
  else {
    servo.write(90);

  }

  

  delay(100);

}