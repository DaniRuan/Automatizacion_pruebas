/************************************************** *********************
ECU 4 Test Cases (proximity)
By:
 - Fausto Rodrigo Carrillo
 - Daniel Ruán
ITESM - EDAG intership
Email: 
 - A01735674@tec.mx
 - A01731921@tec.mx
October, 2023
Programming of the test cases for ECU 4 stipulated in the
documentation.
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>
#include <mcp2515.h>
#define NOTE_A7  3520
#define CS_PIN 10 // Chip Select pin for MCP2515
#define TIMEOUT_MS 5000 // Timeout for message reception in milliseconds

MCP2515 mcp(CS_PIN);
unsigned long startTime;

const int ECHO=5;
const int TRIG=4;
int DURACION;
int DISTANCIA;
const int BUZZER = A4;
int BOTON;
const int powerPin = A0;

void Set_sensor_proximity(void){
  pinMode(BUZZER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// Function to test if the Arduino is running
void test_ECU4_Is_On(void) {
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
        if (canMsg.can_id == 0x0E4) {
          messageReceived = true;
          break;
        }
      }
    }

    // Check if a message was received
    TEST_ASSERT_TRUE_MESSAGE(messageReceived, "Messages could not be received.");
  }
}

// Function to test when proximity sensor activates
void test_proximity_sensor_activates(void){
  Set_sensor_proximity();
  String receivedString;

  digitalWrite(TRIG, HIGH);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(TRIG));
  delay(1);

  digitalWrite(TRIG,LOW);
  TEST_ASSERT_EQUAL(LOW, digitalRead(TRIG));

  DURACION = pulseIn(ECHO, HIGH);
  DISTANCIA = DURACION/ 58.2;
  Serial.print("DISTANCIA: ");
  Serial.println(DISTANCIA);
  
  while (Serial.available()) {
    receivedString += (char)Serial.read();
  }

  // Check that it is displaying numerical values when detecting any object in the monitor
  const char* expectedCStr = ("DISTANCIA: " + String(DISTANCIA)).c_str();
  TEST_ASSERT_EQUAL_STRING(expectedCStr, receivedString.c_str());
  TEST_ASSERT_GREATER_THAN(0, DISTANCIA);

  tone(BUZZER, NOTE_A7, 8);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(BUZZER));
  delay(DISTANCIA*7);

  noTone(BUZZER);
  TEST_ASSERT_EQUAL(LOW, digitalRead(BUZZER));
  delay(DISTANCIA*6);
}

// Function to test when proximity sensor is deactivated
void test_proximity_sensor_deactivated(void){
  Set_sensor_proximity();
  delay(300);
  
  digitalWrite(TRIG,LOW);
  TEST_ASSERT_EQUAL(LOW, digitalRead(TRIG));

  noTone(BUZZER);
  TEST_ASSERT_EQUAL(LOW, digitalRead(BUZZER));
}