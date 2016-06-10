// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BNO055
// This code is designed to work with the BNO055_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <Wire.h>

// BNO055 I2C address is 0x28(40)
#define Addr 0x28

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select OPR_MODE register
  Wire.write(0x3D);
  // Accelerometer, Magnetometer and Gyrometer enabled
  Wire.write(0x07);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select PWR_MODE register
  Wire.write(0x3E);
  // Normal mode
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select PAGE_ID register
  Wire.write(0x07);
  // Shift to Page-1
  Wire.write(0x01);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select ACC_CONFIG register
  Wire.write(0x08);
  // Range = 4G, B/W = 62.5, Normal mode
  Wire.write(0x0D);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select MAG_CONFIG register
  Wire.write(0x09);
  // Data o/p rate = 10 Hz, Regular mode, normal mode
  Wire.write(0x0B);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select GYRO_CONFIG1 register
  Wire.write(0x0A);
  // Range = 2000 dps, B/W  = 32 Hz
  Wire.write(0x38);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select GYRO_CONFIG2 register
  Wire.write(0x0B);
  // Normal mode
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select PAGE_ID register
  Wire.write(0x07);
  // Shift to Page-0
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{ unsigned int data[6];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Acceleration data register
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();


  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int xAccl = ((data[1] * 256) + data[0]);
  int yAccl = ((data[3] * 256) + data[2]);
  int zAccl = ((data[5] * 256) + data[4]);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select magnetometer data register
  Wire.write(0x0E);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int xMag = ((data[1] * 256) + data[0]);
  int yMag = ((data[3] * 256) + data[2]);
  int zMag = ((data[5] * 256) + data[4]);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select gyrometer data register
  Wire.write(0x14);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int xGyro = ((data[1] * 256) + data[0]);
  int yGyro = ((data[3] * 256) + data[2]);
  int zGyro = ((data[5] * 256) + data[4]);

  // Output data to serial monitor
  Serial.print("X-Axis of rotation : ");
  Serial.println(xGyro);
  Serial.print("Y-Axis of rotation : ");
  Serial.println(yGyro);
  Serial.print("Z-Axis of rotation : ");
  Serial.println(zGyro);
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis : ");
  Serial.println(zAccl);
  Serial.print("Magnetic field in X-Axis : ");
  Serial.println(xMag);
  Serial.print("Magnetic field in Y-Axis : ");
  Serial.println(yMag);
  Serial.print("Magnetic filed in Z-Axis : ");
  Serial.println(zMag);
  delay(1000);
}
