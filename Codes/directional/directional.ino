byte pinLED[6] = {2,3,4,5,6,7};

int t1=40;
int t2=500;

//1 =right, 2 = left, 3 = intermittent
int status = 1;

void setup() {
  for(int pin= 0; pin<6; pin++){
    pinMode(pinLED[pin], OUTPUT);  
  }
}

void loop() {
  if(status==1){
    for(int i=0; i<6;i++){
      digitalWrite(pinLED[i], HIGH);
      delay(t1);      
    }

    for(int i=0; i<6;i++){
      digitalWrite(pinLED[i], LOW);
      delay(t1);      
    }
  }

  if(status==2){
    for(int j=5; j>-1;j--){
      digitalWrite(pinLED[j], HIGH);
      delay(t1);      
    }

    for(int k=5; k>-1;k--){
      digitalWrite(pinLED[k], LOW);
      delay(t1);      
    }
  }

  if(status==3){
    for(int i=0; i<6;i++){
      digitalWrite(pinLED[i], HIGH);     
    }
    delay(t2);
    for(int i=0; i<6;i++){
      digitalWrite(pinLED[i], LOW);      
    }
    delay(t2);
  }
}
/*    
#define pinLED1 2
#define pinLED2 3
#define pinLED3 4
#define pinLED4 5
#define pinLED5 6
#define pinLED6 7

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(pinLED4, OUTPUT);
  pinMode(pinLED5, OUTPUT);
  pinMode(pinLED6, OUTPUT);


    digitalWrite(pinLED1, HIGH);
    delay(t1);
    digitalWrite(pinLED2, HIGH);
    delay(t1);
    digitalWrite(pinLED3, HIGH);
    delay(t1);
    digitalWrite(pinLED4, HIGH);
    delay(t1);
    digitalWrite(pinLED5, HIGH);
    delay(t1);
    digitalWrite(pinLED6, HIGH);
    delay(t1);  

    digitalWrite(pinLED1, LOW);
    delay(t1);
    digitalWrite(pinLED2, LOW);
    delay(t1);
    digitalWrite(pinLED3, LOW);
    delay(t1);
    digitalWrite(pinLED4, LOW);
    delay(t1);
    digitalWrite(pinLED5, LOW);
    delay(t1);
    digitalWrite(pinLED6, LOW);
    delay(t1);
  }

  if(status==2){  
    digitalWrite(pinLED6, HIGH);
    delay(t1);
    digitalWrite(pinLED5, HIGH);
    delay(t1);
    digitalWrite(pinLED4, HIGH);
    delay(t1);
    digitalWrite(pinLED3, HIGH);
    delay(t1);
    digitalWrite(pinLED2, HIGH);
    delay(t1);
    digitalWrite(pinLED1, HIGH);
    delay(t1);  

    digitalWrite(pinLED6, LOW);
    delay(t1);
    digitalWrite(pinLED5, LOW);
    delay(t1);
    digitalWrite(pinLED4, LOW);
    delay(t1);
    digitalWrite(pinLED3, LOW);
    delay(t1);
    digitalWrite(pinLED2, LOW);
    delay(t1);
    digitalWrite(pinLED1, LOW);
    delay(t1);
  }

  if(status==3){  
    digitalWrite(pinLED1, HIGH);
    digitalWrite(pinLED2, HIGH);
    digitalWrite(pinLED3, HIGH);
    digitalWrite(pinLED4, HIGH);
    digitalWrite(pinLED5, HIGH);
    digitalWrite(pinLED6, HIGH);
    delay(t2);  

    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);
    digitalWrite(pinLED3, LOW);
    digitalWrite(pinLED4, LOW);
    digitalWrite(pinLED5, LOW);
    digitalWrite(pinLED6, LOW);
    delay(t2);
  }
 */  
