/* Script where the module test cases are executed */
#include <Arduino.h>
#include <unity.h>
#include <Set_display_test.hpp>

void setup(){
  Serial.begin(9600);
  delay(1000);

  UNITY_BEGIN();
    RUN_TEST(test_display_elements);
  UNITY_END();
}

void loop() {
}