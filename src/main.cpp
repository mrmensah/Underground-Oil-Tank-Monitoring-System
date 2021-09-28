#include "Functions.h"

void setup()
{
  // Pin declarations
  pinMode(UTS_TRIGGER, OUTPUT);
  pinMode(UTS_ECHO, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);

  Serial.begin(9600);
  sensor.begin(); // Temperature Sensor

  /***************
   * LCD display *
   * *************/

  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Hello Welcome");
  delay(1500);
  
  checkInternet(); // connect to wifi
}

void loop()
{
  sendData(readTemp(), readLevel()); //posting to the database
  delay(time);
}
