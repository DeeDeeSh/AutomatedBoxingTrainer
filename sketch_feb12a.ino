#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found. Check wiring or I2C address!");
    while (1) delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 Ready! Begin punching 🥊");
  delay(100);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float ax = accel.acceleration.x;
  float ay = accel.acceleration.y;
  float az = accel.acceleration.z;
  float gx = gyro.gyro.x;
  float gy = gyro.gyro.y;
  float gz = gyro.gyro.z;

  String punch = "No Punch";

  // ----- Thresholds (adjust as per testing) -----
  if (abs(ax) > 6 ) {
    punch = "Hook";
  } else if (abs(ay) > 7 && abs(gz) > 0) {
    punch = "Jab";
  } else if (abs(az) > 0 || (abs(gz) > 0.0 && abs(gy) > 0)) {
    punch = "Uppercut";
  }

  Serial.print("Accel X: "); Serial.print(ax); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(ay); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(az); Serial.print(" || ");
  Serial.print("Gyro X: "); Serial.print(gx); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(gy); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(gz); Serial.print(" || ");

  Serial.print("Detected: ");
  Serial.println(punch);

  delay(1000);
}