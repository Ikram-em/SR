int ledrojo = 2;
int ledverde = 3;
int ledazul = 4;

int botonrojo =7;
int botonverde =8;

int piezoPin = 11;

int mostradaSecuencia = 0;

int contadorRonda = 0;
int condicionLectura = 0;
int botonesPulsados = 0;

// Notes (frequencies in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A3  220
#define NOTE_C5  523

int melodyLose[] = {
  NOTE_C5, NOTE_G4, NOTE_E4, NOTE_A3, NOTE_F4, NOTE_C4
};

int durations[] = {
  300, 300, 300, 300, 400, 600
};

int melodyWin[] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5 };
int winDurations[] = { 200, 200, 200, 400, 200, 600 };
int winLength = 6;

int arraysecuencia[5] = {0, 0, 0, 0, 0};
/*
 * rojo=1
 * verde=2
*/
int pinForRandom = A0;

int victoria=0;

void setup() {
  pinMode(ledrojo,OUTPUT);
  pinMode(ledverde,OUTPUT);
  pinMode(botonrojo,INPUT);
  pinMode(botonverde, INPUT);

  digitalWrite(ledrojo,LOW);
  digitalWrite(ledverde,LOW);

  Serial.begin(9600);

  randomSeed(analogRead(pinForRandom));

  
}

void loop() {
  if (victoria == 0 and mostradaSecuencia == 0){
    arraysecuencia[0] = 0;
    arraysecuencia[1] = 0;
    arraysecuencia[2] = 0;
    arraysecuencia[3] = 0;
    arraysecuencia[4] = 0;
    
    arraysecuencia[0]=random(1,3);
    arraysecuencia[1]=random(1,3);
    arraysecuencia[2]=random(1,3);
    
    Serial.print(arraysecuencia[0]);
    Serial.print(arraysecuencia[1]);
    Serial.println(arraysecuencia[2]);
    
    contadorRonda = 3;
    
    mostrarSecuencia();
    mostradaSecuencia = 1;
    
    condicionLectura = leerSecuencia();
    if (condicionLectura == 0){
      victoria = 0;
      // Perdiste
      secuenciaDerrota();
    }
    else{
      victoria = victoria + 1;
    }
    mostradaSecuencia = 0;
    botonesPulsados = 0;
    delay(1000);
  
  }
  if (victoria == 1 and mostradaSecuencia == 0) {
    arraysecuencia[3]=random(1,3);
    contadorRonda = 4;
    
    mostrarSecuencia();
    mostradaSecuencia = 1;
    
    condicionLectura = leerSecuencia();
    if (condicionLectura == 0){
      victoria = 0;
      // Perdiste
      secuenciaDerrota();
    }
    else{
      victoria = victoria + 1;
    }
    mostradaSecuencia = 0;
    botonesPulsados = 0;
    delay(1000);
  }
  if (victoria == 2 and mostradaSecuencia == 0) {
    arraysecuencia[4]=random(1,3);
    contadorRonda = 5;
    
    mostrarSecuencia();
    mostradaSecuencia = 1;
    
    condicionLectura = leerSecuencia();
    if (condicionLectura == 0){
      victoria = 0;
      // Perdiste
      secuenciaDerrota();
    }
    else{
      victoria = victoria + 1;
    }
    mostradaSecuencia = 0;
    botonesPulsados = 0;
    delay(1000);
  }
  if (victoria == 3) {
    secuenciaVictoria();
  }
  
  

}
void secuenciaDerrota() {
  for (int i = 0; i < 6; i++) {
    int duration = durations[i];
    tone(piezoPin, melodyLose[i], duration);
    delay(duration * 1.3); // tiny pause between notes
  }
  noTone(piezoPin); // shut the piezo up
  while(true) {
    digitalWrite(ledazul,HIGH);
    delay(1000);
    digitalWrite(ledazul,LOW);
    delay(1000);
  }
  
}
void secuenciaVictoria() {
  
  for (int i = 0; i < 6; i++) {
    int duration = winDurations[i];
    tone(piezoPin, melodyWin[i], duration);
    delay(duration * 1.3); // tiny pause between notes
  }
  noTone(piezoPin);
  while(true) {
    digitalWrite(ledverde,LOW);
    delay(100);
    digitalWrite(ledazul,HIGH);
    delay(100);
    digitalWrite(ledrojo,HIGH);
    delay(100);
    digitalWrite(ledazul,LOW);
    delay(100);
    digitalWrite(ledverde,HIGH);
    delay(100);
    digitalWrite(ledrojo,LOW);
    delay(100);
  }
  
}

void mostrarSecuencia(){
  
  for (int i=0; i<contadorRonda; i++){
      if (arraysecuencia[i]==1){
        digitalWrite(ledrojo,HIGH);
        delay(1000);
        digitalWrite(ledrojo,LOW);
        delay(1000);
      }
      if (arraysecuencia[i]==2){
        digitalWrite(ledverde,HIGH);
        delay(1000);
        digitalWrite(ledverde,LOW);
        delay(1000);
      }
  }
}

int leerSecuencia(){
  for (int i = 0; i < contadorRonda; i++) {
    Serial.println(arraysecuencia[i]);
    Serial.println("Leyendo secuencia :");
    while(botonesPulsados-1 < i) {
      
      if(digitalRead(botonrojo) == HIGH and arraysecuencia[i] != 1) {
        Serial.println("Rojo, incorrecto");
        delay(400);
        // Condicion fallida
        return 0;
      }
      if(digitalRead(botonrojo) == HIGH and arraysecuencia[i] == 1) {
        Serial.println("Rojo, correcto");
        delay(400);
        // Condicion Correcta
        botonesPulsados = botonesPulsados + 1;
      
      }
      if(digitalRead(botonverde) == HIGH and arraysecuencia[i] == 2) {
        Serial.println("Verde, correcto");
        delay(400);
        // Condicion Correcta
        botonesPulsados = botonesPulsados + 1;
      }
      if(digitalRead(botonverde) == HIGH and arraysecuencia[i] != 2) {
        Serial.println("Verde, incorrecto");
        delay(400);
        // Condicion fallida
        return 0;
      }
      
    }
  }
  if (botonesPulsados == contadorRonda) {
    return 1;
  }
}
