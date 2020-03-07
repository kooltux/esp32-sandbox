#include "i2c.h"

#include <Wire.h>
#include "log.h"

void scanI2C() {
	Wire.begin(SDA,SCL);
	byte error, address;
	int nDevices=0;

    Log.info("I2C Scanning...");
	for(address = 1; address < 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if (error == 0) {
			Log.info("I2C device found at 0x%02x",address);
			nDevices++;
		}
		else if (error==4) {
			Log.info("Unknow I2C error at address 0x%02x",address);
		}    
	}
	if (nDevices == 0) {
		Log.info("No I2C devices found");
	}
	else {
        Log.info("I2C scanning done");
	}
}
