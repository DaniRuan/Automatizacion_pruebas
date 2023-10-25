/************************************************** *********************
ECU 2 Test Cases (Windshield Wipers)
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of the test cases for ECU 2 stipulated in the
documentation.
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Servo.h>
#define CS_PIN 10 // Chip Select pin for MCP2515
#define TIMEOUT_MS 5000 // Timeout for message reception in milliseconds


MCP2515 mcp(CS_PIN);
unsigned long startTime;
Servo myservo;
int pos = 0;
const int powerPin = A0;

void set_servo(void){
  myservo.attach(3); // Pin signal pwm servo
}

// Function to test if the Arduino is running
void test_ECU2_Is_On(void) {
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
        if (canMsg.can_id == 0x0E2) {
          messageReceived = true;
          break;
        }
      }
    }

    // Check if a message was received
    TEST_ASSERT_TRUE_MESSAGE(messageReceived, "Messages could not be received.");
  }
}

// Function to test the functionality in mode = 0
void test_wipers_operation_0(void){
  int oscilations=0;
  set_servo();
  if (oscilations < 1) {
    for (int angle = 0; angle <= 80; angle += 1){
      pos = map(angle, 0, 80, 0, 80); 
      myservo.write(pos);
      delay(9);
      //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read()); // Check if the servo's position matches the expected angle
    }

    for (int angle = 80; angle >= 0; angle -= 1){
      pos = map(angle, 0, 80, 0, 80);
      myservo.write(pos);
      delay(9);
      //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read()); // Check if the servo's position matches the expected angle
    }

    oscilations++;
  }
  // Detiene el bucle loop()
  else {
    while (true) {
      // bucle infinito
    }
  }
  // Make an assertion that ensures only one oscillation has occurred
  TEST_ASSERT_EQUAL(1, oscilations);
}

// Function to test the functionality in mode = 1
void test_wipers_operation_1(void){
  set_servo();
  for (int angle = 0; angle <= 80; angle += 1) {
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read()); // Check if the servo's position matches the expected angle
  }

  for (int angle = 80; angle >= 0; angle -= 1) {
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read()); // Check if the servo's position matches the expected angle
  }
  delay(5000);
}

// Function to test the functionality in mode = 2
void test_wipers_operation_2(void){
  set_servo();
  for (int angle = 0; angle <= 80; angle += 1) {
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    //check if the servo's position matches the expected angle within a tolerance
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read());
  }

  for (int angle = 80; angle >= 0; angle -= 1) {
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    // check if the servo's position matches the expected angle within a tolerance
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read());
  }
    delay(1000);
}


// Function to test the functionality in mode = 3
void test_wipers_operation_3(void){
  set_servo();
  for (int angle = 0; angle <= 80; angle += 1){
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    //check if the servo's position matches the expected angle within a tolerance
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read());
  }

  for (int angle = 80; angle >= 0; angle -= 1){
    pos = map(angle, 0, 80, 0, 80);
    myservo.write(pos);
    delay(9);
    //check if the servo's position matches the expected angle within a tolerance
    //TEST_ASSERT_INT_WITHIN(2, pos, myservo.read());
  }
}