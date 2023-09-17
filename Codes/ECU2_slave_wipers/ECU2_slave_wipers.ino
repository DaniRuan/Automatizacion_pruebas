/**********************************************************************
ECU2 nodo esclavo - limpiaparabrisa
Por Daniel Ruán
ITESM - EDAG intership
Email: A01731921@tec.mx
Septiembre, 2023
Simula la función de un limpiaparabrisas realizando una velocidad 
diferente dependiendo de una variable que contiene un mensaje enviado 
nodo por el master.
***********************************************************************/

#include <SPI.h>
#include <mcp2515.h>
#include <Servo.h>
#define CS_PIN 10 // pin Chip Select

Servo myservo;
int pos = 0;

int oscilations=0;

struct can_frame canMsg;

MCP2515 mcp(CS_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  // Configuración de comunicación CAN
  SPI.begin();
  mcp.reset();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();

  myservo.attach(3); // Pin signal pwm servo
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x0E2) { // ID del mensaje enviado por el Gateway
    
      if (canMsg.data[0] == 1) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for (int angle = 0; angle <= 80; angle += 1){
          pos = map(angle, 0, 80, 0, 80); // mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }

        for (int angle = 80; angle >= 0; angle -= 1){
          pos = map(angle, 0, 80, 0, 80); //mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }

        delay(5000); // Espera 5 segundo entre oscilaciones 
      }
      
      else if (canMsg.data[0] == 2) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for (int angle = 0; angle <= 80; angle += 1){
          pos = map(angle, 0, 80, 0, 80); //mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }

        for (int angle = 80; angle >= 0; angle -= 1){
          pos = map(angle, 0, 80, 0, 80); //mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }

        delay(1000); // Espera 1 segundo entre oscilaciones 
      }
      
      else if (canMsg.data[0] == 3) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");
        for (int angle = 0; angle <= 80; angle += 1){
          pos = map(angle, 0, 80, 0, 80); // mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }

        for (int angle = 80; angle >= 0; angle -= 1){
          pos = map(angle, 0, 80, 0, 80); // mapeo
          myservo.write(pos);
          delay(9); // retardo entre oscilación
        }
      }

      else if (canMsg.data[0] == 0) { // Verifica el contenido del mensaje
        // Realiza acciones según el mensaje recibido
        Serial.println("Valor recibido");      
        if (oscilations < 1) {
          for (int angle = 0; angle <= 80; angle += 1){
            pos = map(angle, 0, 80, 0, 80); // mapeo
            myservo.write(pos);
            delay(9); // retardo entre oscilación
          }

          for (int angle = 80; angle >= 0; angle -= 1){
            pos = map(angle, 0, 80, 0, 80); // mapeo
            myservo.write(pos);
            delay(9); // retardo entre oscilación
          }

          oscilations++;
        }
        // Detiene el bucle loop()
        else {
          while (true) {
            // bucle infinito
          }
        }
      }
    }
  }
}
