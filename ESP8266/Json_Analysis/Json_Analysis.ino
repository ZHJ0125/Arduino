// Tests for analyzing json with NodeMCU
// ZhangHoujin 2021.03.04

#include <ArduinoJson.h>
String Str = "{\"errno\":0,\"data\":{\"update_at\":\"2021-03-04 09:10:00\",\"id\":\"Temperature\",\"create_time\":\"2021-03-03 22:26:07\",\"current_value\":24},\"error\":\"succ\"}";

void setup() {
  Serial.begin(9600);
}

void loop(){
  Json_Analysis(Str);
  delay(2000);
}

void Json_Analysis(String input){
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, input);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
  int errno = doc["errno"]; // 0
  JsonObject data = doc["data"];
  const char* data_update_at = data["update_at"]; // "2021-03-04 09:10:00"
  const char* data_id = data["id"]; // "Temperature"
  const char* data_create_time = data["create_time"]; // "2021-03-03 22:26:07"
  int data_current_value = data["current_value"]; // 24
  const char* succ = doc["error"]; // "succ"
  
  Serial.println("data_update_at: " + String(data_update_at));
  Serial.println("data_id: " + String(data_id));
  Serial.println("data_create_time: " + String(data_create_time));
  Serial.println("data_current_value: " + String(data_current_value));
  Serial.println("succ: " + String(succ));
}
