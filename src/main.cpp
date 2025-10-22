#include <Arduino.h>
#include <ArduinoSTL.h>
#include <SwitchControlLibrary.h>

#define TEST // LRボタンを押す動き
#define VERSION 3 // versionの切り替え

// ピンの設定
#define PIN_LED 13

#define PIN_WALK 3
#define PIN_DOWN 4
#define PIN_UP 5
#define PIN_RUN 6
#define PIN_BACK 7
#define PIN_STOP 8

void setup() {
  pinMode(PIN_LED, OUTPUT);
  for (int i = PIN_WALK; i <= PIN_STOP; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  SwitchControlLibrary();
  delay(1000);

#ifdef TEST
  digitalWrite(PIN_LED, HIGH);
  for (int i = 0; i < 2; i++) {
    SwitchControlLibrary().pressButton(Button::L);
    SwitchControlLibrary().pressButton(Button::R);
    SwitchControlLibrary().sendReport();
    delay(100);
    SwitchControlLibrary().releaseButton(Button::L);
    SwitchControlLibrary().releaseButton(Button::R);
    SwitchControlLibrary().sendReport();
    delay(100);
  }
  digitalWrite(PIN_LED, LOW);
  delay(1000);

#endif // TEST

  SwitchControlLibrary().pressButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::MAX, Stick::MIN);
  SwitchControlLibrary().sendReport();
  delay(1000);
  SwitchControlLibrary().releaseButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(1000);
}

int delta = 0;

void loop() {
  // SwitchControlLibrary().moveLeftStick(lx, ly);
  // Left, Up   : 0 (Stick::MIN)
  // Right, Down: 255 (Stick::MAX)
  // Newtral    : 128 (Stick::NEUTRAL)

/* --- version 4 --- */
/*
  version3の動きを基本として、カナリィの手前で斜め前に進むことで密着を狙う
  これから作る
*/
#if VERSION == 4
  // write here
#endif

/* --- version 3 --- */
/*
  カナリィの右奥にある角で原点出しをする方法
  真正面から当たろうとするとどちらに行くかわからないことが判明した
*/
#if VERSION == 3
  // v3
  SwitchControlLibrary().moveLeftStick(Stick::MIN + Stick::NEUTRAL/3*2, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(660 + delta); // ここで頑張る
  delta += 1;
  // x 
  // x  
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(1000);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MAX);
  SwitchControlLibrary().sendReport();
  delay(6000);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();

  // while (digitalRead(PIN_WALK));
  delay(1000);

  SwitchControlLibrary().pressButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MIN);
  SwitchControlLibrary().sendReport();
  delay(3500);
  SwitchControlLibrary().releaseButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::MAX, Stick::MIN);
  SwitchControlLibrary().sendReport();
  delay(1000);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(1000);

  // while (digitalRead(PIN_WALK));
  delay(1000);

#endif

/* --- version 2 --- */
/*
  ラシーヌ工務店の入り口から、左右方向は椅子、前後方向はドアに当たることで位置を揃えることにした
  対象(カナリィ)から遠すぎる気がした
*/
#if VERSION == 2
  // v2
  SwitchControlLibrary().pressButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MIN);
  SwitchControlLibrary().sendReport();
  delay(900);
  SwitchControlLibrary().releaseButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::MAX, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(2500);
  SwitchControlLibrary().pressButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MIN + Stick::NEUTRAL/3.25);
  SwitchControlLibrary().sendReport();
  delay(9194 + delta);
  // delayMicroseconds(500 + delta); // ここを頑張る
  SwitchControlLibrary().releaseButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::MAX, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(5000);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();

  while (digitalRead(PIN_WALK)) {
    digitalWrite(PIN_LED, HIGH);
    delay(250);
    digitalWrite(PIN_LED, LOW);
    delay(250);
  }

  // 帰り
  SwitchControlLibrary().pressButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MAX);
  SwitchControlLibrary().sendReport();
  delay(2500);
  SwitchControlLibrary().releaseButton(Button::B);
  SwitchControlLibrary().moveLeftStick(Stick::MIN, Stick::NEUTRAL);
  SwitchControlLibrary().sendReport();
  delay(3000);
  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MAX);
  SwitchControlLibrary().sendReport();
  delay(1500);
  SwitchControlLibrary().pressButton(Button::A);
  SwitchControlLibrary().sendReport();
  delay(100);
  SwitchControlLibrary().releaseButton(Button::A);
  SwitchControlLibrary().sendReport();
  delay(3000);

  SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
  SwitchControlLibrary().pressButton(Button::A);
  SwitchControlLibrary().sendReport();
  delay(100);
  SwitchControlLibrary().releaseButton(Button::A);
  SwitchControlLibrary().sendReport();
  // delay(2000);

  while (digitalRead(PIN_WALK)) {
    digitalWrite(PIN_LED, HIGH);
    delay(250);
    digitalWrite(PIN_LED, LOW);
    delay(250);
  }

  delta += 1;

#endif

/* --- version 1 --- */
/*
  自動で横方向に直進したまま、上下ボタンを押して調整しようとした 
  操作が難しくて断念、自動化を決意
*/
#if VERSION == 1
  // v1
  int state_walk = 0;
  // 0: stop
  // 1: walk back
  // 2: walk forward
  // 3: run forward

  while (true) {
    if (!digitalRead(PIN_RUN))  state_walk = 3;
    if (!digitalRead(PIN_WALK)) state_walk = 2;
    if (!digitalRead(PIN_BACK)) state_walk = 1;
    if (!digitalRead(PIN_STOP)) state_walk = 0;

    int lx = Stick::NEUTRAL;
    switch (state_walk) {
      case 1: // back
        lx -= (int)(Stick::NEUTRAL/1.5);
        break;
      case 2: // walk
        lx += (int)(Stick::NEUTRAL/3.25);
        break;
      case 3: // run
        lx = Stick::MAX;
        break;
    }

    int ly = Stick::NEUTRAL;
    if (!digitalRead(PIN_UP)) ly -= Stick::NEUTRAL/5;
    if (!digitalRead(PIN_DOWN)) ly += Stick::NEUTRAL/5;

    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().sendReport();
    // delay(10);
  }
#endif
  
}