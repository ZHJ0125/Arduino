// Navigate to the Sketch > Include Library > Manage Libraries…Wait for Library Manager to download libraries index and update list of installed libraries.
// Filter your search by typing ‘ntpclient’. There should be a couple entries. Look for NTPClient by Fabrice Weinberg. Click on that entry, and then select Install.
// Test By ZhangHoujin 2020.05.17

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Your Network Name";
const char *password = "Your Password";

const long utcOffsetInSeconds = 28800;
// For UTC -5.00 : -5 * 60 * 60 : -18000
// For UTC +8.00 : 8 * 60 * 60 : 28800
// For UTC +0.00 : 0 * 60 * 60 : 0

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.pool.aliyun.com", utcOffsetInSeconds);
// pool.ntp.org

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
