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

// Initialize the pins for the servos

const int servoPin1 = 7;
const int servoPin2 = 6;
const int servoPin3 = 5;

// Initialize the home position for the servos
const int homePos = 0;

// Madgwick filter requires an update rate, this value is in Hz
const int filterUpdateRate = 75;

// Need to convert the equivalent servo rotation from sensor data
const long sensorRotMin = -90;
const long sensorRotMax = 90;
const long servoRotMin = 0;
const long servoRotMax = 180;

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

  servo1.attach(servoPin1);
  servo2.attach(servoPin2); 
  servo3.attach(servoPin3); 

  servo1.write(homePos);
  servo2.write(homePos);
  servo3.write(homePos);
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
  int servo1Angle = map(yaw, sensorRotMin, sensorRotMax, servoRotMin, servoRotMax);   // For yaw
  int servo2Angle = map(roll, sensorRotMin, sensorRotMax, servoRotMin, servoRotMax);  // For roll
  int servo3Angle = map(pitch, sensorRotMin, sensorRotMax, servoRotMin, servoRotMax); // For pitch

  // Write to servos
  servo1.write(servo1Angle);
  servo2.write(servo2Angle);
  servo3.write(servo3Angle);
}
