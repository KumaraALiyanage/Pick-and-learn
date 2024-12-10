#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("RFID Reader Initialized!");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();

    if (content == "6D785838") { 
      Serial.println("1");
    } else if (content == "AD646737") {
      Serial.println("2"); 
    } else if (content == "C3307698") {
      Serial.println("3"); 
    } else if (content == "53FB3E1C") {
      Serial.println("4"); 
    } else {
      Serial.println("ERROR!");
    }

    while (mfrc522.PICC_IsNewCardPresent()) {} 
  } else {
    // No RFID tag detected
    Serial.println("5"); 
    
    delay(1000); 
  }
}
