// Pines de los LEDs (deben ser PWM para controlar brillo)
const int ledA = 6;  // PWM
const int ledB = 5;  // PWM
const int ledC = 3;  // PWM

// Pines de potenciómetros
const int potNivel = A5;  // Selección de combinación de LEDs
const int potBrillo = A4; // Control de brillo

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
}

void loop() {
  // Lee el potenciómetro que controla el patrón
  int valorNivel = analogRead(potNivel); // 0–1023
  int nivel = map(valorNivel, 0, 1023, 0, 7);

  // Lee el potenciómetro que controla el brillo
  int valorBrillo = analogRead(potBrillo); // 0–1023
  int brillo = map(valorBrillo, 0, 1023, 0, 255); // Escala 0–255

  // Apagamos todos los LEDs primero
  analogWrite(ledA, 0);
  analogWrite(ledB, 0);
  analogWrite(ledC, 0);

  // Encendemos los LEDs con el brillo correspondiente
  switch (nivel) {
    case 0:
      // Todos apagados
      break;
    case 1:
      analogWrite(ledA, brillo);
      break;
    case 2:
      analogWrite(ledB, brillo);
      break;
    case 3:
      analogWrite(ledC, brillo);
      break;
    case 4:
      analogWrite(ledA, brillo);
      analogWrite(ledB, brillo);
      break;
    case 5:
      analogWrite(ledB, brillo);
      analogWrite(ledC, brillo);
      break;
    case 6:
      analogWrite(ledA, brillo);
      analogWrite(ledC, brillo);
      break;
    case 7:
      analogWrite(ledA, brillo);
      analogWrite(ledB, brillo);
      analogWrite(ledC, brillo);
      break;
  }

  delay(50); // Retardo para estabilidad
}
