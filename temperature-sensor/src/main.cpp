#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <Update.h>

// For a connection via I2C using the Arduino Wire include:
#include <SSD1306Wire.h>

#include "eeprom_config.h"
#include "web.h"
#include "i2c.h"

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

EEPROM_Config config;

// display message buffer
char message[33];

void displayMessage(const char *msg, SSD1306Wire* d=NULL) {
	if (!d) d=&display;

	d->clear();
	if (strlen(msg) <=10)
    	d->setFont(ArialMT_Plain_24);
    else
		d->setFont(ArialMT_Plain_16);
	d->drawString(0,0,msg);
	d->display();
}

void setup() {
	int n=0;
	const char * waiter="-\\|/";
	
	Serial.begin(115200);

	pinMode(ledPin, OUTPUT);

	ScanI2C();

	// Initialising the UI will init the display too.
	display.init();
	display.flipScreenVertically();

	// retrive config from eeprom
	displayMessage("Configure...");

	// config.set_ssid("xxxxxx");
	// config.set_password("xxxxxx");
	// config.set_hostname("esp32");
	// config.save();

	config.load();

	// Connect to WiFi network
	WiFi.begin(config.ssid(), config.password());
	Serial.printf("Connecting to %s",config.ssid());

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		sprintf(message,"WLAN connect  %c",waiter[(n++)%4]);
		displayMessage(message);
		delay(50);
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(config.ssid());
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	displayMessage("WLAN ok");

	/*use mdns for host name resolution*/
	if (!MDNS.begin(config.hostname())) { //http://esp32.local
		Serial.println("Error setting up MDNS responder!");
		displayMessage("mDNS error");
		while (1) {
		delay(1000);
		}
	}
	Serial.println("mDNS responder started");
	displayMessage("mDNS ok");

	// Start the DS18B20 sensor
	sensor.begin();
	sensor.setResolution(12);
}

unsigned long previousMillis = 0;  // will store last time LED was updated
float temperature = -127.0;
float previousTemp = temperature;
bool temperatureIsValid = false;

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

		// update display
		if (temperatureIsValid) {
			sprintf(message,"%.2f °C %c",temperature,
				(previousTemp<temperature)?'^':((previousTemp>temperature)?'v':'=')
			);
			displayMessage(message);
		}
		else {
			displayMessage("- undef -");
		}

		previousTemp = temperature;
	}

	delay(10);
}

