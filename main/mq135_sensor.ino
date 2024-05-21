void mq135_sensor() {
  mq135_value = analogRead(mq135_pin);
  mq135_voltage = (mq135_value / 1023.0) * 5.0;
  mq135_ppm = constrain(((mq135_voltage / 0.2) * 100), 0, 1000);
  mq135_NO2 = (mq135_ppm * 46) / (24.5 * 0.001);
  Serial.print("mq135 analog value: "); Serial.println(mq135_value);
  Serial.print("mq135 voltage: "); Serial.println(mq135_voltage);
  Serial.print("mq135 ppm: "); Serial.println(mq135_ppm);
  Serial.print("mq135 NO2: "); Serial.println(mq135_NO2);

  // ISPU NO2
  if (mq135_NO2 >= 0 && mq135_NO2 <= 80) {
    ispu_NO2 = ((50.0 - 0) / (80.0 - 0)) * (mq135_NO2 - 0) + 0;
  } else if (mq135_NO2 >= 81 && mq135_NO2 <= 200) {
    ispu_NO2 = ((100.0 - 50) / (200.0 - 80)) * (mq135_NO2 - 80.0) + 50;
  } else if (mq135_NO2 >= 201 && mq135_NO2 <= 1130) {
    ispu_NO2 = ((200.0 - 100) / (1130.0 - 200)) * (mq135_NO2 - 200.0) + 100;
  } else if (mq135_NO2 >= 1131 && mq135_NO2 <= 2260) {
    ispu_NO2 = ((300.0 - 200) / (2260.0 - 1130)) * (mq135_NO2 - 1130.0) + 200;
  } else if (mq135_NO2 >= 2261 && mq135_NO2 <= 3000) {
    ispu_NO2=((301.0 - 300) / (3000.0 - 2261)) * (mq135_NO2 - 2261.0) + 300;
  } else if (mq135_NO2 >= 3000) {
    ispu_NO2 = 301;
  }

  // Status ISPU
  if (ispu_NO2 >= 0 && ispu_NO2 <= 50) {
    status_NO2 = "baik";
  } else if (ispu_NO2 >= 51 && ispu_NO2 <= 100) {
    status_NO2 = "sedang";
  } else if (ispu_NO2 >= 101 && ispu_NO2 <= 200) {
    status_NO2 = "tidak sehat";
  } else if (ispu_NO2 >= 201 && ispu_NO2 <= 300) {
    status_NO2 = "sangat tidak sehat";
  } else if (ispu_NO2 >= 300) {
    status_NO2 = "berbahaya";
  }

  Serial.print("ISPU NO2: "); Serial.println(ispu_NO2);
  Serial.print("Status ISPU NO2: "); Serial.println(status_NO2);
}
