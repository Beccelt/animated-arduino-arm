
# Motion-Controlled Arduino-Based Arm (Software Version)

This is the software version of the README file.


## Documentation

The following below is the code for main.cpp

https://github.com/Beccelt/animated-arduino-arm/blob/main/MAE576_Project.cpp






## Installation

Install to PlatformIO (on Visual Studio Code) the following:

```bash
	arduino-libraries/Servo@^1.2.1
	arduino-libraries/Madgwick@^1.2.0
	adafruit/Adafruit Unified Sensor@^1.1.14
	adafruit/Adafruit MPU6050@^2.2.6
```

Please make sure these are added with the latest version of every file.




    
## Libraries

Libraries:
<Adafruit_MPU6050.h> and <Adafruit_Sensor.h>:

These libraries are used for interfacing with the MPU6050 sensor, which is a popular IMU (Inertial Measurement Unit) capable of providing accelerometer and gyroscope data.
The Adafruit library simplifies reading data from the MPU6050.
<MadgwickAHRS.h>:

The Madgwick filter library is used for sensor fusion and orientation estimation. It combines accelerometer and gyroscope data to provide a more accurate and stable estimation of the sensor's orientation (roll, pitch, yaw).
<Wire.h>:

This library is used for I2C communication, which is the protocol used by the MPU6050 to communicate with the Arduino.
<Servo.h>:

The Servo library provides functions to control servo motors, making it easier to set the position of each servo.
