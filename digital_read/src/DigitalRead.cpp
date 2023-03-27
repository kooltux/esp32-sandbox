#include <Arduino.h>
#include <driver/adc.h>

#if defined(BUILD_BOARD_esp32d1)
#define D_PIN0 0
#define LED_PIN0 2
#elif defined(BUILD_BOARD_esp32s2)
#define D_PIN0 0
#define LED_PIN0 15
#elif defined(BUILD_BOARD_esp32c3)
#define D_PIN0 0
#define LED_PIN0 7
#elif defined(BUILD_BOARD_esp32c3_luatos)
#define D_PIN0 0
#define LED_PIN0 7
#else
#error "Unknown build environment"
#endif

const int contactPin = D_PIN0;
const int ledPin = LED_PIN0;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  pinMode(contactPin, INPUT);
  if (ledPin >= 0)
    pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Reading potentiometer value
  int contact = digitalRead(contactPin);
  Serial.printf("pot: %d\n", contact);

  if (ledPin >= 0)
  {
    digitalWrite(ledPin, contact ? HIGH : LOW);
  }
  delay(500);
}
