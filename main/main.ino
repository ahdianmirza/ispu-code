// MQ7 Sensor
#define mq7_pin 33
int mq7_value;
float mq7_voltage;
float mq7_ppm;
float mq7_CO;

// Inisialisasi fungsi
void mq7_sensor();

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");
}

void loop() {
  mq7_sensor();
}
