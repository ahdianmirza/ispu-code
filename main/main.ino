// Import Library
#include <LiquidCrystal_I2C.h>

// Define Pin Sensor
#define mq7_pin 33
#define mq135_pin 35

// MQ7 Sensor
int mq7_value;
float mq7_voltage;
float mq7_ppm;
float mq7_CO;

// MQ135 Sensor
int mq135_value;
float mq135_voltage;
float mq135_ppm;
float mq135_NO2;

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
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Inisialisasi fungsi
void mq7_sensor();
void mq135_sensor();

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");

  // Start the LCD
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, microSymbol);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Connected");
  delay(3000);
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
  lcd.print("m/m3");

  lcd.setCursor(0,1);
  lcd.print("NO2=");
  lcd.print(mq135_NO2);
  lcd.write(byte(0));
  lcd.print("m/m3");
  delay(1000);
}
