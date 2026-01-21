// Pines de los LEDs
const int ledA = 6;
const int ledB = 5;
const int ledC = 3;

// Pin del potenciómetro
const int potPin = A5;

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
}

void loop() {
  int valor = analogRead(potPin); // Lee el potenciómetro (0–1023)

  // Mapeamos el valor a una escala de 0 a 7
  int nivel = map(valor, 0, 1023, 0, 7);

  // Apagamos todos los LEDs primero
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);

  // Encendemos según el tramo
  switch (nivel) {
    case 0:
      // Todos apagados
      break;
    case 1:
      digitalWrite(ledA, HIGH);
      break;
    case 2:
      digitalWrite(ledB, HIGH);
      break;
    case 3:
      digitalWrite(ledC, HIGH);
      break;
    case 4:
      digitalWrite(ledA, HIGH);
      digitalWrite(ledB, HIGH);
      break;
    case 5:
      digitalWrite(ledB, HIGH);
      digitalWrite(ledC, HIGH);
      break;
    case 6:
      digitalWrite(ledA, HIGH);
      digitalWrite(ledC, HIGH);
      break;
    case 7:
      digitalWrite(ledA, HIGH);
      digitalWrite(ledB, HIGH);
      digitalWrite(ledC, HIGH);
      break;
  }

  delay(50); // Pequeño retardo para estabilidad
}
