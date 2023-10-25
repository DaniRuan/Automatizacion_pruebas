/************************************************** *********************
ECU 3 (display) testing volumen variation
By Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
October, 2023
Programming of test cases for the volume variation in ECU 3.
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

// Function to test if the valume changes when receiving different values 0 - 100
void test_volume_variation(void){
  set_OLED();
  delay(1000);
  display.clearDisplay();
  for (int volume = 0; volume <= 100; volume++) {
    
    display.clearDisplay();

    // Volume bar
    int maxBarWidth = SCREEN_WIDTH - 2;
    int barWidth = map(volume, 0, 100, 0, maxBarWidth);
    display.fillRect(1, 10, barWidth, SCREEN_HEIGHT / 4 - 2, SH110X_WHITE);

    display.setCursor(1, 1);
    display.print("Volume: ");
    display.print(volume);
    display.print("%");

    display.display();
    
    // Validate the volume bar and dimensions
    TEST_ASSERT(barWidth >= 0);
    TEST_ASSERT(barWidth <= maxBarWidth);
    TEST_ASSERT_EQUAL(SCREEN_WIDTH, display.width());
    TEST_ASSERT_EQUAL(SCREEN_HEIGHT, display.height());

    delay(100);
  }
  display.clearDisplay();
  delay(2000);
}