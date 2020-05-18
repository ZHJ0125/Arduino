// Used to detect photoresistor data
// NodeMCU + GM5516
// Written by ZhangHoujin on May 18, 2020
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  float sensorValue = analogRead(A0);
  Serial.print("sensorValue = ");
  Serial.println(sensorValue);
  delay(500);
}
