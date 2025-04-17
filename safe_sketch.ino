void setup() {
  Serial.begin(9600); // Same baud as 8051 UART
}

void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read()); // Pass data to PC
  }
}
