


// code made a elik7777
// company R0B0C0DE


//---------------Setting LEO 6---------------------

//number
bool LeoNumberOn = true;
unsigned int LeoNumber = 1;

//speed default
unsigned int speed = 150;  //not: speeed < 150

//--------------------------------------------------


#include <Servo.h>
#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Sonar.h"
#include "melody.h"
#include "SevenSegmentDisplay.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
CRGB leds[8];
unsigned long lastChangeTime = 0;
int lastPotValue = 0;
bool on_six_seven = true;
bool cleared = false;
int buzzerPin = 31;
int speedrn = speed;
bool backword_led = false;
char dataBT;
char lastDataBT;
int prevColorIndex = -1;
int servo_defalt = 90;
bool zoomer;
bool forword_led;
bool drawToLSD = false;
unsigned long avariaTimer = 0;
bool saveWallState;
bool sonareState;
bool AlgoritmBlackLineState;
bool AlgoritmBlackLineStateFalse = false;
bool saveWall = false;
bool avariaState = false;
bool avaria;
bool avariaStateFalse = false;
unsigned int color = 0;
const unsigned long avariaInterval = 1000;
bool six_seven = false;
bool lastButtonState = LOW;
unsigned long prevMillis = 0;
bool StateState = false;
const int multiplexInterval = 5;
unsigned long startTime = 0;
bool isBacking = false;
bool showTens = true;
bool sonare = false;
bool AlgoritmBlackLine = false;
Servo servo;
int trigPin = 12;
int echoPin = 13;
int A = 32;
int B = 33;
int C = 34;
int D = 35;
int E = 36;
int F = 37;
int G = 38;
int H = 39;
int TENS = 41;
int ONES = 40;
CRGB colors[11] = {
  CRGB::Black,
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Yellow,
  CRGB::Cyan,
  CRGB::Magenta,
  CRGB::Orange,
  CRGB::Purple,
  CRGB::Pink,
  CRGB::White
};

int out[] = { A, B, C, D, E, F, G, H, 6, 7, 8, 9, 26, 27, 28, 29, 30, buzzerPin, TENS, ONES };
int in[] = { 16, 17 };

#define NUM_LEDS 8
void forword() {
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  analogWrite(5, speed);
  analogWrite(10, speed);
  servo.write(servo_defalt);
}

void backword() {
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  analogWrite(5, speed);
  analogWrite(10, speed);
  servo.write(servo_defalt);
}

void stop() {
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  servo.write(servo_defalt);
}

void super_left(bool a) {
  int b;
  int c;
  if (a == true) {
    b = 1;
    c = 0;
  } else {
    b = 0;
    c = 1;
  }

  digitalWrite(6, b);
  digitalWrite(7, c);
  digitalWrite(8, b);
  digitalWrite(9, c);
  analogWrite(5, speed);
  analogWrite(10, speed / 1.5);
  servo.write(20);
}

void super_rigth(bool a) {
  int b;
  int c;
  if (a == true) {
    b = 1;
    c = 0;
  } else {
    b = 0;
    c = 1;
  }
  digitalWrite(6, b);
  digitalWrite(7, c);
  digitalWrite(8, b);
  digitalWrite(9, c);
  analogWrite(5, speed / 1.5);
  analogWrite(10, speed);
  servo.write(160);
}

void rigth(bool a) {
  int b;
  int c;
  if (a == true) {
    b = 1;
    c = 0;
  } else {
    b = 0;
    c = 1;
  }
  digitalWrite(6, b);
  digitalWrite(7, c);
  digitalWrite(8, b);
  digitalWrite(9, c);
  analogWrite(5, speed);
  analogWrite(10, speed);
  servo.write(128);
}

