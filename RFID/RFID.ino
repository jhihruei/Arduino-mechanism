/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 */

 /*
  *  Used the opensource library from https://github.com/miguelbalboa/rfid
  *  include "rfid/src/MFRC522.h" and "rfid/src/MFRC522.cpp"
  */

#include <SPI.h>
#include "MFRC522.h"

#define Debug_Mode false

#define SS_PIN 10
#define RST_PIN 9
#define buzzer_PIN 7
#define relay_PIN 6
#define signal_PIN 5 //signal

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

#define Num_Of_List 5 
unsigned char ID_List[Num_Of_List][4]={ //set the Uid that can open the door
                                {0xFF,0xFF,0xFF,0xFF},
                                {0x00,0x00,0x00,0x01},
                                {0xAA,0xAA,0xAA,0xAA},
                                {0x99,0x99,0x00,0x00},
                                {0x00,0x00,0x00,0x00}}; 
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  if(Debug_Mode)
    Serial.println("Wait for new card");
  pinMode(buzzer_PIN,OUTPUT);
  pinMode(relay_PIN,OUTPUT);
  pinMode(signal_PIN,OUTPUT);
  digitalWrite(buzzer_PIN,LOW);
  digitalWrite(relay_PIN,LOW);
  digitalWrite(signal_PIN,HIGH); //signal high
}

void loop() {
  bool inList = false;
  // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  } else{
    delay(1000); //wait for 1 sec to avoid person don't find correct area
  }
  
  // Select one of the cards
  if (mfrc522.PICC_ReadCardSerial()) {
    inList = false;
    buzz(100);
    if(Debug_Mode) {
      Serial.print("Card ID:");
      show_id(mfrc522);
    }
    for(byte i=0;i<Num_Of_List;i++) {  // check ID list
      for(byte j=0;j<4 && mfrc522.uid.uidByte[j]==ID_List[i][j];j++){
        if( j==3 ) {
          inList = true;
        } 
      }
    }
    delay(100);
    buzz(100);
    if(inList) {
      digitalWrite(signal_PIN,LOW); //signal low
      if(Debug_Mode)
        Serial.println("Card in List");
      digitalWrite(relay_PIN,HIGH);
    }
    else { 
      if(Debug_Mode) 
        Serial.println("Card unknow");
      digitalWrite(signal_PIN,HIGH); //signal high
      digitalWrite(relay_PIN,LOW); 
    }
  } else {
    return;
  }
  delay(2000);
}

void show_id(MFRC522 item) { //show uid in hex
  for(byte i = 0; i <4; i++)
    {
      Serial.print(item.uid.uidByte[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
}

void buzz(int ms){  //buzz(delaytime)
  digitalWrite(buzzer_PIN,HIGH);
  delay(ms);
  digitalWrite(buzzer_PIN,LOW);
}


