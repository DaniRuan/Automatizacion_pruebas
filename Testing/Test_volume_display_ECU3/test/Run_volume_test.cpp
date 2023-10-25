/* Script where the module test cases are executed */
#include <Arduino.h>
#include <unity.h>
#include <Set_volume_test.hpp>

void setup(){
  Serial.begin(9600);
  delay(1000);

  UNITY_BEGIN();
      RUN_TEST(test_volume_variation);
  UNITY_END();
}

void loop() {
}