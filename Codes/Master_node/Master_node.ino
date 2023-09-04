#include <SPI.h>
#include <mcp2515.h>

#define CS_PIN 53 // pin Chip Select

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
// funcion para enviar a diferentes CAN
void sendMSG(uint32_t canID, uint8_t data) {
  canMsg.can_id  = canID;  // ID del mensaje
  canMsg.can_dlc = 1;      // Longitud del mensaje (1 byte)
  canMsg.data[0] = data; // Contenido del mensaje

  if (mcp.sendMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("Mensaje enviado a CAN ID ");
    Serial.print(canID, HEX);
    Serial.print(": ");
    Serial.println(data);
  } else {
    Serial.println("Error al enviar el mensaje");
  }
}

void loop() {
  // 1 = right, 2 = left , 3 = intermittent, 0 = off
  sendMSG(0x0E1, 1); // Envia mensaje al ECU 1 (direccional)
  // 1 = intermittent, 2 = slow , 3 = high, 0 = off
  sendMSG(0x0E2, 0); // Envia mensaje al ECU 2 (limpiaparabrisas)
}

/*
  canMsg.can_id  = 0x0E1; // ID del mensaje
  canMsg.can_dlc = 1;     // Longitud del mensaje (1 byte)
  canMsg.data[0] = 1;     // Contenido del mensaje (valor 1)

  if (mcp.sendMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.println("Mensaje enviado al Arduino Nano");
  } else {
    Serial.println("Error al enviar el mensaje");
  }

  delay(100); // Envía el mensaje cada 1 segundo
*/