#include <Arduino.h>
#include "Libraries.h"
#include "Prototypes.h"
#include "Variables.h"

/* WiFi setup */
WiFiClient client;
WiFiServer server(80);

/* Setting up the LCD */
LiquidCrystal_I2C lcd(0x3F, 16, 2);

/* setting up temperature sensor */
OneWire oneWire(TEMP);
DallasTemperature sensor(&oneWire);

void readTemp()
{
  sensor.requestTemperatures();
  float temperatureC = sensor.getTempCByIndex(0);
  float temperatureF = sensor.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  // lcd.setCursor(0, 1);
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(5000);
}

void readLevel()
{
  //sending the signal
  digitalWrite(UTS_TRIGGER, LOW);
  delayMicroseconds(5);
  digitalWrite(UTS_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(UTS_TRIGGER, LOW);

  // Receiving the signal
  float duration = pulseIn(UTS_ECHO, HIGH);

  // calculating the distance in centimeters
  float cm = (duration / 2) / 29.1;
  //level of oil
  float oil_level = MAX_DISTANCE - cm;
  // float cross_sectional_area_of_tank{};
  // float oil_volume = oil_level * cross_sectional_area_of_tank;
  lcd.clear();
  Serial.print("level: ");
  Serial.print(oil_level);
  Serial.print(" m^3");

  // wait for a while then check again
  delay(2500);
}

// void takeValues(float value)
// {
//   // taking the values
//   float data = value;

//   // save the value into a file in the SPIFFS
// }

void sendValues()
{
  /* Check for internet connection
  if there is internet connection, send the data in the SPIFFS file
  
  else wait for 10 seconds and check again for two times then go back to taking values
  */
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/1"); //place server address here
    int httpCode = http.GET(); // change this a post request 

    if (httpCode > 0)
    {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject &root = jsonBuffer.parseObject(http.getString());

      int id = root["id"];
      const char *name = root["name"];
      const char *username = root["username"];
      const char *email = root["email"];

      Serial.print("Name:");
      Serial.println(name);
      Serial.print("Username:");
      Serial.println(username);
      Serial.print("Email:");
      Serial.println(email);
    }
    http.end(); //Close connection
  }
  delay(60000);
}

void checkInternet()
{
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.scrollDisplayLeft();
  lcd.print("Connecting to ");
  lcd.print(ssid);
  lcd.print(" ...");

  // Waiting for the Wifi to connect
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(++i);
    lcd.print(' ');
  }
  lcd.clear();
  lcd.scrollDisplayLeft();
  lcd.print("Connection established!");
  lcd.setCursor(0, 1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  delay(20500);
}

void displayValues()
{
}