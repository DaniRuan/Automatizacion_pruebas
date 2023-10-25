/************************************************** *********************
ECU 1 Test Cases (Directional)
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of the test cases for ECU 1 stipulated in the
documentation.
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>
#include <mcp2515.h>
#define CS_PIN 10 // Chip Select pin for MCP2515
#define TIMEOUT_MS 5000 // Timeout for message reception in milliseconds

MCP2515 mcp(CS_PIN);
unsigned long startTime;
byte pinLED[6] = {2,3,4,5,6,7};
int t1=40;
int t2=500;
const int powerPin = A0;

void set_LEDs(void){
  for(int pin= 0; pin<6; pin++){
    pinMode(pinLED[pin], OUTPUT);  
  }
}

// Function to test if the Arduino is running
void test_ECU1_Is_On(void) {
  // Measures the supply voltage
  int voltage = analogRead(powerPin);
  // Check if the tension is correct  (0 - 1023 | 0 v -5v)
  TEST_ASSERT_GREATER_OR_EQUAL( voltage, 950);
}

// Function to test if the MCP25215 module is connected
void test_MCP2515_Module_Connected(void) {
  bool isMCP2515Connected = false;
  // Try to initialize the MCP2515
  SPI.begin();
  isMCP2515Connected = mcp.reset() == MCP2515::ERROR_OK;

  TEST_ASSERT_TRUE_MESSAGE(isMCP2515Connected, "MCP2515 module not connected.");
}

// Function to test communication
void test_CAN_Message_Receive(void) {
  bool module = false;

  SPI.begin();
  module = (mcp.reset() == MCP2515::ERROR_OK);
  if (module == false){
    TEST_FAIL_MESSAGE("Messages could not be received.");
  }
  else{
    mcp.setBitrate(CAN_125KBPS);
    mcp.setNormalMode();
    struct can_frame canMsg;
    unsigned long startTime = millis();
    bool messageReceived = false;

    while (millis() - startTime < TIMEOUT_MS) {
      if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) {
        if (canMsg.can_id == 0x0E1) {
          messageReceived = true;
          break;
        }
      }
    }

    // Check if a message was received
    TEST_ASSERT_TRUE_MESSAGE(messageReceived, "Messages could not be received.");
  }
}

// Function to test functionality in mode 0
void test_LED_Operation_0(void) {
    set_LEDs();
    for(int i=0; i<6;i++){
      digitalWrite(pinLED[i], LOW);     
    }

    // Check if the LED states are as expected after canMsg.data[0] == 0
  for(int i=0; i<6;i++){
    TEST_ASSERT_EQUAL(LOW, digitalRead(pinLED[i]));
  }
}

// Function to test functionality in mode 1
void test_LED_Operation_1(void) {
  set_LEDs();
  for(int i=0; i<6;i++){
    digitalWrite(pinLED[i], HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(pinLED[i]));
    delay(t1);
  }
  for(int i=0; i<6;i++){
    digitalWrite(pinLED[i], LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(pinLED[i]));
    delay(t1);
  }
}

// Function to test functionality in mode 2
void test_LED_Operation_2(void) {
  set_LEDs();
  for(int j=5; j>-1;j--){
    digitalWrite(pinLED[j], HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(pinLED[j]));
    delay(t1);      
  }

  for(int k=5; k>-1;k--){
      digitalWrite(pinLED[k], LOW);
      TEST_ASSERT_EQUAL(LOW, digitalRead(pinLED[k]));
      delay(t1);      
  }
}

// Function to test functionality in mode 3
void test_LED_Operation_3(void) {
  set_LEDs();
  for(int i=0; i<6;i++){
    digitalWrite(pinLED[i], HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(pinLED[i]));  
  }
  delay(t2);
  for(int i=0; i<6;i++){
    digitalWrite(pinLED[i], LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(pinLED[i]));    
  }
  delay(t2);
}