void left(bool a) {
  int b;
  int c;
  if (a == true) {
    b = 1;
    c = 0;
  } else {
    b = 0;
    c = 1;
  }

  digitalWrite(6, b);
  digitalWrite(7, c);
  digitalWrite(8, b);
  digitalWrite(9, c);
  analogWrite(5, speed);
  analogWrite(10, speed);
  servo.write(53);
}
void setup() {
  servo.attach(11);
  servo.write(servo_defalt);
  Serial.begin(9600);
  Serial3.begin(9600);
  FastLED.addLeds<WS2812, 42, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  for (int i = 0; i < sizeof(out) / sizeof(out[0]); i++) pinMode(out[i], OUTPUT);
  for (int i = 0; i < sizeof(in) / sizeof(in[0]); i++) pinMode(in[i], INPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = backword_led ? CRGB::Red : CRGB::Black;
  }
  FastLED.show();
  clearDisplaySegment();
  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("R0B0C0DE");
  if (LeoNumberOn) {
    lcd.setCursor(5, 1);
    lcd.print("Leo");
    lcd.setCursor(9, 1);
    lcd.print(LeoNumber);
  }
  initSonar();
}
void loop() {
  unsigned int distance = getDistance();
  //Serial.println(distance);
  updateSong();
  int colorIndex = map(analogRead(3), 0, 1023, 0, 10);
  int potensometrA2 = map(analogRead(2), 0, 1000, 0, 5);
  if (potensometrA2 != lastPotValue) {
    lastPotValue = potensometrA2;
    lastChangeTime = millis();
    cleared = false;

    displayDigitSegment(potensometrA2, true);
    on_six_seven = false;
  }

  if (!cleared && millis() - lastChangeTime >= 3000) {
    clearDisplaySegment();
    cleared = true;
    on_six_seven = true;
  }

  if (analogRead(7) >= 500) {
    switch (potensometrA2) {
      case 0:
        sonare = false;
        AlgoritmBlackLine = false;
        saveWall = false;
        drawToLSD = false;
        displayDigitSegment(potensometrA2, true);
        break;
      case 1:
        sonare = true;
        AlgoritmBlackLine = false;
        saveWall = false;
        drawToLSD = false;
        displayDigitSegment(potensometrA2, true);
        break;
      case 2:
        sonare = false;
        AlgoritmBlackLine = true;
        saveWall = false;
        drawToLSD = false;
        displayDigitSegment(potensometrA2, true);
        break;
      case 3:
        sonare = false;
        AlgoritmBlackLine = false;
        saveWall = true;
        drawToLSD = false;
        displayDigitSegment(potensometrA2, true);
        break;
      case 4:
        sonare = false;
        AlgoritmBlackLine = false;
        saveWall = false;
        drawToLSD = true;
        displayDigitSegment(potensometrA2, true);
        break;
      case 5:
        sonare = false;
        AlgoritmBlackLine = false;
        saveWall = false;
        drawToLSD = false;
        displayDigitSegment(potensometrA2, true);
        break;
    }
  }

  if (saveWall) {
    if (distance < 25 && distance != 0 && !isBacking) {
      isBacking = true;
      startTime = millis();
    }
    if (isBacking) {
      backword();
      if (millis() - startTime >= 300) {
        stop();
        isBacking = false;
      }
      speed = speedrn;
      return;
    }
  }

  if (AlgoritmBlackLine) {
    AlgoritmBlackLineStateFalse = true;
    speed = 80;
    if (distance < 30 && distance != 0 && !isBacking) {
      isBacking = true;
      startTime = millis();
    }
    if (isBacking) {
      backword();
      if (millis() - startTime >= 1500) {
        stop();
        isBacking = false;
      }
      return;
    }
    int s4 = analogRead(4);
    int s5 = analogRead(5);
    // Serial.print("S4: ");
    // Serial.print(s4);
    // Serial.print(" S5: ");
    // Serial.println(s5);
    int sensor = 400;
    if (s4 > sensor && s5 <= sensor) {
      left(true);
      delay(100);
    } else if (s5 > sensor && s4 <= sensor) {
      rigth(true);
      delay(100);
    } else {
      forword();
    }
    delay(100);
  } else {
    if (AlgoritmBlackLineStateFalse) {
      AlgoritmBlackLineStateFalse = false;
      speed = speedrn;
      stop();
    }
  }

  if (sonare) {
    if (distance <= 200 && distance > 60) {
      digitalWrite(28, 0);
      digitalWrite(29, 0);
      digitalWrite(30, 1);
    } else if (distance <= 60 && distance > 20) {
      digitalWrite(28, 0);
      digitalWrite(29, 1);
      digitalWrite(30, 1);
    } else if (distance <= 20 && distance >= 0) {
      digitalWrite(28, 1);
      digitalWrite(29, 1);
      digitalWrite(30, 1);
    }
  } else {
    digitalWrite(28, 0);
    digitalWrite(29, 0);
    digitalWrite(30, 0);
  }
  if (digitalRead(17) == 1) {
    if (potensometrA2 == 0) {
      stopAllSounds();
    } else {
      startSong(potensometrA2 - 1);
    }
  }
  if (digitalRead(17) == 1) {
    speed = map(analogRead(0), 0, 1023, 0, 255);
    speedrn = speed;
    servo.write(map(analogRead(1), 0, 1023, 20, 160));
  }
  if (colorIndex != prevColorIndex) {

    prevColorIndex = colorIndex;

    switch (colorIndex) {
      case 0:
        fill_solid(leds, NUM_LEDS, colors[0]);
        FastLED.show();
        color = 0;
        break;
      case 1:
        fill_solid(leds, NUM_LEDS, colors[1]);
        FastLED.show();
        color = 1;
        break;
      case 2:
        fill_solid(leds, NUM_LEDS, colors[2]);
        FastLED.show();
        color = 2;
        break;
      case 3:
        fill_solid(leds, NUM_LEDS, colors[3]);
        FastLED.show();
        color = 3;
        break;
      case 4:
        fill_solid(leds, NUM_LEDS, colors[4]);
        FastLED.show();
        color = 4;
        break;
      case 5:
        fill_solid(leds, NUM_LEDS, colors[5]);
        FastLED.show();
        color = 5;
        break;
      case 6:
        fill_solid(leds, NUM_LEDS, colors[6]);
        FastLED.show();
        color = 6;
        break;
      case 7:
        fill_solid(leds, NUM_LEDS, colors[7]);
        FastLED.show();
        color = 7;
        break;
      case 8:
        fill_solid(leds, NUM_LEDS, colors[8]);
        FastLED.show();
        color = 8;
        break;
      case 9:
        fill_solid(leds, NUM_LEDS, colors[9]);
        FastLED.show();
        color = 9;
        break;
      case 10:
        fill_solid(leds, NUM_LEDS, colors[10]);
        FastLED.show();
        color = 10;
        break;
    }
  }


  bool currentButtonState = digitalRead(16);
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    six_seven = !six_seven;
  }
  lastButtonState = currentButtonState;
  if (on_six_seven) {
    if (six_seven) {
      unsigned long currentMillis = millis();
      if (currentMillis - prevMillis >= multiplexInterval) {
        prevMillis = currentMillis;
        showTens = !showTens;
        if (showTens) {
          displayDigitSegment(6, false);
        } else {
          displayDigitSegment(7, true);
        }
      }
    } else {
      clearDisplaySegment();
    }
  }
  if (avaria) {
    if (!StateState) {
      avariaStateFalse = true;
      StateState = true;
      sonareState = sonare;
      AlgoritmBlackLineState = AlgoritmBlackLine;
      saveWallState = saveWall;

      sonare = false;
      AlgoritmBlackLine = false;
      saveWall = false;
    }

    unsigned long now = millis();

    if (now - avariaTimer >= avariaInterval) {
      avariaTimer = now;
      avariaState = !avariaState;
    }

    if (avariaState) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
      FastLED.show();
      if (!zoomer) {
        tone(31, 700);
        zoomer = true;
      }
      digitalWrite(26, HIGH);
      digitalWrite(27, HIGH);
      speed = 0;
      stop();
    } else {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      noTone(31);
      zoomer = false;
      digitalWrite(26, LOW);
      digitalWrite(27, LOW);
      speed = 0;
      stop();
    }

  } else {
    if (StateState) {
      sonare = sonareState;
      AlgoritmBlackLine = AlgoritmBlackLineState;
      saveWall = saveWallState;
      StateState = false;
    }
    if (avariaStateFalse) {
      avariaStateFalse = false;
      speed = speedrn;
      stop();
    }
  }


  if (Serial3.available()) {
    char c = Serial3.read();
    if (c != '\n' && c != '\r') {
      dataBT = tolower(c);
      if (dataBT != lastDataBT) {
        Serial.println(dataBT);
      }
      lastDataBT = dataBT;
    }
  }

  switch (dataBT) {
    case 'f':
      forword();
      break;
    case 'b':
      backword();
      break;
    case 'l':
      super_left(true);
      break;
    case 'r':
      super_rigth(true);
      break;
    case 'g':
      left(true);
      break;
    case 'i':
      rigth(true);
      break;
    case '0':
      speed = 150;
      speedrn = speed;
      break;
    case '1':
      speed = 160;
      speedrn = speed;
      break;
    case '2':
      speed = 171;
      speedrn = speed;
      break;
    case '3':
      speed = 181;
      speedrn = speed;
      break;
    case '4':
      speed = 192;
      speedrn = speed;
      break;
    case '5':
      speed = 202;
      speedrn = speed;
      break;
    case '6':
      speed = 213;
      speedrn = speed;
      break;
    case '7':
      speed = 223;
      speedrn = speed;
      break;
    case '8':
      speed = 234;
      speedrn = speed;
      break;
    case '9':
      speed = 255;
      speedrn = speed;
      break;
    case 's':
      stop();
      break;
    case 'h':
      super_left(false);
      break;
    case 'j':
      super_rigth(false);
      break;
    case 'w':
      forword_led = !forword_led;
      if (forword_led) {
        digitalWrite(26, HIGH);
        digitalWrite(27, HIGH);

      } else {
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
      }
      delay(30);
      break;
    case 'v':
      zoomer = !zoomer;
      if (zoomer) {
        tone(31, 700);
      } else {
        noTone(31);
      }
      delay(30);
      break;
    case 'u':
      backword_led = !backword_led;

      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = backword_led ? CRGB::Red : colors[color];

      FastLED.show();
      delay(30);
      break;
    case 'x':
      avaria = !avaria;
      break;
  }
}
