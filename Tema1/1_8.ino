// Pines de los LEDs
const int led1 = 6;
const int led2 = 5;
const int led3 = 3;

// Pin del potenciómetro
const int potPin = A5;

// Prototipos de funciones
int leerPotenciometro();
void calcularBrillos(int pot, int &b1, int &b2, int &b3);
void actualizarLEDs(int b1, int b2, int b3);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  int pot = leerPotenciometro();  // Leer valor del potenciómetro

  int brillo1 = 0, brillo2 = 0, brillo3 = 0;
  calcularBrillos(pot, brillo1, brillo2, brillo3); // Calcular brillos

  actualizarLEDs(brillo1, brillo2, brillo3); // Actualizar LEDs

  delay(10);
}

// ---- FUNCIONES ----

//  Leer el potenciómetro y mapear a 0–255
int leerPotenciometro() {
  int valor = analogRead(potPin);         // 0–1023
  return map(valor, 0, 1023, 0, 255);     // 0–255
}

//  Calcular los brillos según el rango del potenciómetro
void calcularBrillos(int pot, int &b1, int &b2, int &b3) {
  b1 = b2 = b3 = 0; // Reset de brillos

  if (pot >= 0 && pot < 64) {
    b1 = map(pot, 0, 63, 0, 255);
  }
  else if (pot >= 64 && pot < 128) {
    b2 = map(pot, 64, 127, 0, 255);
  }
  else if (pot >= 128 && pot < 192) {
    b3 = map(pot, 128, 191, 0, 255);
  }
  else if (pot >= 192) {
    int brillo = map(pot, 192, 255, 0, 255);
    b1 = b2 = b3 = brillo;
  }
}

//  Aplicar los brillos a los LEDs
void actualizarLEDs(int b1, int b2, int b3) {
  analogWrite(led1, b1);
  analogWrite(led2, b2);
  analogWrite(led3, b3);}

