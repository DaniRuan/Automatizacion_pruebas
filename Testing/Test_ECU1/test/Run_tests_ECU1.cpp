/* Script where the module test cases are executed */
#include <Arduino.h>
#include <unity.h>
#include <Set_tests_ECU1.hpp>

void setup(){
    Serial.begin(9600);
    delay(1000);

  UNITY_BEGIN();
    RUN_TEST(test_ECU1_Is_On);
    delay(1000);
    RUN_TEST(test_MCP2515_Module_Connected);
    delay(1000);
    RUN_TEST(test_CAN_Message_Receive);
    delay(1000);
    RUN_TEST(test_LED_Operation_0);
    delay(1000);
    RUN_TEST(test_LED_Operation_1);
    delay(1000);
    RUN_TEST(test_LED_Operation_2);
    delay(1000);
    RUN_TEST(test_LED_Operation_3);
    delay(1000);
  UNITY_END();
}

void loop() {
}