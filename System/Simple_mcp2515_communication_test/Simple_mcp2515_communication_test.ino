// simple prueba para ver si el módulo can recibe mensajes o esta dañado
#include <SPI.h>
#include <mcp2515.h>

#define CS_PIN 10 // pin cs

struct can_frame canMsg;

MCP2515 mcp(CS_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mcp.reset();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      Serial.println("Valor recibido");
  }
}

