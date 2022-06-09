#include "SoftwareSerial.h"

//RX=2,TX=3(D2) Software Serial Port
SoftwareSerial mySerial(2,3);

#define SERIAL Serial
#define TRANS_SERIAL  mySerial


String code_bon = "2022"; // Code de la porte d'entrée
String code =""; // Code en cous d'utilisation avant la validation
String touch =""; //Variable de sauvegarde de la touche entrée

void setup() {
  TRANS_SERIAL.begin(9600); 
  SERIAL.begin(9600);  // start serial for output
  SERIAL.println("Version:v1.0");
  SERIAL.println("HEX | DEC | ASCII");
  
}

void loop() {
    printData();
    digiCode();
    Verification();
}

/*
* data mapping:E1---1；E2---2；E3---3；E4---4；E5---5；E6---6；
*              E7---7；E8---8；E9---9；EA---*；EB---0；EC---#；
*/
void printData() {
  //
    while(TRANS_SERIAL.available()) {
        uint8_t data = TRANS_SERIAL.read();
        SERIAL.print(" ");
        SERIAL.print(data,HEX);
        SERIAL.print(" | ");
        SERIAL.print(data,DEC);
        SERIAL.print(" | ");
        switch(data) {
                case 0xE1 :
                    SERIAL.println("1");
                    SERIAL.print("touch:");
                    touch="1";
                    SERIAL.println(touch);
                    break;
                case 0xE2 :
                    SERIAL.println("2");
                    SERIAL.print("touch:");
                    touch="2";
                    SERIAL.println(touch);
                    break;
                case 0xE3 :
                    SERIAL.println("3");
                    SERIAL.print("touch:");
                    touch="3";
                    SERIAL.println(touch);
                    break;
                case 0xE4 :
                    SERIAL.println("4");
                    SERIAL.print("touch:");
                    touch="4";
                    SERIAL.println(touch);
                    break;
                case 0xE5 :
                    SERIAL.println("5");
                    SERIAL.print("touch:");
                    touch="5";
                    SERIAL.println(touch);
                    break;
                case 0xE6 :
                    SERIAL.println("6");
                    SERIAL.print("touch:");
                    touch="6";
                    SERIAL.println(touch);
                    break;
                case 0xE7 :
                    SERIAL.println("7");
                    SERIAL.print("touch:");
                    touch="7";
                    Serial.println(touch);
                    break;
                case 0xE8 :
                    SERIAL.println("8");
                    SERIAL.print("touch:");
                    touch="8";
                    SERIAL.println(touch);
                    break;
                case 0xE9 :
                    SERIAL.println("9");
                    SERIAL.print("touch:");
                    touch="9";
                    SERIAL.println(touch);
                    break;
                case 0xEA :
                    SERIAL.println("*");
                    SERIAL.print("touch:");
                    touch="*";
                    SERIAL.println(touch);
                    break;
                case 0xEB :
                    SERIAL.println("0");
                    SERIAL.print("touch:");
                    touch="0";
                    SERIAL.println(touch);
                    break;
                case 0xEC :
                    SERIAL.println("#");
                    SERIAL.print("touch:");
                    touch="#";
                    SERIAL.println(touch);
                    break;
                default:
                    break;
            }
    }
}

//Enregistement du code qui est composé au clavier au fur et à mesure
void digiCode(){
  if (touch =="1" || touch =="2"|| touch =="3"|| touch =="4"|| touch =="5"|| touch =="6"|| touch =="7"|| touch =="8"|| touch =="9"|| touch =="0"|| touch =="*")
  {
    code+=touch;
    touch="";
    SERIAL.print("code : ");
    SERIAL.println(code);
  }
}

//Verification du code une fois que l'on appuis sur la touche #
//La touche # sert à confirmer le code entrée
void Verification(){

    if(touch =="#")
    {
      if(code==code_bon)
        SERIAL.println("Le code est bon ! :) ");
      else
        SERIAL.println("Le n'est pas bon ! :( ");
      code="";
      touch="";
    }
}
