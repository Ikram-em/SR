/* 
Hecho por:
Martín Almoina Iglesias UO300717
Sergio Fernandez-Miranda Longo UO302282
Ikram El Mabrouk Morhnane UO301848
*/

int led1 =2;
int led2 =3;
int led3 = 4;
int boton = 7;

int pushed =0;
int pinForRandom = A0;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(boton, INPUT);

  
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);

  
 Serial.begin(9600);

 randomSeed(analogRead(pinForRandom));
}

void loop() {
  int lect = digitalRead(boton);
  if (lect == HIGH  && pushed == 0){
    
    
    int rand = random(1, 4);
    Serial.println(rand);
     digitalWrite(led1,LOW);
     digitalWrite(led2,LOW);
     digitalWrite(led3,LOW);
    if (rand >= 1){
      digitalWrite(led1,HIGH);
    }
    if (rand >= 2){
      digitalWrite(led2,HIGH);
    }
    if (rand >= 3){
      digitalWrite(led3,HIGH);
    }
    pushed = 1;
  } else if (lect == LOW && pushed == 1){
  pushed = 0;
  }

}
