int state = 0;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
    Serial.println("Recived!");
 }
 if (state == "0") {
  digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == "1") {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED: ON");
  state = 0;
 } 
}
