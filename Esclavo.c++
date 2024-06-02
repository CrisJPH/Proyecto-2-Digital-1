include <Servo.h>
#include <stdint.h>
#include <arduino.h>

int angulo;
int a = 0;
void setup(){

  Serial.begin(9600);
  while (!Serial);
}
void loop(){ // Si hay suficientes bytes disponibles para leer un float
//sirve para detectar si se mando un dato desde el maestro
 if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    //identifica si es el de temperatura normal
      if (command.startsWith("SRV:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("La Persona tiene una buena temperatura");
    //identifica si es una persona con fiebre
    }else if(command.startsWith("SRC:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("la persona tiene una fiebre");
        //identifica si es una persona con pulso normal
    }else if(command.startsWith("SCC:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("la persona tiene un pulso normal");
        //identifica si es una persona con pulso anormal
      }else if(command.startsWith("SMM:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("la persona tiene una Pulso Anormal");
        //identifica si la persona esta sobria
      }else if(command.startsWith("MMM:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("la persona esta sobrio");
        //identifica si la persona esta borracho
      }else if(command.startsWith("SRS:")) {
      int angulo = command.substring(4).toInt();
      Serial.println("la persona esta en estado de alcoholismo");
 }
 }
}