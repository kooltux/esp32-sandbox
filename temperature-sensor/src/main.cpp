#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// For a connection via I2C using the Arduino Wire include:
#include <SSD1306Wire.h>

// Initialize the OLED display using Arduino Wire:
// SDA: 21
// SCL: 22
#define DISPLAY_ADDR 0x3c
SSD1306Wire display(DISPLAY_ADDR, SDA, SCL, GEOMETRY_128_32);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

// ESP32 Pin to which onboard LED is connected
#define ledPin 23 // ESP32 GPIO 23

// GPIO where the DS18B20 is connected to
#define ONE_WIRE_BUS 4 // D4

// interval at which to read temp sensor
const long tempInterval = 5000;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Start the DS18B20 sensor
  sensor.begin();
  sensor.setResolution(12);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

unsigned long previousMillis = 0;  // will store last time LED was updated
float temperature = -127.0;
bool temperatureIsValid = false;
char message[33];

void loop() {

	//loop to blink without delay
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= tempInterval) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		digitalWrite(ledPin, HIGH);
		sensor.requestTemperatures();
		temperature = sensor.getTempCByIndex(0);
		digitalWrite(ledPin, LOW);

		// check if temp is valid
		temperatureIsValid = (temperature != -127.0);

		Serial.printf("Temperature: %f ºC\n", temperature);
		Serial.printf("I2C Display: %x %d %d\n",DISPLAY_ADDR,SDA,SCL);

		// update display
		display.clear();
		display.setFont(ArialMT_Plain_24);
		if (temperatureIsValid) {
			sprintf(message,"%.2f °C",temperature);
			display.drawString(0, 0, message);
		}
		else {
			display.drawString(0, 0, "- undef -");
		}
		display.display();
	}

	delay(0.1);

}

