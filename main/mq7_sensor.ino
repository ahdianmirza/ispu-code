void mq7_sensor() {
  mq7_value = analogRead(mq7_pin);
  mq7_voltage = (mq7_value / 1023.0) * 5.0;
  mq7_ppm = constrain(((mq7_voltage / 0.1) - 10.0), 0, 1000);
  mq7_CO = (mq7_ppm * 28) / (24.5 * 0.001);
  Serial.print("MQ7 analog value: "); Serial.println(mq7_value);
  Serial.print("MQ7 voltage: "); Serial.println(mq7_voltage);
  Serial.print("MQ7 ppm: "); Serial.println(mq7_ppm);
  Serial.print("MQ7 CO: "); Serial.println(mq7_CO);
  delay(1000);
}
