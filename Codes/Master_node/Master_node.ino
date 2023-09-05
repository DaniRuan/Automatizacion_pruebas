/**********************************************************************
Nodo master gateway
Por Daniel R.
ITESM - EDAG intership
Septiembre, 2023
Manda mensajes por protocolo CAN a los ECUs para modificar su
comṕortamiento por medio de potenciometros para cambiar su variable.
***********************************************************************/

#include <SPI.h>
#include <mcp2515.h>

#define CS_PIN 53 // pin Chip Select

struct can_frame canMsg;
int potPin1 = A1;
int potPin2 = A2; 
int mappedValue1;
int mappedValue2;

MCP2515 mcp(CS_PIN);

void setup() {  
  Serial.begin(9600);
  while (!Serial);
// Configuración protocolo CAN
  SPI.begin();
  mcp.reset();
  mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp.setNormalMode();
}
// Función para enviar a diferentes CAN
void sendMSG(uint32_t canID, uint8_t data) {
  canMsg.can_id  = canID;  // ID del mensaje
  canMsg.can_dlc = 1;      // Longitud del mensaje (1 byte)
  canMsg.data[0] = data; // Contenido del mensaje

  if (mcp.sendMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("Mensaje enviado a CAN ID ");
    Serial.print(canID, HEX);
    Serial.print(":  ");
    Serial.println(data);
  } else {
    Serial.println("Error al enviar el mensaje");
  }
}

void loop() {
  int valorPot1 = analogRead(potPin1); // Lee el valor del primer potenciómetro
  int valorPot2 = analogRead(potPin2); // Lee el valor del segundo potenciómetro

    // Mapea los valores al rango 0-3
  if (valorPot1 < 256 ) {
    mappedValue1 = 0; // Rango 0-255
  } else if (valorPot1 < 512) {
    mappedValue1 = 1; // Rango 256-511
  } else if (valorPot1 < 768) {
    mappedValue1 = 2; // Rango 512-767
  } else if (valorPot1 < 1024) {
    mappedValue1 = 3; // Rango 768-1023
  }

  if (valorPot2 < 256 ) {
    mappedValue2 = 0; // Rango 0-255
  } else if (valorPot2 < 512) {
    mappedValue2 = 1; // Rango 256-511
  } else if (valorPot2 < 768) {
    mappedValue2 = 2; // Rango 512-767
  } else if (valorPot2 < 1024) {
    mappedValue2 = 3; // Rango 768-1023
  }  
  
  // 1 = right, 2 = left , 3 = intermittent, 0 = off
  sendMSG(0x0E1, mappedValue1); // Envia mensaje al ECU 1 (direccional)
  // 1 = intermittent, 2 = slow , 3 = high, 0 = off
  sendMSG(0x0E2, mappedValue2); // Envia mensaje al ECU 2 (limpiaparabrisas)
}