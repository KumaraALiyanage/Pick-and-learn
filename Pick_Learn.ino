#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
                                        // A valid RFID tag is detected
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    
    Serial.println("1");                // Print "1" and continue looping while a recognized tag is present
    delay(500);
    while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {}
  } else{
    Serial.println("2");
    delay(500);                         // Add a small delay to avoid flooding the serial monitor
  }
}
