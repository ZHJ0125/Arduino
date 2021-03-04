// Upload data using OneNET + NodeMCU
// Test By ZhangHoujin 2021.03.04

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define DEVICE_ID "xxxxxxxxxxxxxx"
#define  API_Key  "xxxxxxxxxxxxxx"
String   GET_URL = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/Temperature";
String  POST_URL = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datapoints";
const char* ssid = "xxxxxxxxxxxx";
const char* password = "xxxxxxxx";
int temp = 20;
int humi = 30;

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");        // Waiting for connection
  }
  Serial.println("\nWiFi Connected!");
}

void loop(){
  if((WiFi.status() == WL_CONNECTED)){
    if(++temp>40){temp=20;}   // Data for simulation
    if(++humi>60){humi=30;}
    ESP8266_POST();
    delay(3000);  // 3s
    ESP8266_GET();
  }
  else{
    Serial.println("[ERROR] WiFi Disconnected!");
  }
  delay(2000);
}

void ESP8266_GET(){
  HTTPClient httpClient;
  httpClient.begin(GET_URL);
  //Serial.print("GET_URL: "); Serial.println(GET_URL);

  httpClient.setReuse(true);    // Keep-Alive
  httpClient.addHeader("api-key", API_Key);
  
  int httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + String(GET_URL));

  if(httpCode == HTTP_CODE_OK){
    String responsePayload = httpClient.getString();
    Json_Analysis_GET(responsePayload);
    //Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  }
  else{
    Serial.println("Server Respose Code：" + httpCode);
  }
}

void ESP8266_POST(){
  WiFiClient client;
  HTTPClient httpClient;
  String pay = "{\"datastreams\":[{\"id\":\"Temperature\",\"datapoints\":[{\"value\":" + String(temp) + "}]},{\"id\": \"Humidity\",\"datapoints\":[{\"value\":" + String(humi) + "}]}]}";
  //Serial.println("pay: " + pay);

  httpClient.begin(client, POST_URL);
  httpClient.setReuse(true);  //Keep-Alive
  httpClient.addHeader("api-key", API_Key);
  //Serial.print("[POST] begin\n");
  int httpCode = httpClient.POST(pay);
  //Serial.print("[POST] .....\n");

  if(httpCode > 0){
    //Serial.printf("[POST] Code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK){
      const String& payload = httpClient.getString();
      Serial.println("[POST] Received: " + payload);
      Serial.println("-------------------------------------------\n");
    }
  }
  else{
    Serial.printf("[ERROR] Failed, POST error: %s\n", httpClient.errorToString(httpCode).c_str());
  }
}

void Json_Analysis_GET(String input){
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
  
  Serial.println("[GET]     data_id: " + String(data_id));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at));
  Serial.println("[GET] create_time: " + String(data_create_time));
  if(succ == "succ"){
    Serial.println("[GET] OK!");
  }
  
}
