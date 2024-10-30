#include <IRremote.hpp>

#define DECODE_NEC
#define IR_RECEIVE_PIN 11
#define EXCLUDE_UNIVERSAL_PROTOCOLS
#define EXCLUDE_EXOTIC_PROTOCOLS
#define MAX_INT 32767
#define MIN_INT -32768

const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;
const int common = 13;

bool isIncrementing = false;  // Flag for incrementing
bool isDecrementing = false;  // Flag for decrementing

// Current value of number to operate "Next" or "Prev"
int currentNumber = 0;

void setup() {
  Serial.begin(115200);
  // Connect IR Sensor
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  // Connect 7-segment display with common cathode mode
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(common, OUTPUT);
  digitalWrite(common, LOW);
}

void loop() {
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command) {
      case 0x0C:
        displayNumber(0);
        break;
      case 0x10:
        displayNumber(1);
        break;
      case 0x11:
        displayNumber(2);
        break;
      case 0x12:
        displayNumber(3);
        break;
      case 0x14:
        displayNumber(4);
        break;
      case 0x15:
        displayNumber(5);
        break;
      case 0x16:
        displayNumber(6);
        break;
      case 0x18:
        displayNumber(7);
        break;
      case 0x19:
        displayNumber(8);
        break;
      case 0x1A:
        displayNumber(9);
        break;
      case 0x09: // Button "Previous"
        displayNumber(MIN_INT);
        break;
      case 0x01: // Button "Next"
        displayNumber(MAX_INT);
        break;
      case 0x0A:
        isIncrementing = true;
        isDecrementing = false; 
        break;
      case 0x08:
        isDecrementing = true;
        isIncrementing = false; 
        break;
      default:
        Serial.println(IrReceiver.decodedIRData.command);
    }
    IrReceiver.resume();
  }
  if (isIncrementing && currentNumber < 9) {
      currentNumber++;
      displayNumber(currentNumber);
      delay(1000);
      }
   if (isDecrementing && currentNumber > 0) {
      currentNumber--;
      displayNumber(currentNumber);
      delay(1000);
    }
}

void displayNumber(int number) {
  // Turn all segments off, reset
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);

  // Change number to the next or previous value
  if (number == MAX_INT) {
    number = currentNumber + 1;
    if (number >= 10) {
      number = 0;
    }
  } else if (number == MIN_INT) {
    number = currentNumber - 1;
    if (number <= -1) {
      number = 9;
    }
  }

 // Turn on the segments for the given number
  switch ( number) {
    case 0:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      break;
    case 1:
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      break;
    case 2:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 3:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 4:
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 5:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 6:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 7:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      break;
    case 8:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 9:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
  }
  currentNumber = number;
}
