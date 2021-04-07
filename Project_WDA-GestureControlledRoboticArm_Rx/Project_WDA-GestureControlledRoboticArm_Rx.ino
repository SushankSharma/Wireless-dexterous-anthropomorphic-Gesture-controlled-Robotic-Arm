/*  Gesture Controlled Robotic Arm
    Rx - the slave or the receiver
    by Team MRIT- 2020

    nRF24L01 Modules CONNECTIONS:
    1 - GND
    2 - VCC 3.3V !!! NOT 5V
    3 - CE to Arduino pin 9
    4 - CSN to Arduino pin 10
    5 - SCK to Arduino pin 13
    6 - MOSI to Arduino pin 11
    7 - MISO to Arduino pin 12
    8 - UNUSED

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// Pin Connections
#define THUMB_PIN 3
#define INDEX_PIN 5
#define MIDDLE_PIN 6
#define RING_PIN 9
#define PINKY_PIN 10
#define pinCE_NRF 7
#define pinCSN_NRF 8

// RF24 object
RF24 radio(pinCE_NRF, pinCSN_NRF);

// Address through which two modules communicate.
const byte address[6] = "00001";

// Variables
int values[5];

Servo srvThumb;
Servo srvIndex;
Servo srvMiddle;
Servo srvRing;
Servo srvPinky;

int thumbPosMin = 40, thumbPosMax = 110, thumbPos;
int indexPosMin = 30, indexPosMax = 100, indexPos;
int middlePosMin = 5, middlePosMax = 95, middlePos;
int ringPosMin = 25, ringPosMax = 90, ringPos;
int pinkyPosMin = 25, pinkyPosMax = 90, pinkyPos;

int thumbValMin = 0, thumbValMax = 0, thumbVal;
int indexValMin = 0, indexValMax = 0, indexVal;
int middleValMin = 0, middleValMax = 0, middleVal;
int ringValMin = 0, ringValMax = 0, ringVal;
int pinkyValMin = 0, pinkyValMax = 0, pinkyVal;

int count = 1;
unsigned long checkout = millis();

void setup() {
  Serial.begin(9600);
  restPositions();
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //  closeAllFingers();
}

// Open all fingers
void restPositions() {
  srvThumb.attach(THUMB_PIN);
  srvThumb.write(thumbPosMax); // 110 - 40

  srvIndex.attach(INDEX_PIN);
  srvIndex.write(indexPosMax);  // 100 - 30

  srvMiddle.attach(MIDDLE_PIN);
  srvMiddle.write(middlePosMax);  // 90 - 10

  srvRing.attach(RING_PIN);
  srvRing.write(ringPosMax);  // 90 -30

  srvPinky.attach(PINKY_PIN);
  srvPinky.write(pinkyPosMax); // 90 - 30
  delay(3000);
}

// Close all fingers
void closeAllFingers() {
  srvThumb.write(thumbPosMin);
  srvIndex.write(indexPosMin);
  srvMiddle.write(middlePosMin);
  srvRing.write(ringPosMin);
  srvPinky.write(pinkyPosMin);
  delay(2000);
}

void loop() {
  while (millis() - checkout < 1000) {
    if (radio.available()) {
      radio.read(values, sizeof(values));
      thumbVal = values[0];
      indexVal = values[1];
      middleVal = values[2];
      ringVal = values[3];
      pinkyVal = values[4];

      Serial.print(thumbVal);
      Serial.print("\t");
      Serial.print(indexVal);
      Serial.print("\t");
      Serial.print(middleVal);
      Serial.print("\t");
      Serial.print(ringVal);
      Serial.print("\t");
      Serial.println(pinkyVal);

      thumbPos = map(thumbVal, 310, 428, thumbPosMin, thumbPosMax);
      indexPos = map(indexVal, 426, 510, indexPosMin, indexPosMax);
      middlePos = map(middleVal, 285, 350, middlePosMin, middlePosMax);
      ringPos = map(ringVal, 200, 240, ringPosMin, ringPosMax);
      pinkyPos = map(pinkyVal, 350, 447, pinkyPosMin, pinkyPosMax);

      Serial.print(thumbPos);
      Serial.print("\t");
      Serial.print(indexPos);
      Serial.print("\t");
      Serial.print(middlePos);
      Serial.print("\t");
      Serial.print(ringPos);
      Serial.print("\t");
      Serial.println(pinkyPos);
      Serial.println();      
    }
  }

  if (thumbPos < thumbPosMin) {
    thumbPos = thumbPosMin;
  } else if (thumbPos > thumbPosMax) {
    thumbPos = thumbPosMax;
  }

  if (indexPos < indexPosMin) {
    indexPos = indexPosMin;
  } else if (thumbPos > indexPosMax) {
    indexPos = indexPosMax;
  }

  if (middlePos < middlePosMin) {
    middlePos = middlePosMin;
  } else if (thumbPos > middlePosMax) {
    middlePos = middlePosMax;
  }

  if (ringPos < ringPosMin) {
    ringPos = ringPosMin;
  } else if (thumbPos > ringPosMax) {
    ringPos = ringPosMax;
  }

  if (pinkyPos < pinkyPosMin) {
    pinkyPos = pinkyPosMin;
  } else if (thumbPos > pinkyPosMax) {
    pinkyPos = pinkyPosMax;
  }

  srvThumb.write(thumbPos);
  srvIndex.write(indexPos);
  srvMiddle.write(middlePos);
  srvRing.write(ringPos);
  srvPinky.write(pinkyPos);
  checkout = millis();
}
