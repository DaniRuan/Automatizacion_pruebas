/* Script where the module test cases are executed */
#include <Arduino.h>
#include <unity.h>
#include <Set_value_test.hpp>

void setup(){
  Serial.begin(9600);
  delay(1000);

  UNITY_BEGIN();
      RUN_TEST(test_value_variation);
  UNITY_END();
}

void loop() {
}
