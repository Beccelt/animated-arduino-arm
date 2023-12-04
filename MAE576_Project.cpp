#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <MadgwickAHRS.h>
#include <Wire.h>
#include <Servo.h>

// Make instances of the libraries
Adafruit_MPU6050 mpu;

Madgwick filter;

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

// Madgwick filter requires an update rate, this value is in Hz
const int filterUpdateRate = 75;

void setup(void) {
  Serial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  filter.begin(filterUpdateRate);

  servo1.attach(7);
  servo2.attach(6); 
  servo3.attach(5); 
  servo4.attach(4); 

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

void loop() {
  // Read sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  filter.updateIMU(g.gyro.x, g.gyro.y, g.gyro.z, a.acceleration.x, a.acceleration.y, a.acceleration.z);

  // Get the orientation (roll, pitch, yaw) from the filter
  float roll = filter.getRoll();
  float pitch = filter.getPitch();
  float yaw = filter.getYaw();

  // Map roll, pitch, yaw to servo angles
  int servo1Angle = map(yaw, -90, 90, 0, 180);   // For yaw
  int servo2Angle = map(roll, -90, 90, 0, 180);  // For roll
  int servo3Angle = map(pitch, -90, 90, 0, 180); // For pitch

  // Write to servos
  servo1.write(servo1Angle);
  servo2.write(servo2Angle);
  servo3.write(servo3Angle);
}
