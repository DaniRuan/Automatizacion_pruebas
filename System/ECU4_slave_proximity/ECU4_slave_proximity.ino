/* Creado por a01735674 Fausto Carrillo, programa para sistema de alarma de proximidad
 *  correo A01735674@tec.mx
 */
#include <SPI.h>  //Librerias para comunicación con perifericos SPI
#include <mcp2515.h> //Libreria para comunicacion con modulo MCP2515
#define NOTE_A7  3520 //Nota musical para el zumbador


const int ECHO=5;
const int TRIG=4;
int DURACION;
int DISTANCIA;
const int BUZZER = A4;
const int CS_PIN= 10;

int BOTON;

struct can_frame canMsg;
MCP2515 mcp(CS_PIN);

void setup() { 
  Serial.begin(9600);
  mcp.reset();
  mcp.setBitrate(CAN_125KBPS);
  mcp.setNormalMode();
  pinMode(BUZZER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (mcp.readMessage(&canMsg) == MCP2515::ERROR_OK) { 
    if(canMsg.can_id==0x0E4){
      BOTON=canMsg.data[0];
      if(BOTON==1){
        Serial.println("Sensor de proximidad encendido");
        digitalWrite(TRIG, HIGH); //Encendido del sensor ultrasonico
        delay(1);
        digitalWrite(TRIG,LOW);
        DURACION= pulseIn(ECHO, HIGH);
        DISTANCIA = DURACION/ 58.2;
        Serial.print("DISTANCIA: ");
        Serial.println(DISTANCIA);
       
        digitalWrite(LED_BUILTIN, HIGH);
        tone(BUZZER, NOTE_A7, 8);
        delay(DISTANCIA*7);
        digitalWrite(LED_BUILTIN, LOW);
        noTone(BUZZER);
        delay(DISTANCIA*6);
      }
      
      else if(BOTON==0){
        Serial.println("Sensor de proximidad apagado");
        delay(300);
        digitalWrite(TRIG,LOW); //Apagado del sensor ultrasonico
        noTone(BUZZER);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }
}
