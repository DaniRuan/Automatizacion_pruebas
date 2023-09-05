/**********************************************************************
ECU1 nodo esclavo direccionales
Por Daniel R.
ITESM - EDAG intership
Septiembre, 2023
Simula la función de direccionales realizando un modo
diferente dependiendo del mensaje que recibe del master.
***********************************************************************/

#include <SPI.h>
#include <mcp2515.h>
#define CS_PIN 10 // pin Chip Select

byte pinLED[6] = {2,3,4,5,6,7};

int t1=40;
int t2=500;

struct can_frame canMsg;

MCP2515 mcp(CS_PIN);

void setup() {
  // Configuración de puerto serial, comunicación CAN y LEDs
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mcp.reset();
  mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp.setNormalMode();

  for(int pin= 0; pin<6; pin++){
    pinMode(pinLED[pin], OUTPUT);  
  }
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x0E1) { // ID del mensaje enviado por el Gateway
    
      if (canMsg.data[0] == 1) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for(int i=0; i<6;i++){
          digitalWrite(pinLED[i], HIGH);
          delay(t1);      
        }

        for(int i=0; i<6;i++){
          digitalWrite(pinLED[i], LOW);
          delay(t1);      
        }
      }
      
      else if (canMsg.data[0] == 2) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for(int j=5; j>-1;j--){
          digitalWrite(pinLED[j], HIGH);
          delay(t1);      
        }

        for(int k=5; k>-1;k--){
          digitalWrite(pinLED[k], LOW);
          delay(t1);      
        }
      }  
      else if (canMsg.data[0] == 3) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for(int i=0; i<6;i++){
          digitalWrite(pinLED[i], HIGH);     
        }
        delay(t2);
        for(int i=0; i<6;i++){
          digitalWrite(pinLED[i], LOW);      
        }
        delay(t2);
      }
      else if (canMsg.data[0] == 0) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for(int i=0; i<6;i++){
          digitalWrite(pinLED[i], LOW);     
        }
      }
    }
  }
}
