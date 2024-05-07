#define dust_density_pin 32

int ledPower = 22;
float vo_dustDensity;
float calcVoltage_dustDensity;
float dustDensity;
float dustDensity_value;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");
}

void loop() {
  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);
  vo_dustDensity = analogRead(dust_density_pin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepTime);
  
  calcVoltage_dustDensity = vo_dustDensity * (5.0/1023.0);
  dustDensity = 0.17 * calcVoltage_dustDensity - 0.1;
  dustDensity_value = dustDensity;
//  dustDensity = constrain(((170 * calcVoltage_dustDensity) - 0.1), 0, 1000);
//  dustDensity_value = constrain(dustDensity, 0, 1000);
  Serial.print("vo_dustDensity: "); Serial.println(vo_dustDensity);
  Serial.print("calcVoltage_dustDensity: "); Serial.println(calcVoltage_dustDensity);
  Serial.print("dustDensity: "); Serial.println(dustDensity);
  Serial.print("dustDensity_value: "); Serial.println(dustDensity_value);
  delay(1000);
}
