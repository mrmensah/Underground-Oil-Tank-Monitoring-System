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

  // connect to wifi
  checkInternet();

  //Setting ESP as access point
  // createAP();
}

void loop()
{
  // digitalWrite(GRN_LED, HIGH);
  // delay(2000);
  // digitalWrite(GRN_LED, LOW);
  // delay(2000);
  // readTemp();
  // checkInternet();
  // readLevel();

  sendData(); //posting to the database
  delay(50000);
}
