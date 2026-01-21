#include <Keypad.h>

const int ledRojo = 10;
const int ledVerde = 11;

bool puertaAbierta = false;
unsigned long tiempoApertura = 0;
const unsigned long duracionApertura = 5000; // 5 segundos

const String clave = "9876";
String entrada = "";

bool bloqueoEntrada = false;
unsigned long tiempoBloqueo = 0;
int parpadeos = 0;

// Configuración del teclado
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
  // Procesar tiempo de bloqueo (por parpadeo o apertura)
  if (bloqueoEntrada) {
    if (puertaAbierta) {
      // Durante apertura, solo permitir cerrar con C
      char tecla = teclado.getKey();
      if (tecla == 'C') {
        cerrarPuerta();
        bloqueoEntrada = false;
      } else if (millis() - tiempoApertura >= duracionApertura) {
        cerrarPuerta();
        bloqueoEntrada = false;
      }
    } else {
      // Durante parpadeo por error de contraseña
      if (millis() - tiempoBloqueo >= 1000 && parpadeos < 3) {
        digitalWrite(ledVerde, !digitalRead(ledVerde));
        tiempoBloqueo = millis();
        parpadeos++;
      } else if (parpadeos >= 3) {
        digitalWrite(ledVerde, HIGH); // LED verde encendido al terminar
        bloqueoEntrada = false;
        parpadeos = 0;
        entrada = ""; // Limpiar entrada
      }
    }
    return; // No procesar más durante el bloqueo
  }

  char tecla = teclado.getKey();

  if (tecla) {
    Serial.print("Tecla presionada: ");
    Serial.println(tecla);

    if (tecla == 'C' && puertaAbierta) {
      cerrarPuerta();
      bloqueoEntrada = false;
    }
    else if (tecla >= '0' && tecla <= '9') {
      entrada += tecla;
      if (entrada.length() == 4) {
        verificarClave();
        entrada = "";
      }
    } else {
      // Tecla no válida, ignorar (A, B, D, *, #)
    }
  }
}

void verificarClave() {
  if (entrada == clave) {
    Serial.println("Contraseña correcta");
    digitalWrite(ledVerde, LOW); // Apagar LED verde 1 segundo
    delay(1000);
    abrirPuerta();
    bloqueoEntrada = true; // Bloquear entrada durante apertura
  } else {
    Serial.println("Contraseña incorrecta");
    bloqueoEntrada = true;
    parpadeos = 0;
    tiempoBloqueo = millis();
    digitalWrite(ledVerde, LOW); // Empezar parpadeo
  }
}

void abrirPuerta() {
  puertaAbierta = true;
  tiempoApertura = millis();
  digitalWrite(ledRojo, HIGH);   // LED rojo encendido (puerta abierta)
  digitalWrite(ledVerde, LOW);   // LED verde apagado
  Serial.println("Puerta abierta");
}

void cerrarPuerta() {
  puertaAbierta = false;
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, HIGH);
  entrada = ""; // Limpiar entrada al cerrar
  Serial.println("Puerta cerrada");
}
