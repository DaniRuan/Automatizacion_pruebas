/* Script where the module test cases are executed */
#include <Arduino.h>
#include <unity.h>
#include <Set_tests_Gateway.hpp>

void setup(){
    Serial.begin(9600);
    delay(1000);

  UNITY_BEGIN();
    RUN_TEST(test_Gateway_Is_On);
    delay(1000);
    RUN_TEST(test_MCP2515_Module_Connected);
    delay(1000);
    RUN_TEST(test_CAN_Communication);
    delay(1000);
  UNITY_END();
}

void loop() {
}
