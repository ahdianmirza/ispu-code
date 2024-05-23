// Import Library
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <MQ7.h>

// Define Pin Sensor
//#define mq7_pin 33
#define mq135_pin 35

// MQ7 Sensor
MQ7 mq7(33, 3.3);
int mq7_value;
float mq7_voltage;
float mq7_ppm;
float mq7_CO;

// MQ135 Sensor
int mq135_value;
float mq135_voltage;
float mq135_ppm;
float mq135_NO2;

// ISPU Value
float ispu_CO;
float ispu_NO2;

// ISPU Condition
String status_CO;
String status_NO2;

// LCD Need
byte microSymbol[8] = {
  B00000,
  B10001,
  B10001,
  B10001,
  B11110,
  B10000,
  B10000,
  B00000
};
byte cubicSymbol[8] = {
  B11100,
  B00100,
  B11100,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000
};
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Post API
unsigned long lastTime = 0;
unsigned long lastTimeUpdate = 0;
unsigned long timerDelay = 10000;
unsigned long timerDelayUpdate = 5000;

// Inisialisasi fungsi
void mq7_sensor();
void mq135_sensor();
void postDataSensor();
void updateDataSensor();

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");

  //  Wifi Manager
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  // reset setting
//  res = wm.resetSettings();
  res = wm.autoConnect("ESP32-ISPU MONITORING TEST", "");

  // Start the LCD
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, microSymbol);
  lcd.createChar(1, cubicSymbol);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Waiting to connect");

  // Wifi Condition 
  if (!res) {
    Serial.println("Failed to connect");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Failed to connect");
    delay(1000);
    // ESP.restart();
  } else {
    Serial.println("Connected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connected!");
    delay(3000);
  }
}

void loop() {
  Serial.println("============================================");
  mq7_sensor();
  mq135_sensor();
  Serial.println("============================================");

  // LCD Print 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO=");
  lcd.print(mq7_CO);
  lcd.write(byte(0));
  lcd.print("g/m");
  lcd.write(byte(1));

  lcd.setCursor(0,1);
  lcd.print("NO2=");
  lcd.print(mq135_NO2);
  lcd.write(byte(0));
  lcd.print("g/m");
  lcd.write(byte(1));

  lcd.setCursor(0,2);
  lcd.print("ISPU CO = ");
  lcd.print(ispu_CO);

  lcd.setCursor(0,3);
  lcd.print("ISPU NO2 = ");
  lcd.print(ispu_NO2);

  // Send Data to Database 
  postDataSensor();
  updateDataSensor();
  delay(1000);
}
