/*
#include <Servo.h>

Servo myservo;
int pos = 0;

// off=0 , intermitent=1 , low=2 , high=3
int mode = 0;
int oscilations=0;

void setup(){
  myservo.attach(3); // Pin signal
}

void loop() {
  if (mode==1){
    for (int angle = 0; angle <= 80; angle += 1){
      pos = map(angle, 0, 80, 0, 80); // mapeo
      myservo.write(pos);
      delay(9); // retardo entre oscilaciónal que está conectado el servo
    }

    for (int angle = 80; angle >= 0; angle -= 1){
      pos = map(angle, 0, 80, 0, 80); //mapeo
      myservo.write(pos);
      delay(9); // retardo entre oscilación
    }

    delay(5000); // Espera 4 segundo entre oscilaciones 
  }
  
  else if (mode==2){
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

  else if (mode==3){
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
  
  else if (mode == 0) {
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
*/

#include <Servo.h>

Servo myservo;
int pos = 0;

// off=0 , intermitent=1 , low=2 , high=3
int mode = 4;
int oscilations=0;
int currentPosition;

void setup(){
  myservo.attach(3); // Pin signal
}

void loop() {
      currentPosition = myservo.read();
  if (mode==1){

    for (int angle = currentPosition ; angle  <= 80; angle  += 1){
      pos = map(angle, currentPosition, 80, currentPosition, 80); // mapeo
      myservo.write(pos);
      delay(9); // retardo entre oscilaciónal que está conectado el servo
    }

    for (int angle = 80; angle >= 0; angle -= 1){
      pos = map(angle, 0, 80, 0, 80); //mapeo
      myservo.write(pos);
      delay(9); // retardo entre oscilación
    }

    delay(5000); // Espera 4 segundo entre oscilaciones 
  }
  
  else if (mode==2){
    //currentPosition = myservo.read();
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

  else if (mode==3){
    //currentPosition = myservo.read();
    for (int angle = 0 ; angle <= 80; angle += 1){
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

  else if (mode == 4){

    
      for (int angle = currentPosition; angle >= 0; angle -= 1){
        pos = map(angle, 0, currentPosition, 0, currentPosition); // mapeo
        myservo.write(pos);
        delay(9); // retardo entre oscilación
      }
      while (true) {
        // bucle infinito
      }
     
  }
  

  else if (mode == 5) {
  myservo.write(0); // Mueve el servo a la posición 0 grados
  delay(500); // Espera un tiempo para que el servo alcance la posición deseada
  // Detiene el bucle loop()
  while (true) {
    // bucle infinito
  }
}

  else if (mode == 0) {
    //currentPosition = myservo.read();
    if (oscilations < 1) {
      for (int angle = currentPosition ; angle <= 80; angle += 1){
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