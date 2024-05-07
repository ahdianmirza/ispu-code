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

// Inisialisasi fungsi
void mq7_sensor();
void mq135_sensor();

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");
}

void loop() {
  Serial.println("============================================");
  mq7_sensor();
  mq135_sensor();
  Serial.println("============================================");
  delay(1000);
}
