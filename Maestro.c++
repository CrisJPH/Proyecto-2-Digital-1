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