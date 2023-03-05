/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
//#define ledPin 7  // C3
#define ledPin 15 // S2

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(ledPin, OUTPUT);

  Serial.printf("entering main loop...\n");
}

#define DEFAULT_DELAY 1000
double period = DEFAULT_DELAY;

void loop()
{
  Serial.printf("%f\n", period);
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin, HIGH);
  // wait for a second
  delay((int)period);
  // turn the LED off by making the voltage LOW
  digitalWrite(ledPin, LOW);
  // wait for a second
  delay((int)period);

  period /= (1 + period / DEFAULT_DELAY);

  if (period < 20)
    period = DEFAULT_DELAY;
}
