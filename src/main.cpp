#include "Functions.h"

void setup()
{
  // Ultrasonic sensor
  pinMode(UTS_TRIGGER, OUTPUT);
  pinMode(UTS_ECHO, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);

  Serial.begin(9600);
  // Temperature Sensor
  sensor.begin();
  // LCD display
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin();
  // lcd.backlight();
  lcd.print("Hello Welcome");
  delay(1500);
  // readTemp();

  // Setting up a file to store the data collected
  // File temperature SPIFFS.open("/temperature.txt", "w");
  // File level SPIFFS.open("/level.txt", "w");
}

void loop()
{
  // digitalWrite(GRN_LED, HIGH);
  // delay(2000);
  // digitalWrite(GRN_LED, LOW);
  // delay(2000);
  readTemp();
  // checkInternet();
  // readLevel();
}

