void updateDataSensor() {
  if (millis() - lastTimeUpdate > timerDelayUpdate) {
    if (WiFi.status() == WL_CONNECTED) {
      float CO_postData, NO2_postData, ispu_CO_postData, ispu_NO2_postData;
      String postData;

      CO_postData = mq7_CO;
      NO2_postData = mq135_NO2;
      ispu_CO_postData = ispu_CO;
      ispu_NO2_postData = ispu_NO2;
      postData = "co=" + String(CO_postData) + "&no2=" + String(NO2_postData) + "&ispu_co=" + String(ispu_CO_postData) + "&ispu_no2=" + String(ispu_NO2_postData);

      HTTPClient http;
      http.setTimeout(1000);
      http.begin("http://192.168.101.58:8080/api/data-dashboard");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      auto httpCode = http.POST(postData);
      String payload = http.getString();

      Serial.print("httpCode update: "); Serial.println(httpCode);
      Serial.print("postData update: "); Serial.println(postData);
      Serial.print("payload update: "); Serial.println(payload);

      http.end();
    } else {
      Serial.println("Wifi Disconnected!");
    }
    lastTimeUpdate = millis();
  }
}
