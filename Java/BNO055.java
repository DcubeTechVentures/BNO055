// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BNO055
// This code is designed to work with the BNO055_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class BNO055
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, BNO055 I2C address is 0x28(40)
		I2CDevice device = bus.getDevice(0x28);
		
		// Select OPR_MODE register
		// Accelerometer, Magnetometer and Gyrometer enabled
		device.write(0x3D, (byte)0x07);
		// Select PWR_MODE register
		// Normal mode
		device.write(0x3E, (byte)0x00);
		// Select PAGE_ID register
		// Shift to Page-1
		device.write(0x07, (byte)0x01);
		// Select ACC_CONFIG register
		// Range = 4G, B/W = 62.5, Normal mode
		device.write(0x08, (byte)0x0C);
		// Select MAG_CONFIG register
		// Data o/p rate = 10 Hz, Regular mode, normal mode
		device.write(0x09, (byte)0x0B);
		// Select GYRO_CONFIG1 register
		// Range = 2000 dps, B/W  = 32 Hz
		device.write(0x0A, (byte)0x38);
		// Select GYRO_CONFIG2 register
		// Normal mode
		device.write(0x0B, (byte)0x00);
		// Select PAGE_ID register
		// Shift to Page-0
		device.write(0x07, (byte)0x00);
		Thread.sleep(500);
		
		// Read 6 bytes of data from address 0x08(08)
		// xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
		byte[] data = new byte[6];
		device.read(0x08, data, 0, 6);
		
		// Convert the data
		int xAccl = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xAccl > 32767)
		{
			xAccl -= 65536;
		}	
		
		int yAccl = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yAccl > 32767)
		{
			yAccl -= 65536;
		}
		
		int zAccl = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zAccl > 32767)
		{
			zAccl -= 65536;
		}
		
		// Read 6 bytes of data from address 0x0E(14)
		// xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
		device.read(0x0E, data, 0, 6);
		
		// Convert the data
		int xMag = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF));
		if(xMag > 32767)
		{
			xMag -= 65536;
		}	

		int yMag = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yMag > 32767)
		{
			yMag -= 65536;
		}

		int zMag = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zMag > 32767)
		{
			zMag -= 65536;
		}
		
		// Read 6 bytes of data from address 0x14(20)
		// xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
		device.read(0x14, data, 0, 6);
		
		// Convert the data
		int xGyro = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xGyro > 32767)
		{
			xGyro -= 65536;
		}
		
		int yGyro = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yGyro > 32767)
		{
			yGyro -= 65536;
		}
		
		int zGyro = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zGyro > 32767)
		{
			zGyro -= 65536;
		}
		
		// Output data to screen
		System.out.printf("X-axis Of Rotation : %d %n", xGyro);
		System.out.printf("Y-axis Of Rotation : %d %n", yGyro);
		System.out.printf("Z-axis Of Rotation : %d %n", zGyro);
		System.out.printf("Acceleration in X-Axis : %d %n", xAccl);
		System.out.printf("Acceleration in Y-Axis : %d %n", yAccl);
		System.out.printf("Acceleration in Z-Axis : %d %n", zAccl);
		System.out.printf("Magnetic field in X-Axis : %d %n", xMag);
		System.out.printf("Magnetic field in Y-Axis : %d %n", yMag);
		System.out.printf("Magnetic field in Z-Axis : %d %n", zMag);			
	}	
}