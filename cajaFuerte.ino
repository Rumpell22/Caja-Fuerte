#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//int buzzer = 50;

// Inicializamos el sensor DHT11
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#include <Servo.h>
#include <Keypad.h>

//Variables
int mot_min = 150;   //min servo angle  (set yours)
int mot_max = 60; //Max servo angle   (set yours)
int character = 0;
int activated =0;
int intentos = 3;
char Str[16] = {' ', ' ', ' ', ' ', ' ', ' ', '-', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' '};  

//Pins
Servo myservo;
int buzzer=50;     //pin for the buzzer beep
//int external = 12; //pin to inside open
//int internal = 13; //pin to inside close

//Keypad config
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  myservo.attach(48); //attach the servo to pin D10
  pinMode(buzzer,OUTPUT); 
  Serial.begin(9600);
//  pinMode(external,INPUT);
//  pinMode(internal,INPUT); 
  //Init the screen and print the first text
    lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print("      PIN:");
  lcd.setCursor(0,1);
  lcd.print("      -***     ");
  //put the servo in the close position first
  myservo.write(mot_min);  
  
}
  
void loop(){
    
///////////////KEYPAD OPEN/CLOSE////////////  
  char customKey = customKeypad.getKey(); //this function reads the presed key
  if (customKey){

    if (character ==0)
    {  
    Serial.println(customKey);
    Str[6]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      PIN:");   
    lcd.setCursor(0,1);
    lcd.print(Str);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    }

    if (character ==1)
    {  
    Serial.println(customKey);
    Str[7]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      PIN:");
    lcd.setCursor(0,1);
    lcd.print(Str);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    }

    if (character ==2)
    {  
    Serial.println(customKey);
    Str[8]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      PIN:");   
    lcd.setCursor(0,1);
    lcd.print(Str);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    }

    if (character ==3)
    {  
    Serial.println(customKey);
    Str[9]= customKey;   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      PIN:"); 
    lcd.setCursor(0,1);
    lcd.print(Str);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    }
    if (character >=4)
    {  
    Serial.println(customKey);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    if(customKey == 'A'){
        activated=1;
        
    }
    }
    character=character+1;
  }

  if (activated == 1)
    {
/*Change your password below!!! 
Change each of Str[6], Str[7], Str[8], Str[9]*/

    if( Str[6]=='3' && Str[7]=='0' && Str[8]=='0' && Str[9]=='7' )
    {
      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("ACCEPTED");
      activated = 2;
      digitalWrite(buzzer,HIGH);
      delay(250);
      digitalWrite(buzzer,LOW);
      delay(250);
      digitalWrite(buzzer,HIGH);
      delay(250);
      digitalWrite(buzzer,LOW); 
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("Bienvenido");
      delay(500);
      delay(1000);

      lcd.clear();    
      lcd.setCursor(1,0);
      lcd.print("PUERTA ABIERTA");
      
    }
    else
    {
      lcd.clear();    
      lcd.setCursor(1,0);
      lcd.print("PIN INCORRECTO");
      lcd.setCursor(3,1);
      lcd.print("INTENTOS: ");
      lcd.print(intentos-1);
      digitalWrite(buzzer,HIGH);
      delay(1200);
      digitalWrite(buzzer,LOW);
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';
      activated = 0;
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("  PIN:"); 
      lcd.setCursor(0,1);
      lcd.print(Str);
      intentos=intentos-1;   
    }
    if(intentos==0){
        int segundostotal =30;
        int aminutos;
        int asegundos;
        while(segundostotal>0){
           lcd.clear();
           lcd.setCursor(1,0);
           lcd.print("CAJA BLOQUEADA");
           lcd.setCursor(0,1);
           lcd.print("INTENTE EN ");
           segundostotal--;
           aminutos = (segundostotal / 60) % 60;  
           asegundos = segundostotal % 60;        
           if (aminutos < 10) lcd.print("0");   // Si los minutos son menor que 10, pone un "0" delante.
           lcd.print(aminutos);                 
           lcd.print(":");
           if (asegundos < 10) lcd.print("0");  // si el valor de segundo esta por debajo de 9 (unidad) antepone un cero
           lcd.print(asegundos); 
           delay (1000);    
        }
        intentos=3;
    }
  }
  if (activated == 2)
    {
    if(customKey == 'C' )
    {
      lcd.clear();    
      lcd.setCursor(1,0);
      lcd.print("PUERTA CERRADA");
      delay(2000);
      myservo.write(mot_min);
      activated = 0;
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("      PIN:");   
      lcd.setCursor(0,1);
      lcd.print(Str);
     
    }
  }  
}



 
