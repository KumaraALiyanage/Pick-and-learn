#include <MFRC522.h>

#define NR_OF_READERS   3

#define RST_PIN 9
#define SS_PIN_1 4
#define SS_PIN_2 5
#define SS_PIN_3 6

// Define RFID scanner numbers
const int scanner1 = 2;
const int scanner2 = 3;
//const int scanner3 = 4;

MFRC522 mfrc522[NR_OF_READERS] = {
  MFRC522(SS_PIN_1, RST_PIN),
  MFRC522(SS_PIN_2, RST_PIN),
  MFRC522(SS_PIN_3, RST_PIN)
};

void setup() {
  Serial.begin(9600);
  SPI.begin();

  Serial.println("");
}

void loop() {
  // Check if any card is detected on any scanner
  bool allCardsDetected = true;
  bool tag1Detected = true;
  bool tag2Detected = true;
  bool tag3Detected = true;

  // Scan all RFID readers
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      // If a card is detected, mark it
      allCardsDetected = false;

      String content = "";
      for (byte i = 0; i < mfrc522[reader].uid.size; i++) {
        content.concat(String(mfrc522[reader].uid.uidByte[i] < 0x10 ? "0" : ""));
        content.concat(String(mfrc522[reader].uid.uidByte[i], HEX));
      }
      content.toUpperCase();
      
      // Check which tag is detected
      if (content == "6D785838") {
        tag1Detected = false;
      } else if (content == "AD646737") {
        tag2Detected = true;
      } else if (content == "C3307698") {
        tag3Detected = true;
      }
    }
  }  

  // Print the detection result after scanning all readers
  if (allCardsDetected) {
    Serial.println("1"); // All tags are detected
  } else {
    if (tag1Detected) {
      Serial.println("22"); // Tag 1 is not detected
    }
    if (tag2Detected) {
      Serial.println("33"); // Tag 2 is not detected
    }
    if (tag3Detected) {
      Serial.println("44"); // Tag 3 is not detected
    }
  }
  
  // Add a small delay to avoid flooding the serial monitor
  delay(1000); 
}
