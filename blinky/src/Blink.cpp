/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
#define ledPin 23

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(ledPin, OUTPUT);

  Serial.printf("entering main loop...\n");
}

void loop()
{
  Serial.printf(".");
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(ledPin, LOW);
  // wait for a second
  delay(1000);
}
