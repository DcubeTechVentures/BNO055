// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BNO055
// This code is designed to work with the BNO055_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// BNO055 I2C address is 0x28(40)
#define Addr 0x28

int xAccl = 0, yAccl =  0, zAccl = 0, xGyro = 0, yGyro = 0, zGyro = 0, xMag = 0, yMag = 0, zMag = 0;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "BNO055");
  Particle.variable("xAccl", xAccl);
  Particle.variable("yAccl", yAccl);
  Particle.variable("zAccl", zAccl);
  Particle.variable("xGyro", xGyro);
  Particle.variable("yGyro", yGyro);
  Particle.variable("zGyro", zGyro);
  Particle.variable("xMag", xMag);
  Particle.variable("yMag", yMag);
  Particle.variable("zMag", zMag);

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
{
  unsigned int data[6];

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
  xAccl = ((data[1] * 256) + data[0]);
  if (xAccl > 32767)
  {
    xAccl -= 65536;
  }

  yAccl = ((data[3] * 256) + data[2]);
  if (yAccl > 32767)
  {
    yAccl -= 65536;
  }

  zAccl = ((data[5] * 256) + data[4]);
  if (zAccl > 32767)
  {
    zAccl -= 65536;
  }

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
  xMag = ((data[1] * 256) + data[0]);
  if (xMag > 32767)
  {
    xMag -= 65536;
  }
  yMag = ((data[3] * 256) + data[2]);
  if (yMag > 32767)
  {
    yMag -= 65536;
  }
  zMag = ((data[5] * 256) + data[4]);
  if (zMag > 32767)
  {
    zMag -= 65536;
  }

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
  xGyro = ((data[1] * 256) + data[0]);
  if (xGyro > 32767)
  {
    xGyro -= 65536;
  }
  yGyro = ((data[3] * 256) + data[2]);
  if (yGyro > 32767)
  {
    yGyro -= 65536;
  }
  zGyro = ((data[5] * 256) + data[4]);
  if (zGyro > 32767)
  {
    zGyro -= 65536;
  }

  // Output data to dashboard
  Particle.publish("X-Axis of rotation : ", String(xGyro));
  Particle.publish("Y-Axis of rotation : ", String(yGyro));
  Particle.publish("Z-Axis of rotation : ", String(zGyro));
  delay(500);
  Particle.publish("Acceleration in X-Axis : ", String(xAccl));
  Particle.publish("Acceleration in Y-Axis : ", String(yAccl));
  Particle.publish("Acceleration in Z-Axis : ", String(zAccl));
  delay(500);
  Particle.publish("Magnetic field in X-Axis : ", String(xMag));
  Particle.publish("Magnetic field in Y-Axis : ", String(yMag));
  Particle.publish("Magnetic filed in Z-Axis : ", String(zMag));
  delay(500);
}
