#include <Keypad.h>

const int ledRojo = 10;
const int ledVerde = 11;

bool puertaAbierta = false;
unsigned long tiempoApertura = 0;
const unsigned long duracionApertura = 5000; // 5 segundos

// Configuración del teclado (4x4 en este caso)
const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {2, 3, 4, 5};
byte pinesColumnas[COLUMNAS] = {6, 7, 8, 9};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledVerde, HIGH); // Puerta cerrada al inicio
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    if (tecla == 'A' && !puertaAbierta) {
      abrirPuerta();
    }
    // Cualquier otra tecla se ignora
  }

  if (puertaAbierta && millis() - tiempoApertura >= duracionApertura) {
    cerrarPuerta();
  }
}

void abrirPuerta() {
  puertaAbierta = true;
  tiempoApertura = millis();
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, HIGH);
  Serial.println("Puerta abierta");
}

void cerrarPuerta() {
  puertaAbierta = false;
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, HIGH);
  Serial.println("Puerta cerrada");
}
