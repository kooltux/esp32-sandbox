/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#if defined(BUILD_BOARD_esp32d1)
#define LED_PIN0 2
#elif defined(BUILD_BOARD_esp32s2)
#define LED_PIN0 15
#elif defined(BUILD_BOARD_esp32c3)
#define LED_PIN0 7
#elif defined(BUILD_BOARD_esp32c3_luatos)
#define LED_PIN0 12
#else
#error "Unknown build environment"
#endif

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(LED_PIN0, OUTPUT);

  Serial.printf("entering main loop...\n");
}

#define DEFAULT_DELAY 1000
double period = DEFAULT_DELAY;

void loop()
{
  Serial.printf("%f\n", period);
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_PIN0, HIGH);
  // wait for a second
  delay((int)period);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_PIN0, LOW);
  // wait for a second
  delay((int)period);

  period /= (1 + period / DEFAULT_DELAY);

  if (period < 20)
    period = DEFAULT_DELAY;
}
