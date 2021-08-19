/* Defining the pins */
#define LCD_SCL 5
#define LCD_SDA 4
#define UTS_TRIGGER D5
#define UTS_ECHO D6
#define TEMP 16
#define GRN_LED 12
#define RED_LED 14
#define MAX_DISTANCE 200

// Password setup
const char *ssid = "Mensah's Nokia";
const char *password = "lucille1";

// important must be global
float oil_level{};
float temperatureC{};
