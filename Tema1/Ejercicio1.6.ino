// Use PWM-capable pins
int led1R = 9;
int led1G = 10;
int led1B = 11;

int led2R = 3;
int led2G = 5;
int led2B = 6;

// Altavoz piezo
int buzzer = 7;

int oldValSound = 0;

// Potenciómetros
int potLeds = A0;
int potSound = A1;

void setup() {
  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);
  Serial.begin(9600);

  pinMode(led2R, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2B, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

// Función arcoíris (0–255 → r,g,b)
void rainbowColor(int value, int &r, int &g, int &b) {
  byte region = value / 43;
  byte remainder = (value - (region * 43)) * 6;

  switch (region) {
    case 0: r = 255; g = remainder; b = 0; break;
    case 1: r = 255 - remainder; g = 255; b = 0; break;
    case 2: r = 0; g = 255; b = remainder; break;
    case 3: r = 0; g = 255 - remainder; b = 255; break;
    case 4: r = remainder; g = 0; b = 255; break;
    default: r = 255; g = 0; b = 255 - remainder; break;
  }
}

void loop() {
  // --- CONTROL LEDs ---
 
  int valLeds = analogRead(potLeds);   // 0–1023 → controla solo LEDs
  int colorVal = map(valLeds, 0, 1023, 0, 255);

  // Color base arcoíris
  int rBase, gBase, bBase;
  rainbowColor(colorVal, rBase, gBase, bBase);

  // Brillo proporcional para cada LED
  int brightness1 = map(valLeds, 0, 1023, 0, 255);
  int brightness2 = 255 - brightness1;

  int r1 = (rBase * brightness1) / 255;
  int g1 = (gBase * brightness1) / 255;
  int b1 = (bBase * brightness1) / 255;

  int r2 = (rBase * brightness2) / 255;
  int g2 = (gBase * brightness2) / 255;
  int b2 = (bBase * brightness2) / 255;

  analogWrite(led1R, r1);
  analogWrite(led1G, g1);
  analogWrite(led1B, b1);

  analogWrite(led2R, r2);
  analogWrite(led2G, g2);
  analogWrite(led2B, b2);

  // --- CONTROL BUZZER ---
  int valSound = analogRead(potSound); // 0–1023

  
  // if value changed, beep once
  Serial.print(valSound);
  if (valSound < oldValSound-15 ||valSound > oldValSound+15  ) {
    Serial.println("dentro ");
    oldValSound = valSound;  // update memory

    int freq = map(valSound, 0, 1023, 200, 2000); // pick a freq range you like

    tone(buzzer, freq);   // start sound
    delay(30);            // keep it for 30 ms
    noTone(buzzer);       // then stop
  }

  // small delay to stabilize readings
  delay(5);
  
  }
  
  
