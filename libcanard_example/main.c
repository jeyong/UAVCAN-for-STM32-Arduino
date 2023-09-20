#include "Arduino.h"
#include "stm32yyxx_ll.h"


const int PwmOutputPin = PA0;         // PA_0,D46/A0 -- USES TIM2
const int TestOutputPin = PA6;

unsigned long previousMillis = 0;     // stores last time output was updated
const long interval = 1000;           // interval at which to print output (milliseconds)

void setup() {

  printInitMsg();
  println();

  // digital pin 초기화
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PwmOutputPin, OUTPUT);
  pinMode(TestOutputPin, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

//  uint32_t ret = DWT_Delay_Init();

  // STM32 CAN 초기화
  CAN_HW_Init();

  // uavcan 초기화
  uavcanInit();

}

void loop() {

  unsigned long currentMillis;

  currentMillis = millis();

  sendCanard();
  receiveCanard();
  spinCanard();
  publishCanard();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    showRcpwmonUart();
  }

}
