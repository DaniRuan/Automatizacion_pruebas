/************************************************** *********************
ECU 3 (display) testing elements display
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of test cases for the display of all the elements in ECU 3.
************************************************** *********************/
#pragma once
#include <Arduino.h>
#include <unity.h>
#include <SPI.h>

// Display variables
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void set_OLED(void){
  // OLED 128x64
  delay(250);
  display.begin(i2c_Address, true);
  display.display();
  delay(2000);

  // Color & size font
  display.setTextSize(1.5);
  display.setTextColor(SH110X_WHITE);
  delay(1000);
}

// Function to test the correct display of elements on the OLED screen
void test_display_elements(void){
  set_OLED();
  // Test variables
  int musicAmplitude = 30;      
  int volume = 70; 

  display.clearDisplay();

  // Test volume bar
  int maxBarWidth = SCREEN_WIDTH - 2;
  int barWidth = map(volume, 0, 100, 0, maxBarWidth);
  display.fillRect(1, 10, barWidth, SCREEN_HEIGHT / 4 - 2, SH110X_WHITE);
  display.display();
  delay(2000);

  TEST_ASSERT_EQUAL(SH110X_WHITE, display.getPixel(1, 10));  // Check the bar

  display.clearDisplay();
  // Test volume percentage display
  display.setCursor(1, 1);
  display.print("Volume: ");
  display.print(volume);
  display.print("%");
  display.display();
  delay(2000);

  TEST_ASSERT_EQUAL(SH110X_WHITE, display.getPixel(1, 1)); // Check the text and its position

  display.clearDisplay();
  // Test music animation
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    int barHeight = random(0, musicAmplitude);
    display.drawLine(i, SCREEN_HEIGHT - barHeight, i, SCREEN_HEIGHT - 1, SH110X_WHITE);
    TEST_ASSERT_TRUE(barHeight >= 0);
    TEST_ASSERT_TRUE(barHeight <= musicAmplitude);
  }
  
  display.display();
  delay(1000);

  // Test dimensions
  TEST_ASSERT_EQUAL(SCREEN_WIDTH, display.width());
  TEST_ASSERT_EQUAL(SCREEN_HEIGHT, display.height());

  display.clearDisplay();
  delay(2000);
}