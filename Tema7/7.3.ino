/*
Hecho por:
Martín Almoina Iglesias UO300717
Sergio Fernandez-Miranda Longo UO302282
Ikram El Mabrouk Morhnane UO301848
*/

#include <Servo.h>

// === Señal de línea (digital) ===
const int NO_LINE = LOW;
const int LINE    = HIGH;

// === Servos y pines ===
Servo servoLeft;
Servo servoRight;

const int pinIrDer      = 3;
const int pinIrIzq      = 2;
const int pinServoRight = 9;
const int pinServoLeft  = 8;

// === Ultrasónico ===
const int pinTrig = 4;   // Trig en D4
const int pinEcho = 5;   // Echo en D5

// === Comandos de servo (servo continuo; 90=stop) ===
const int STOP          = 90;
const int BACKWARD      = 0;
const int FORWARD       = 180;
const int FORWARD_SLOW  = 135;
const int BACKWARD_SLOW = 45;

// === Tiempos (ms) de la maniobra de esquiva (AGRESIVOS, salida por IZQUIERDA) ===
// Sentido horario: salimos hacia la IZQUIERDA para trazar por FUERA y reentramos a la derecha.
unsigned int T_RETROCEDER      = 200;   // 150–250 ms
unsigned int T_PIVOT_SALIDA    = 480;   // giro IZQUIERDA ~100–120°
unsigned int T_AVANCE_LIBRAR   = 2000;   // antes 2000 ms → más corto (ganar lateral)
unsigned int T_PIVOT_PARALELO  = 480;   // giro DERECHA ~95–110°
unsigned int T_AVANCE_BORDEO   = 1000;  // 900–1300 ms (pasar el vaso por fuera)
unsigned int T_PIVOT_REENTRADA = 600;   // giro DERECHA hacia la línea
unsigned int T_BUSCA_LINEA_TO  = 3000;  // tiempo máx para reencontrar línea

// === Umbral de detección de obstáculo frontal (cm) ===
int DIST_OBS_CM = 16;               // 14–20 cm según pista
const unsigned long PROX_DEBOUNCE_MS = 40;

// === Utilidades de conducción ===
inline void stopNow() {
  servoLeft.write(STOP);
  servoRight.write(STOP);
}

inline void forwardFast() {
  // Avance recto según vuestro mapeo
  servoLeft.write(FORWARD);
  servoRight.write(BACKWARD);
}

inline void backwardFast() {
  servoLeft.write(BACKWARD);
  servoRight.write(FORWARD);
}

// Pivotes en el sitio (según vuestro montaje):
// - Pivot RIGHT (horario): ambos FORWARD
// - Pivot LEFT  (antihorario): ambos BACKWARD
inline void pivotRight() {
  servoLeft.write(FORWARD);
  servoRight.write(FORWARD);
}
inline void pivotLeft() {
  servoLeft.write(BACKWARD);
  servoRight.write(BACKWARD);
}

inline bool irLeftOnLine()  { return digitalRead(pinIrIzq) == LINE; }
inline bool irRightOnLine() { return digitalRead(pinIrDer) == LINE; }

// === Ultrasonidos: lectura estable (mediana de 3) ===
long readDistanceCmOnce() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  // Timeout ~25 ms → ~4.3 m para evitar bloqueos
  unsigned long dur = pulseIn(pinEcho, HIGH, 25000UL);
  if (dur == 0) return 999;           // sin eco dentro de timeout
  long cm = (long)(dur / 58.0);       // conversión típica a cm
  if (cm <= 0) cm = 999;
  return cm;
}

long readDistanceCm() {
  long a = readDistanceCmOnce(); delay(10);
  long b = readDistanceCmOnce(); delay(10);
  long c = readDistanceCmOnce();
  // Mediana de 3 para robustez
  long maxab = (a > b) ? a : b;
  long minab = (a < b) ? a : b;
  long med = (c > maxab) ? maxab : ((c < minab) ? minab : c);
  return med;
}

// Detección con pequeño debounce temporal
bool obstaculoDelante() {
  long d = readDistanceCm();
  if (d <= DIST_OBS_CM) {
    delay(PROX_DEBOUNCE_MS);
    long d2 = readDistanceCm();
    return d2 <= DIST_OBS_CM;
  }
  return false;
}

