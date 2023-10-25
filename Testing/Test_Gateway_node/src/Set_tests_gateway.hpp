/************************************************** *********************
Gateway Test Cases (master node)
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of the test cases for the Gateway node stipulated in the
documentation.
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>
#include <mcp2515.h>

#define CS_PIN 53 // Chip Select pin for MCP2515
MCP2515 mcp(CS_PIN);

// Function to test if the Arduino is running
void test_Gateway_Is_On(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

// Function to test if the MCP25215 module is connected
void test_MCP2515_Module_Connected(void) {
  bool isMCP2515Connected = false;
  // Try to initialize the MCP2515
  SPI.begin();
  isMCP2515Connected = mcp.reset() == MCP2515::ERROR_OK;

  TEST_ASSERT_TRUE_MESSAGE(isMCP2515Connected, "MCP2515 module not connected.");
}

// Function to test communication CAN BUS
void test_CAN_Communication(void) {
  bool module = false;

  SPI.begin();
  module = (mcp.reset() == MCP2515::ERROR_OK);
  if (module == false){
    TEST_FAIL_MESSAGE("Failed to send CAN messages.");
  }
  else{
    mcp.setBitrate(CAN_125KBPS);
    mcp.setNormalMode();

    // Test ID and data
    uint32_t testID = 0x0E1;
    uint8_t testData = 1;

    struct can_frame canMsg;
    canMsg.can_id  = testID;   // ID 
    canMsg.can_dlc = 1;        //  1 byte
    canMsg.data[0] = testData; // Value

    // Check if the message was sent successfully
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
  }
}
