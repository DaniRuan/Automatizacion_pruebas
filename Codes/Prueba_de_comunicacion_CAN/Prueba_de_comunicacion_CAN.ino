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
  mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp.setNormalMode();
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x0E2) { // ID 
        Serial.println("Valor recibido");
    }
  }
}

