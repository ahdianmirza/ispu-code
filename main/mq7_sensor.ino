void mq7_sensor() {
  mq7_value = analogRead(mq7_pin);
  mq7_voltage = (mq7_value / 1023.0) * 5.0;
  mq7_ppm = constrain(((mq7_voltage / 0.1) - 10.0), 0, 1000);
  mq7_CO = (mq7_ppm * 28) / (24.5 * 0.001);
  Serial.print("MQ7 analog value: "); Serial.println(mq7_value);
  Serial.print("MQ7 voltage: "); Serial.println(mq7_voltage);
  Serial.print("MQ7 ppm: "); Serial.println(mq7_ppm);
  Serial.print("MQ7 CO: "); Serial.println(mq7_CO);

  // ISPU CO
  if (mq7_CO >= 0 && mq7_CO <= 4000) {
    ispu_CO = ((50.0 - 0) / (4000.0 - 0)) * (mq7_CO - 0) + 0;
  } else if (mq7_CO >= 4001 && mq7_CO <= 8000) {
    ispu_CO = ((100.0 - 50) / (8000.0 - 4000)) * (mq7_CO - 4000.0) + 50;
  } else if (mq7_CO >= 8001 && mq7_CO <= 15000) {
    ispu_CO = ((200.0 - 100) / (15000.0 - 8000)) * (mq7_CO - 8000.0) + 100;
  } else if (mq7_CO >= 15001 && mq7_CO <= 30000) {
    ispu_CO = ((300.0 - 200) / (30000.0 - 15000)) * (mq7_CO - 15000.0) + 200;
  } else if (mq7_CO >= 30001 && mq7_CO <= 45000) {
    ispu_CO = ((301.0 - 300) / (45000.0 - 30000)) * (mq7_CO - 30000.0) + 300;
  } else if (mq7_CO >= 500) {
    ispu_CO = 301;
  }

  // Status ISPU
  if (ispu_CO >= 0 && ispu_CO <= 50) {
    status_CO = "baik";
  } else if (ispu_CO >= 51 && ispu_CO <= 100) {
    status_CO = "sedang";
  } else if (ispu_CO >= 101 && ispu_CO <= 200) {
    status_CO = "tidak sehat";
  } else if (ispu_CO >= 201 && ispu_CO <= 300) {
    status_CO = "sangat tidak sehat";
  } else if (ispu_CO >= 300) {
    status_CO = "berbahaya";
  }

  Serial.print("ISPU CO: "); Serial.println(ispu_CO);
  Serial.print("Status ISPU CO: "); Serial.println(status_CO);
}
