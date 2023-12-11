#include <SPI.h>
#include <MFRC522.h>

#define GREEN_LED 6
#define RED_LED   7
#define RFID_RST  5
#define RFID_SS   10

// MFRC522 mfrc522(RFID_SS, RFID_RST);
MFRC522 rfid(RFID_SS, RFID_RST); // Instance of the class

MFRC522::MIFARE_Key key;

String tagId = "";
// String authId = "60 88 57 53 ";
String authId = "";

void setup() {
	Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

	SPI.begin();
  rfid.PCD_Init();

}

void loop() {
 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
 
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 
  // Serial.print(rfid.uid.uidByte);
  Serial.print(F("RFID Tag UID:"));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println("");
 
  rfid.PICC_HaltA(); // Halt PICC
}
 
//Routine to dump a byte array as hex values to Serial. 
void printHex(byte *buffer, byte bufferSize) {

  tagId = "";

  for (byte i = 0; i < bufferSize; i++) {
    tagId.concat(String(rfid.uid.uidByte[i], HEX));
    tagId.concat(" ");
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
  Serial.print(tagId);
  Serial.println();
  Serial.print(tagId == "60 88 57 53 ");

  setAuth(tagId);
  tagId == authId ? flashLED(GREEN_LED) : flashLED(RED_LED);
}

void flashLED(int led) {
  digitalWrite(led, HIGH);
  delay(750);
  digitalWrite(led, LOW);
}

void setAuth(String tagId) {
  if (authId == "") {
    authId = tagId;
    flashLED(GREEN_LED);
    flashLED(RED_LED);
    flashLED(GREEN_LED);
    flashLED(RED_LED);
  }
}