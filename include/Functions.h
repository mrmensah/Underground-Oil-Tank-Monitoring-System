#include <Arduino.h>
#include "Libraries.h"
#include "Prototypes.h"
#include "Variables.h"

WiFiClient client; // WiFi setup 
LiquidCrystal_I2C lcd(0x27, 16, 2); // Setting up the LCD
/* setting up temperature sensor */
OneWire oneWire(TEMP);
DallasTemperature sensor(&oneWire);

float readTemp()
{
  sensor.requestTemperatures();
  float temperatureC = sensor.getTempCByIndex(0);
  lcd.clear();
  lcd.print("tmp: ");
  lcd.print(temperatureC);
  lcd.print(" ºC");
  return temperatureC;
}

float readLevel()
{
  //sending the signal
  digitalWrite(UTS_TRIGGER, LOW);
  delayMicroseconds(5);
  digitalWrite(UTS_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(UTS_TRIGGER, LOW);
  float duration = pulseIn(UTS_ECHO, HIGH);  // Receiving the signal
  float cm = (duration / 2) / 29.1; // calculating the distance in centimeters
  float oil_level = MAX_DISTANCE - cm; //level of oil
  lcd.setCursor(0, 1);
  lcd.print("level: ");
  lcd.print(oil_level);
  lcd.print(" cm");
  return oil_level;
}

void sendData(float temp, float lvl)
{
  // Creating json data
  StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
  JsonObject &JSONencoder = JSONbuffer.createObject();

  //Encoding data
  JSONencoder["temperature"] = temp;
  JSONencoder["level"] = lvl;

  char JSONmessageBuffer[300];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);

  // Declaring object class of  the HTTPClient
  HTTPClient http;

  http.begin(client, "http://192.168.205.185:8000/data/");
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONmessageBuffer); //Send the request
  String payload = http.getString();           //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  if (httpCode == 200)
  {
    for (int x = 0; x < 5; x++)
    {
      digitalWrite(GRN_LED, HIGH);
      delay(500);
      digitalWrite(GRN_LED, LOW);
      delay(500);
    }
  }
  http.end(); //Close connection
}
void checkInternet()
{
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.scrollDisplayLeft();
  lcd.print("Connecting to ");
  lcd.print(ssid);
  lcd.println(" ...");

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
  WiFi.mode(WIFI_STA);
  delay(2500); 
}


