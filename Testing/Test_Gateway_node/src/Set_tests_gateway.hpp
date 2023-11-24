/************************************************** *********************
Gateway (master node)
By:
 - Daniel Ruán
 - Fausto Rodrigo Carrillo
ITESM - EDAG intership
Email: 
 - A01731921@tec.mx
 - A01735674@tec.mx
October, 2023
Programming of the test cases for Gateway node
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#define TIMEOUT_MS 5000
unsigned long startTime;

#define CS_PIN 53 // Chip Select pin for MCP2515
MCP2515 mcp(CS_PIN);

// Function to test if the Arduino is running
void test_Gateway_Is_On(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

// Function to test if the MCP25215 module is connected
void test_MCP2515_Module_Connected(void)
{
  bool isMCP2515Connected = false;
  // Try to initialize the MCP2515
  SPI.begin();
  isMCP2515Connected = mcp.reset() == MCP2515::ERROR_OK;

  TEST_ASSERT_TRUE_MESSAGE(isMCP2515Connected, "MCP2515 module not connected.");
}

// Function to test communication CAN BUS
void test_CAN_Communication(void)
{
  bool module = false;

  SPI.begin();
  module = (mcp.reset() == MCP2515::ERROR_OK);
  if (module == false)
  {
    TEST_FAIL_MESSAGE("Failed to send CAN messages.");
  }
  else
  {
    mcp.setBitrate(CAN_125KBPS);
    mcp.setNormalMode();

    // Test ID and data
    uint32_t testID = 0x0E3;
    uint8_t testData = 1;

    struct can_frame canMsg;
    canMsg.can_id = testID;    // ID
    canMsg.can_dlc = 1;        //  1 byte
    canMsg.data[0] = testData; // Value

    // Check if the message was sent successfully
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
  }

  
}

void test_ECU1(){
  SPI.begin();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();

  struct can_frame canMsg;
  canMsg.can_id = 0x0E1;    // ID
  canMsg.can_dlc = 1;        //  1 byte
  canMsg.data[0] = 0;
  
  for (int i = 0; i <= 3; i++) {
    canMsg.data[0] = i; // Value
    // verifica que el mensaje se haya enviado correctamente
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
    delay(1000);
  }
  canMsg.data[0] = 0;
}

void test_ECU2(){
  SPI.begin();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();

  struct can_frame canMsg;
  canMsg.can_id = 0x0E2;    // ID
  canMsg.can_dlc = 1;        //  1 byte
  canMsg.data[0] = 0;
  
  for (int i = 0; i <= 3; i++) {
    canMsg.data[0] = i; // Value
    // verifica que el mensaje se haya enviado correctamente
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
    delay(2000);
  }
  canMsg.data[0] = 0;
}



void test_ECU3(){
  SPI.begin();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();

  struct can_frame canMsg;
  canMsg.can_id = 0x0E3;    // ID
  canMsg.can_dlc = 1;        //  1 byte
  canMsg.data[0] = 0;
  
  for (int i = 0; i <= 100; i++) {
    canMsg.data[0] = i; // Value
    // Check if the message was sent successfully
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
    delay(25);
  }
  delay(10);
  canMsg.data[0] = 0;
}

void test_ECU4(){
 SPI.begin();
 mcp.setBitrate(CAN_125KBPS);
 mcp.setNormalMode();

 struct can_frame canMsg;
 canMsg.can_id = 0x0E4;    // ID
 canMsg.can_dlc = 1;        //  1 byte

 unsigned long startTime = millis();
 while (millis() - startTime < 10000) {
    canMsg.data[0] = 1;
    TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
    delay(100);
 }

 canMsg.data[0] = 0;
}

/*
void test_ECU1(){
  SPI.begin();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();

  struct can_frame canMsg;
  canMsg.can_id = 0x0E1;    // ID
  canMsg.can_dlc = 1;        //  1 byte
  //canMsg.data[0] = 0;

  for (int i = 0; i <=3; i++) {
    canMsg.data[0] = i; // Value
    unsigned long startTime = millis();
    while (millis() - startTime < 4000) {
      TEST_ASSERT_EQUAL_MESSAGE(MCP2515::ERROR_OK, mcp.sendMessage(&canMsg), "Messages not sent successfully");
      delay(100);
    }
  }
}*/