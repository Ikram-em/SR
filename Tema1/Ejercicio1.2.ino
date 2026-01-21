int ledrojo = 2;
int ledverde = 3;

int botonrojo =7;
int botonverde =8;

int mostradaSecuencia = 0;

int contadorRonda = 0;
int condicionLectura = 0;
int botonesPulsados = 0;

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
    Serial.print(arraysecuencia[2]);
    
    contadorRonda = 3;
    
    mostrarSecuencia();
    mostradaSecuencia = 1;
    
    condicionLectura = leerSecuencia();
    if (condicionLectura == 0){
      victoria = 0;
      // Perdiste
      Serial.print("b");
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
void secuenciaVictoria() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledrojo,HIGH);
    digitalWrite(ledverde,HIGH);
    delay(1000);
    digitalWrite(ledrojo,LOW);
    digitalWrite(ledverde,LOW);
    delay(1000);
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
    Serial.print("a");
    while(botonesPulsados < contadorRonda) {
      
      if(digitalRead(botonrojo) == HIGH and arraysecuencia[i] != 1) {
        Serial.println("boton Pulsado");
        delay(400);
        // Condicion fallida
        return 0;
      }
      if(digitalRead(botonrojo) == HIGH and arraysecuencia[i] == 1) {
        Serial.println("boton Pulsado");
        delay(400);
        // Condicion Correcta
        botonesPulsados = botonesPulsados + 1;
      
      }
      if(digitalRead(botonverde) == HIGH and arraysecuencia[i] != 2) {
        Serial.println("boton Pulsado");
        delay(400);
        // Condicion fallida
        return 0;
      }
      if(digitalRead(botonrojo) == HIGH and arraysecuencia[i] == 2) {
        Serial.println("boton Pulsado");
        delay(400);
        // Condicion Correcta
        botonesPulsados = botonesPulsados + 1;
      }
    }
  }
  if (botonesPulsados == contadorRonda) {
    return 1;
  }
}
