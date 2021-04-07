/*  Gesture Controlled Robotic Arm
 *  Tx - the master or the transmitter
 *  by Team MRIT-2020
 *  
 *  nRF24L01 Modules CONNECTIONS:  
 *  1 - GND
 *  2 - VCC 3.3V !!! NOT 5V
 *  3 - CE to Arduino pin 9
 *  4 - CSN to Arduino pin 10
 *  5 - SCK to Arduino pin 13
 *  6 - MOSI to Arduino pin 11
 *  7 - MISO to Arduino pin 12
 *  8 - UNUSED
 *  
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define THUMB_PIN A0
#define INDEX_PIN A1
#define MIDDLE_PIN A2
#define RING_PIN A3
#define PINKY_PIN A4

// Pin Connections
#define pinCE_NRF 7     
#define pinCSN_NRF 8

// Create an RF24 object
RF24 radio(pinCE_NRF, pinCSN_NRF);

// Address through which two modules communicate.
const byte address[6] = "00001";

int values[5];

void setup() {
  analogReference(EXTERNAL);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  values[0] = analogRead(THUMB_PIN);
  values[1] = analogRead(INDEX_PIN);
  values[2] = analogRead(MIDDLE_PIN);
  values[3] = analogRead(RING_PIN);
  values[4] = analogRead(PINKY_PIN);  
  radio.write(values, sizeof(values));
  delay(200);
}
