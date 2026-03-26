# MPU6050 C++ Library (Embedded Linux)

A lightweight, low-level C++ library for interfacing with the MPU6050 (accelerometer + gyroscope + temperature sensor) over I2C on embedded Linux systems.

## Features
- Direct I2C communication via `/dev/i2c-*`
- Minimal dependencies (POSIX only)
- Read:
  - Accelerometer (X, Y, Z)
  - Gyroscope (X, Y, Z)
  - Temperature
  - Configurable full-scale ranges
- Simple, predictable API (no hidden abstractions)

## Requirements
- Linux with I2C support (`i2c-dev`)
- Access to `/dev/i2c-*`
- MPU6050 connected via I2C

## Installation
Simply clone this repository via:

'''bash
git clone https://github.com/yishaqsilva/mpu6050
'''

## Usage

Use i2cdetect to find the bus the mpu6050 module is currently attached to:

bash'''
sudo i2cdetect -y 1
'''

c++'''
#include "mpu6050.h"

mpu6050 m(1); // dev/i2c-1

//converted values
float x = m.accel_x();
float t = m.temp();
float g = m.gyro_x();

//raw values
float k = m.gyro_y_raw();

//configuration
m.config_accel_

//bypass abstractions and extend functionality with
m.write_byte(0x6B, 0x00);

m.read_byte(0x75);
'''
