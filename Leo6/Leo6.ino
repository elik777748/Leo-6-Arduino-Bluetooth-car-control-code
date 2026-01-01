


// code made a elik7777
// company R0B0C0DE


//---------------Setting LEO 6---------------------
                                                //-
//number                                        //-
bool LeoNumberOn = true;                        //-
unsigned int LeoNumber = 1;                     //-
                                                //-
//speed default                                 //-
unsigned int speed = 150;  //not: speeed < 150  //-
                                                //-
//--------------------------------------------------


#include <Servo.h>
#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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
unsigned long avariaTimer = 0;
bool avariaState = false;
bool avaria;
unsigned int color = 0;
const unsigned long avariaInterval = 1000;
bool six_seven = false;
bool lastButtonState = LOW;
unsigned long prevMillis = 0;
const int multiplexInterval = 5;
bool showTens = true;
Servo servo;
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
  servo.write(73);
}
void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  servo.attach(11);
  servo.write(servo_defalt);
  Serial.begin(9600);
  Serial3.begin(9600);
  FastLED.addLeds<WS2812, 42, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  int segments[] = { A, B, C, D, E, F, G };
  for (int i = 0; i < 7; i++) pinMode(segments[i], OUTPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = backword_led ? CRGB::Red : CRGB::Black;
  }
  FastLED.show();
  pinMode(TENS, OUTPUT);
  pinMode(ONES, OUTPUT);
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
}
void loop() {
  updateSong();
  int colorIndex = map(analogRead(3), 0, 1023, 0, 10);
  int sounds = map(analogRead(2), 0, 1000, 0, 5);
  if (sounds != lastPotValue) {
    lastPotValue = sounds;
    lastChangeTime = millis();
    cleared = false;

    displayDigitSegment(sounds, true);
    on_six_seven = false;
  }

  if (!cleared && millis() - lastChangeTime >= 3000) {
    clearDisplaySegment();
    cleared = true;
    on_six_seven = true;
  }




  if (digitalRead(17) == 1) {
    if (sounds == 0) {
      stopAllSounds();
    } else {
      startSong(sounds - 1);
    }
  }

  Serial.println(sounds);
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

    speed = speedrn;
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
