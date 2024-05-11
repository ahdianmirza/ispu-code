#include <LiquidCrystal_I2C.h>

#define mq7_sensor 33
int mq7_value;
float mq7_voltage;
float mq7_ppm;
float mq7_CO;
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
  mq7_value = analogRead(mq7_sensor);
  mq7_voltage = (mq7_value / 1023.0) * 5.0;
  mq7_ppm = constrain(((mq7_voltage / 0.1) - 10.0), 0, 1000);
  mq7_CO = (mq7_ppm * 28) / (24.5 * 0.001);
  Serial.print("MQ7 analog value: "); Serial.println(mq7_value);
  Serial.print("MQ7 voltage: "); Serial.println(mq7_voltage);
  Serial.print("MQ7 ppm: "); Serial.println(mq7_ppm);
  Serial.print("MQ7 CO: "); Serial.println(mq7_CO);

  // LCD Print 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO=");
  lcd.print(mq7_CO);
  lcd.write(byte(0));
  lcd.print("m/m3");
  delay(1000);
}
