#include <Adafruit_NeoPixel.h>

const int personsignalGreen = 2;
const int personsignalRed = 3;
const int carsignalGreen = 4;
const int carsignalYellow = 5;
const int carsignalRed = 6;
const int BUZZER_PIN = A2;
const int PIR_PIN = 18;

// 7세그먼트 디스플레이 핀 설정
const int segmentPins[] = {7, 8, 9, 10, 11, 12, 13};

//NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, A5, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(personsignalGreen, OUTPUT);
  pinMode(personsignalRed, OUTPUT);
  pinMode(carsignalGreen, OUTPUT);
  pinMode(carsignalYellow, OUTPUT);
  pinMode(carsignalRed, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
  strip.setBrightness(255);
  strip.begin();
  strip.show();

  digitalWrite(personsignalGreen, LOW);
  digitalWrite(personsignalRed, HIGH);
  digitalWrite(carsignalGreen, HIGH);
  digitalWrite(carsignalYellow, LOW);
  digitalWrite(carsignalRed, LOW);

  int pir_state = 0;

  // 7세그먼트 디스플레이 핀을 출력으로 설정
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], INPUT);
  }
}

void loop() {
  // NeoPixel
  int light = analogRead(A3);
  delay(50);
  if (light > 940) {
    for (int a = 0; a < 4; a++) {
      strip.setPixelColor(a, 255, 0, 0);
    }
    for (int b = 4; b < 10; b++) {
      strip.setPixelColor(b, 0, 255, 0);
    }
    for (int c = 10; c < 14; c++) {
      strip.setPixelColor(c, 255, 0, 0);
    }
    strip.show();
  }
  else {
    for (int a = 0; a < 4; a++) {
      strip.setPixelColor(a, 0, 0, 0);
    }
    for (int b = 4; b < 10; b++) {
      strip.setPixelColor(b, 0, 0, 0);
    }
    for (int c = 10; c < 14; c++) {
      strip.setPixelColor(c, 0, 0, 0);
    }
    strip.show();
  }
  delay(10);

  int pir_state = digitalRead(PIR_PIN);
  Serial.println(light);

  if (pir_state == 1) {
    digitalWrite(carsignalGreen, LOW);
    digitalWrite(carsignalYellow, HIGH);
    delay(700);
    digitalWrite(carsignalYellow, LOW);
    digitalWrite(carsignalRed, HIGH);
    digitalWrite(personsignalRed, LOW);
    digitalWrite(personsignalGreen, HIGH);

    // NeoPixel
    if (light > 940) {
      for (int a = 0; a < 4; a++) {
        strip.setPixelColor(a, 0, 255, 0);
      }
      for (int b = 4; b < 10; b++) {
        strip.setPixelColor(b, 255, 0, 0);
      }
      for (int c = 10; c < 14; c++) {
        strip.setPixelColor(c, 0, 255, 0);
      }

      strip.show();
    }
    else {
      for (int a = 0; a < 4; a++) {
        strip.setPixelColor(a, 0, 0, 0);
      }
      for (int b = 4; b < 10; b++) {
        strip.setPixelColor(b, 0, 0, 0);
      }
      for (int c = 10; c < 14; c++) {
        strip.setPixelColor(c, 0, 0, 0);
      }
      strip.show();
    }

    // 5초부터 1초까지 카운트 다운 표시
    for (int i = 0; i < 7; i++) {
      pinMode(segmentPins[i], OUTPUT);
    }
    for (int count = 5; count >= 1; count--) {
      displayDigit(count);
      if (light > 940) {
        tone(A2, 110, 200);
        delay(200);
        tone(A2, 0, 100);
        delay(100);
        tone(A2, 110, 300);
        delay(300);
        tone(A2, 0, 400);
        delay(400);
      }
      else {
        delay(1000);
      }
    }

    digitalWrite(BUZZER_PIN, LOW);

    // personsignalGreen를 5초 동안 유지 후 복귀
    digitalWrite(personsignalGreen, LOW);
    digitalWrite(personsignalRed, HIGH);
    digitalWrite(carsignalGreen, HIGH);
    digitalWrite(carsignalYellow, LOW);
    digitalWrite(carsignalRed, LOW);
    for (int i = 0; i < 7; i++) { //7세그먼트 꺼짐
      pinMode(segmentPins[i], INPUT);
      // NeoPixel 복귀
      if (light > 940) {
        for (int a = 0; a < 4; a++) {
          strip.setPixelColor(a, 255, 0, 0);
        }
        for (int b = 4; b < 10; b++) {
          strip.setPixelColor(b, 0, 255, 0);
        }
        for (int c = 10; c < 14; c++) {
          strip.setPixelColor(c, 255, 0, 0);
        }
        strip.show();
      }
      else {
        for (int a = 0; a < 4; a++) {
          strip.setPixelColor(a, 0, 0, 0);
        }
        for (int b = 4; b < 10; b++) {
          strip.setPixelColor(b, 0, 0, 0);
        }
        for (int c = 10; c < 14; c++) {
          strip.setPixelColor(c, 0, 0, 0);
        }
        strip.show();
      }
    }
    int pir_state = 0;
    // PIR_PIN을 10.7초 동안 감지하지 못하도록 함
    delay(5700); // 10.7(5.7+5)초 동안 PIR 센서 비활성화
  }
  else {
    delay(10);
  }
}



// 7세그먼트 디스플레이에 숫자를 표시하는 함수
void displayDigit(int digit) {
  // 7세그먼트 숫자 패턴 설정
  byte patterns[] = {
    B11000000, // 0
    B11110101, // 1
    B00101000, // 2
    B10110000, // 3
    B10010101, // 4
    B10010010, // 5
    B10000010, // 6
    B11111000, // 7
    B10000000, // 8
    B10010000  // 9
  };

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(patterns[digit], i));
  }
}
