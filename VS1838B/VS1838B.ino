// Infrared Reception
// NodeMCU + VS1838
// Test By ZhangHoujin 2020.05.19

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = 14;
IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    if(results.value == 0x8F7C03F){
      digitalWrite(5, HIGH);
      Serial.println("灯已打开");
    }
    else{
      digitalWrite(5, LOW);
      Serial.println("灯已关闭");
    }
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  delay(100);
}
