// Semáforo 1.5 con 2 LEDs RGB

// Pines Semáforo 1 (RGB)
int rojo1 = 2;
int verde1 = 3;

// Pines Semáforo 2 (RGB)
int rojo2 = 5;
int verde2 = 6;

// Pines Peatones
int rojoP = 7;
int verdeP = 8;
int buzzer = 9;

// Tiempos
int tiempoVerde = 5000;
int tiempoAmarillo = 2000;
int tiempoRojo = 1000;
int tiempoRojoAVerdePeaton = 500;
int tiempoCrucePeat = 4000;
int tiempoParpadeo = 200; // para peatones

void setup() {
  pinMode(rojo1, OUTPUT);
  pinMode(verde1, OUTPUT);

  pinMode(rojo2, OUTPUT);
  pinMode(verde2, OUTPUT);
  
  pinMode(rojoP, OUTPUT);
  pinMode(verdeP, OUTPUT);
  
  pinMode(buzzer, OUTPUT);

  // Estado inicial: semáforo 1 en verde, semáforo 2 en rojo
  digitalWrite(verde1, HIGH);
  digitalWrite(rojo2, HIGH);
  
  // Cuando el semaforo 1 se ponga en rojo los peatones pueden pasar
  digitalWrite(rojoP, HIGH);
  digitalWrite(verdeP, LOW);
}

void loop() {
  // Semáforo 1 verde
  delay(tiempoVerde);

  // Semáforo 1 amarillo
  digitalWrite(verde1, LOW);
  digitalWrite(rojo1, HIGH);
  digitalWrite(verde1, HIGH);
  delay(tiempoAmarillo);

  // Semáforo 1 rojo
  digitalWrite(rojo1, LOW);
  digitalWrite(verde1, LOW);
  digitalWrite(rojo1, HIGH);
  
  delay(tiempoRojoAVerdePeaton);
  
  digitalWrite(verdeP, HIGH);
  digitalWrite(rojoP, LOW);
  digitalWrite(buzzer, HIGH);
  
  delay(tiempoRojoAVerdePeaton);

  // Semáforo 2 verde
  digitalWrite(rojo2, LOW);
  digitalWrite(verde2, HIGH);
  digitalWrite(buzzer, LOW);
  
  for(int i = 0; i<5;i++) {
  	delay(tiempoRojoAVerdePeaton);
    digitalWrite(buzzer, LOW);
    delay(tiempoRojoAVerdePeaton);
    if(i==4) {
    	break;
    }
    digitalWrite(buzzer, HIGH);
  }

  // Semáforo 2 amarillo
  digitalWrite(verde2, LOW);
  digitalWrite(rojo2, HIGH);
  digitalWrite(verde2, HIGH);
  
  for(int i=0; i<5; i++) {
    delay(tiempoParpadeo);
    digitalWrite(verdeP, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(tiempoParpadeo);
    digitalWrite(verdeP, LOW);
    digitalWrite(buzzer, LOW);
  }
  digitalWrite(rojoP, HIGH);

  // Semáforo 2 rojo
  digitalWrite(rojo2, LOW);
  digitalWrite(verde2, LOW);
  digitalWrite(rojo2, HIGH);
  delay(tiempoRojo);

  // Semáforo 1 verde de nuevo
  digitalWrite(rojo1, LOW);
  digitalWrite(verde1, HIGH);
}

