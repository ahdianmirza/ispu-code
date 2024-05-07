void mq135_sensor() {
  mq135_value = analogRead(mq135_pin);
  mq135_voltage = (mq135_value / 1023.0) * 5.0;
  mq135_ppm = constrain(((mq135_voltage / 0.2) * 100), 0, 1000);
  mq135_NO2 = (mq135_ppm * 46) / (24.5 * 0.001);
  Serial.print("mq135 analog value: "); Serial.println(mq135_value);
  Serial.print("mq135 voltage: "); Serial.println(mq135_voltage);
  Serial.print("mq135 ppm: "); Serial.println(mq135_ppm);
  Serial.print("mq135 NO2: "); Serial.println(mq135_NO2);
}