// Avances temporizados
void driveForwardMs(unsigned int t)  { forwardFast();   delay(t); stopNow(); }
void driveBackwardMs(unsigned int t) { backwardFast();  delay(t); stopNow(); }
void pivotRightMs(unsigned int t)    { pivotRight();    delay(t); stopNow(); }
void pivotLeftMs(unsigned int t)     { pivotLeft();     delay(t); stopNow(); }

// Avanzar hasta detectar línea (uno de los IR) o timeout
bool avanzarHastaLinea(unsigned long timeoutMs) {
  unsigned long t0 = millis();
  forwardFast();
  while (millis() - t0 < timeoutMs) {
    if (irLeftOnLine() || irRightOnLine()) {
      stopNow();
      return true;
    }
    delay(5);
  }
  stopNow();
  return false;
}

// Realinear al recuperar línea
void realinearConLinea() {
  if (irLeftOnLine() && !irRightOnLine()) {
    // Corrige a la derecha
    servoLeft.write(FORWARD);
    servoRight.write(STOP);
    delay(120); // Ajustar fino si hace falta
    stopNow();
  } else if (!irLeftOnLine() && irRightOnLine()) {
    // Corrige a la izquierda
    servoLeft.write(STOP);
    servoRight.write(BACKWARD);
    delay(120);
    stopNow();
  }
}

// Maniobra completa de esquiva (salida por IZQUIERDA → curva por FUERA)
void esquivarObstaculo() {
  // 1) Freno + retroceso corto
  stopNow();
  delay(40);
  driveBackwardMs(T_RETROCEDER);

  // 2) Salir hacia fuera por la IZQUIERDA (giro antihorario)
  pivotLeftMs(T_PIVOT_SALIDA);

  // 3) Alejarse un poco (tramo corto; dependemos poco de la velocidad)
  driveForwardMs(T_AVANCE_LIBRAR);

  // 4) Colocarse paralelo al exterior (giro a la DERECHA)
  pivotRightMs(T_PIVOT_PARALELO);

  // 5) Bordear el vaso por fuera
  driveForwardMs(T_AVANCE_BORDEO);

  // 6) Giro a la DERECHA para reentrar hacia la línea
  pivotRightMs(T_PIVOT_REENTRADA);

  // 7) Avanzar hasta enganchar la línea
  bool encontrada = avanzarHastaLinea(T_BUSCA_LINEA_TO);

  if (!encontrada) {
    // Fallback: barrido antihorario lento para reencontrar la línea
    unsigned long t0 = millis();
    while (millis() - t0 < 2500) {
      servoLeft.write(BACKWARD_SLOW);
      servoRight.write(BACKWARD_SLOW);
      if (irLeftOnLine() || irRightOnLine()) break;
      delay(5);
    }
    stopNow();
  }

  // 8) Ajuste fino
  realinearConLinea();
}

void setup() {
  Serial.begin(9600);

  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);

  stopNow();
  delay(300);
}

void loop() {
  // Prioridad: obstáculo frontal con ultrasónico
  if (obstaculoDelante()) {
    Serial.println("Obstaculo delante → ESQUIVAR (sale por IZQUIERDA, curva por FUERA)");
    esquivarObstaculo();
    return; // al volver, seguimos con el seguidor
  }

  // Seguidor de línea (sentido horario)
  bool L = (digitalRead(pinIrIzq) == LINE);
  bool R = (digitalRead(pinIrDer) == LINE);

  if (L && R) {
    // centrado
    servoLeft.write(FORWARD);
    servoRight.write(BACKWARD);
  } else if (L && !R) {
    // corrige a la izquierda
    Serial.println("gira izquierda");
    servoLeft.write(STOP);
    servoRight.write(BACKWARD);
  } else if (!L && R) {
    // corrige a la derecha
    Serial.println("gira derecha");
    servoLeft.write(FORWARD);
    servoRight.write(STOP);
  } else {
    // sin línea bajo ambos sensores → detente (más seguro)
    servoLeft.write(STOP);
    servoRight.write(STOP);
  }
}