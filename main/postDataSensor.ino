void postDataSensor() {
    if((millis() - lastTime > timerDelay)) {
        if (WiFi.status() == WL_CONNECTED) {
            float CO_postData, NO2_postData, ispu_CO_postData, ispu_NO2_postData;
            String postData;

            CO_postData = mq7_CO;
            NO2_postData = mq135_NO2;
            ispu_CO_postData = ispu_CO;
            ispu_NO2_postData = ispu_NO2;
            postData = "co=" + String(CO_postData) + "&no2=" + String(NO2_postData) + "&ispu_co=" + String(ispu_CO_postData) + "&ispu_no2=" + String(ispu_NO2_postData);

            HTTPClient http;
//            http.setTimeout(1000);
            http.begin("http://192.168.101.58:8080/api/log-data");
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");

            auto httpCode = http.POST(postData);
            String payload = http.getString();

            Serial.print("httpCode: "); Serial.println(httpCode);
            Serial.print("postData: "); Serial.println(postData);
            Serial.print("payload: "); Serial.println(payload);

            http.end();
        } else {
            Serial.println("Wifi Disconnected!");
        }
        lastTime = millis();
    }
}
