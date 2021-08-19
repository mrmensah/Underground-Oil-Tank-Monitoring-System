#include <Arduino.h>
#include "Libraries.h"
#include "Prototypes.h"
#include "Variables.h"

/* WiFi setup */
WiFiClient client;
// WiFiServer server(80);

/* Setting up the LCD */
LiquidCrystal_I2C lcd(0x3F, 16, 2);
/* setting up temperature sensor */
OneWire oneWire(TEMP);
DallasTemperature sensor(&oneWire);

void readTemp()
{
  sensor.requestTemperatures();
  temperatureC = sensor.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
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
  oil_level = MAX_DISTANCE - cm;
  lcd.clear();
  Serial.print("level: ");
  Serial.print(oil_level);
  Serial.print(" cm");

  // wait for a while then check again
  delay(2500);
}

// void takeValues(float value)
// {
//   // taking the values
//   float data = value;

//   // save the value into a file in the SPIFFS
// }

// void sendValues()
// {
//   /* Check for internet connection
//   if there is internet connection, send the data in the SPIFFS file

//   else wait for 10 seconds and check again for two times then go back to taking values
//   */
//   if (WiFi.status() == WL_CONNECTED)
//   {
//     HTTPClient http;                    //Object of class HTTPClient
//     http.begin("127.0.0.1:8000/data/"); //place server address here
//     int httpCode = http.GET();          // change this a post request

//     if (httpCode > 0)
//     {
//       const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
//       DynamicJsonBuffer jsonBuffer(bufferSize);
//       JsonObject &root = jsonBuffer.parseObject(http.getString());

//       int id = root["id"];
//       const char *name = root["name"];
//       const char *username = root["username"];
//       const char *email = root["email"];

//       Serial.print("Name:");
//       Serial.println(name);
//       Serial.print("Username:");
//       Serial.println(username);
//       Serial.print("Email:");
//       Serial.println(email);
//     }
//     http.end(); //Close connection
//   }
//   delay(60000);
// }

void sendData()
{
  // Creating json data
  StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
  JsonObject &JSONencoder = JSONbuffer.createObject();

  //Encoding data
  JSONencoder["temperature"] = temperatureC;
  JSONencoder["level"] = oil_level;

  char JSONmessageBuffer[300];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);

  // Declaring object class of  the HTTPClient
  HTTPClient http;

  http.begin(client, "http://127.0.0.1:8000/data/");
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONmessageBuffer); //Send the request
  String payload = http.getString();           //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  // Serial.println(payload);  //Print request response payload

  http.end(); //Close connection
}
void checkInternet()
{
  WiFi.begin(ssid, password);
  // lcd.clearSerial
  // lcd.scrollDisplayLeft();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" ...");

  // Waiting for the Wifi to connect
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    // lcd.setCursor(0, 1);
    Serial.print(++i);
    Serial.print(' ');
  }
  // lcd.clear();
  // lcd.scrollDisplayLeft();
  Serial.print("Connection established!");
  // lcd.setCursor(0, 1);
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  delay(2500);
}

void createAP()
{
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}
