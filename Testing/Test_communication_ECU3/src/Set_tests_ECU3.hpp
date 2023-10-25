/************************************************** *********************
ECU 3 (display) testing communication and power
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of test cases for the communication and power of the ECU 3.
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
const int powerPin = A0;

// Function to test if the Arduino is running
void test_ECU3_Is_On(void) {
  // Measures the supply voltage
  int voltage = analogRead(powerPin);
  // Check if the tension is correct  (0 - 1023 | 0v -5v)
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
        if (canMsg.can_id == 0x0E3) {
          messageReceived = true;
          break;
        }
      }
    }

    // Check if a message was received
    TEST_ASSERT_TRUE_MESSAGE(messageReceived, "Messages could not be received.");
  }
}