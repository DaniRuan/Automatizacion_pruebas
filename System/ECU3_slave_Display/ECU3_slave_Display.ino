/**********************************************************************
ECU3 nodo esclavo - display
Por Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
Septiembre, 2023
Simula la función de manipulación de volumen en una canción a través de una variable
mandada del Gateway obtenida de un potenciómetro.
***********************************************************************/

#include <SPI.h>
#include <mcp2515.h>
#define CS_PIN 10 // pin Chip Select

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables para la animación de música
int musicAnimationSpeed = 10; 
int musicAmplitude = 30;      
int volumen; 

struct can_frame canMsg;

MCP2515 mcp(CS_PIN);

void setup() {
  // Configuración de puerto serial y comunicación CAN
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mcp.reset();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();
  // Configuración pantalla OLED 128x64
  delay(250);
  display.begin(i2c_Address, true);
  display.display();
  delay(2000);

  // Color y tamano de letra
  display.setTextSize(1.5);
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) { // Verifica si lee el mensaje
    if (canMsg.can_id == 0x0E3) { // ID del mensaje enviado por el Gateway
    Serial.println("Valor recibido");
      volumen = canMsg.data[0];
    
      display.clearDisplay();

      // Barra de volumen
      int maxBarWidth = SCREEN_WIDTH - 2;
      int barWidth = map(volumen, 0, 100, 0, maxBarWidth);
      display.fillRect(1, 10, barWidth, SCREEN_HEIGHT / 4 - 2, SH110X_WHITE);

      // Mostrar el valor del volumen
      display.setCursor(1, 1);
      display.print("Volume: ");
      display.print(volumen);
      display.print("%");

      // Animación de música (histograma)
      for (int i = 0; i < SCREEN_WIDTH; i++) {
        int barHeight = random(0, musicAmplitude);
        display.drawLine(i, SCREEN_HEIGHT - barHeight, i, SCREEN_HEIGHT - 1, SH110X_WHITE);
      }

      display.display();
    }
  }
}
