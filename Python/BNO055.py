# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# BNO055
# This code is designed to work with the BNO055_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# BNO055 address, 0x28(40)
# Select OPR_MODE register, 0x3D(61)
# 		0x07(07)	Accelerometer, Magnetometer and Gyrometer enabled
bus.write_byte_data(0x28, 0x3D, 0x07)
# BNO055 address, 0x28(40)
# Select PWR_MODE register, 0x3E(62)
# 		0x00(0)		Normal mode
bus.write_byte_data(0x28, 0x3E, 0x00)
# BNO055 address, 0x28(40)
# Select PAGE_ID register, 0x07(07)
# 		0x01(01)	Shift to Page-1
bus.write_byte_data(0x28, 0x07, 0x01)
# BNO055 address, 0x28(40)
# Select ACC_CONFIG register, 0x08(08)
# 		0x0D(13)	Range = 4G, B/W = 62.5, Normal mode
bus.write_byte_data(0x28, 0x08, 0x0D)
# BNO055 address, 0x28(40)
# Select MAG_CONFIG register, 0x09(09)
# 		0x0B(11)	Data o/p rate = 10 Hz, Regular mode, normal mode
bus.write_byte_data(0x28, 0x09, 0x0B)
# BNO055 address, 0x28(40)
# Select GYRO_CONFIG1 register, 0x0A(10)
# 		0x38(56)	Range = 2000 dps, B/W  = 32 Hz
bus.write_byte_data(0x28, 0x0A, 0x38)
# BNO055 address, 0x28(40)
# Select GYRO_CONFIG2 register
# 		0x00(0)		Normal mode, 0x0B(11)
bus.write_byte_data(0x28, 0x0B, 0x00)
# BNO055 address, 0x28(40)
# Select PAGE_ID register, 0x07(07)
# 		0x00(00)	Shift to Page-0
bus.write_byte_data(0x28, 0x07, 0x00)
time.sleep(0.5)

# BNO055 address, 0x28(40)
# Read data back from 0x08(08), 6 bytes
# xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
data = bus.read_i2c_block_data(0x28, 0x08, 6)

# Convert the data
xAccl = data[1] * 256 + data[0]
if xAccl > 32767 :
	xAccl -= 65536

yAccl = data[3] * 256 + data[2]
if yAccl > 32767 :
	yAccl -= 65536

zAccl = data[5] * 256 + data[4]
if zAccl > 32767 :
	zAccl -= 65536

# BNO055 address, 0x28(40)
# Read data back from 0x0E(14), 6 bytes
# xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
data = bus.read_i2c_block_data(0x28, 0x0E, 6)

# Convert the data
xMag = data[1] * 256 + data[0]
if xMag > 32767 :
	xMag -= 65536

yMag = data[3] * 256 + data[2]
if yMag > 32767 :
	yMag -= 65536

zMag = data[5] * 256 + data[4]
if zMag > 32767 :
	zMag -= 65536

# BNO055 address, 0x28(40)
# Read data back from 0x14(20), 6 bytes
# xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb	
data = bus.read_i2c_block_data(0x28, 0x14, 6)

# Convert the data
xGyro = data[1] * 256 + data[0]
if xGyro > 32767 :
	xGyro -= 65536

yGyro = data[3] * 256 + data[2]
if yGyro > 32767 :
	yGyro -= 65536

zGyro = data[5] * 256 + data[4]
if zGyro > 32767 :
	zGyro -= 65536
	
# Output data to screen
print "X-Axis of Rotation : %d" %xGyro
print "Y-Axis of Rotation : %d" %yGyro
print "Z-Axis of Rotation : %d" %zGyro
print "Acceleration in X-Axis : %d" % xAccl
print "Acceleration in Y-Axis : %d" % yAccl
print "Acceleration in Z-Axis : %d" % zAccl
print "Magnetic field in X-Axis : %d" %xMag
print "Magnetic field in Y-Axis : %d" %yMag
print "Magnetic field in Z-Axis : %d" %zMag