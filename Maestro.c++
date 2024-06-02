// Declaracion de variables y librerias para funcionamiento del LCD n nb
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include<arduino.h>
int DHTPIN = A3;
uint8_t rango_temp2;
uint8_t rango_temp;
#define sensorDigital 10
#define sensorAnalogico A2
#define LCD_ADDR 0x27
#define LCD_columns 16
#define LCD_rows 2
typedef enum estados {s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13};
estados estadoA = s0;
estados estadoF = s0;
int valor_limite = 400; 
int buttonPin = 2;
int Led_rojo = 6;
int Led_verde = 7;
int switchState = 4;
int analog;
bool scan = false;
bool standby = false; 
long pul;
float temp, porcentaje;
int a, buttonState;
int off1, off2, off3;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_columns, LCD_rows);
uint8_t pulso_boton;
Servo servo;
Servo servo2;
int pos;
const long inter = 2000;
unsigned long millisPasada = 0;
uint8_t rango_pulso;
uint8_t rango_pulso2;

void setup() {
  // put your setup code here, to run once:
  //Definir las toma de valores de los leds, botones y el switch utilizado en el programa
    Serial.begin(9600);
    
    pinMode(sensorDigital, INPUT_PULLUP);
    servo.attach(9);
    servo2.attach(8);
    pinMode(A2, INPUT);
    pinMode(Led_rojo, INPUT);
    pinMode(Led_verde, INPUT);
    pinMode(buttonPin, INPUT);
    pinMode(switchState, INPUT_PULLUP);
    buttonState = digitalRead(buttonPin);
    //iniciar el LCD
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();

    lcd.setCursor(2,0);
    lcd.print("Bienvenido!!");
    delay(300);
}


void loop() {
  // put your main code here, to run repeatedly:
  //Lectura del boton de inicio para iniciar el programa
  buttonState = digitalRead(buttonPin);
  //lectura del switch para saber la edad del paciente
  bool ciclodevida = digitalRead(switchState);
  // put your main code here, to run repeatedly:
    switch(estadoA){
      case s0:
      //sirve para saber si se inicia el programa o no
        if(buttonState == LOW){
          estadoF = s1;
        }else{
          estadoF = s0;
        }
        break;
      case s1:
        //sirve para saber el ciclo de vida de la persona y mandar a distintos estados 
        //dependiendo de la respuesta
        if(ciclodevida == HIGH){
          estadoF = s3;
        }else{
          estadoF = s2;
        }
        break;
      case s2:
      //toma de temperatura 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("toma tu temp.");
        delay(5000);
         lcd.clear();
        rango_temp = map(analogRead(A3),0, 1000, 0, 50);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(rango_temp);
        delay(1000);
        //si tiene o no tiene fiebre manda a uno de los 2 estados
        if(rango_temp <= 37){
          estadoF = s4;
        }else{
          estadoF = s5;
        }
        break;
      case s3:
      //lo mismo que el caso S2
        Serial.print("SRC:");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("toma tu temp.");
        delay(5000);
        lcd.clear();
        rango_temp = map(analogRead(A3),0, 1000, 0, 50);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(rango_temp);
        delay(1000);
        if(rango_temp <= 37){
          estadoF = s4;
        }else{
          estadoF = s5;
        }
        break;
      case s4:
        //manda al estado s6
        estadoF = s6;
        break;
      case s5:
      //manda al estado s6
        estadoF = s6;
        break;
      case s6:
      //dependiendo el ciclo de vida escogido anteriormente manda a distintos estados 
        if(ciclodevida == HIGH){
          estadoF = s8;
        }else{
          estadoF = s7;
        }
        break;
      case s7:
      //toma de pulso del paciente
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ajusta tu pulso!!");
        delay(3000);
        rango_pulso = map(analogRead(A0),0, 700, 0, 220);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println(rango_pulso);
        delay(2000);
        lcd.setCursor(0,1);
         delay(1000);
        
        lcd.setCursor(0,1);
        //dependiendo del pulso del paciente se va a distintos estados
          if(rango_pulso > 60 && rango_pulso < 120){
            estadoF = s9;
          }else{
            estadoF = s10;
          }
        break;
      case s8:
      //los mismo que el estado S7
        lcd.clear();
        lcd.print("ajusta tu pulso!!");
        delay(3000);
        lcd.setCursor(0,0);
        rango_pulso = map(analogRead(A0),0, 700, 0, 220);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println(rango_pulso);
        delay(2000);
        lcd.setCursor(0,1);
        lcd.print(rango_pulso);
        delay(1000);
          if(rango_pulso > 60 && rango_pulso < 100){
            estadoF = s9;
          }else{
            estadoF = s10;
          }
        break;
      case s9:
      //va al estado s11
        estadoF = s11;
        break;
      case s10:
      //va al estado s11
        estadoF = s11;
        break;
      case s11:
      //toma de alcoholismo de la persona
        analog = analogRead(A1);
        porcentaje = (analog/10000); 
        //dependiendo del nivel de alcohol se va a distintos estados
          if(analog > 400){
          estadoF = s13;
          }else{
          estadoF = s12;
          }
        break;
      case s12:
      //regresa al inicio del programa terminandolo
      estadoF = s0;
        break;
      case s13:
      //regresa al inicio del programa terminandolo 
      estadoF = s0;
        break;
    }