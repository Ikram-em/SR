// Semáforo 1.4 - Cruce con dos semáforos

// Pines Semáforo 1
int rojo1 = 2;
int amarillo1 = 3;
int verde1 = 4;

// Pines Semáforo 2
int rojo2 = 5;
int amarillo2 = 6;
int verde2 = 7;

// Tiempos (en milisegundos)
int tiempoVerde = 5000;    // 5s verde
int tiempoAmarillo = 2000; // 2s amarillo
int tiempoRojo = 1000;     // 1s de seguridad antes del cambio

void setup() {
  // Configurar pines como salida
  pinMode(rojo1, OUTPUT);
  pinMode(amarillo1, OUTPUT);
  pinMode(verde1, OUTPUT);

  pinMode(rojo2, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(verde2, OUTPUT);

  // Estado inicial: semáforo 1 en verde, semáforo 2 en rojo
  digitalWrite(verde1, HIGH);
  digitalWrite(rojo2, HIGH);
}

void loop() {
  // Semáforo 1 verde, Semáforo 2 rojo
  delay(tiempoVerde);

  // Cambia semáforo 1 a amarillo
  digitalWrite(verde1, LOW);
  digitalWrite(amarillo1, HIGH);
  delay(tiempoAmarillo);

  // Pasa semáforo 1 a rojo
  digitalWrite(amarillo1, LOW);
  digitalWrite(rojo1, HIGH);
  delay(tiempoRojo);

  // Cambia semáforo 2 a verde
  digitalWrite(rojo2, LOW);
  digitalWrite(verde2, HIGH);
  delay(tiempoVerde);

  // Cambia semáforo 2 a amarillo
  digitalWrite(verde2, LOW);
  digitalWrite(amarillo2, HIGH);
  delay(tiempoAmarillo);

  // Pasa semáforo 2 a rojo
  digitalWrite(amarillo2, LOW);
  digitalWrite(rojo2, HIGH);
  delay(tiempoRojo);

  // Cambia semáforo 1 a verde de nuevo
  digitalWrite(rojo1, LOW);
  digitalWrite(verde1, HIGH);
}
