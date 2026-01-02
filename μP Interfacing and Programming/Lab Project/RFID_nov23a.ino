void setup(){
  Serial.begin(9600);
  Serial.println("Scan RFID Card...");
}

void loop(){
  if (Serial.available()) {
    String UID = Serial.readStringUntil('\n');
    Serial.print("Card ID: ");
    Serial.println(UID);
  }
}
