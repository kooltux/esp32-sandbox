#include <Arduino.h>
#include <driver/adc.h>

#if defined(BUILD_BOARD_esp32d1)
#define ADC_PIN0 36
#define LED_PIN0 2
#elif defined(BUILD_BOARD_esp32s2)
#define ADC_PIN0 3
#define LED_PIN0 15 // 15
#elif defined(BUILD_BOARD_esp32c3)
#define ADC_PIN0 0
#define LED_PIN0 7 // 7
#elif defined(BUILD_BOARD_esp32c3_luatos)
#define ADC_PIN0 0
#define LED_PIN0 7 // 7
#else
#error "Unknown build environment"
#endif

const int potPin = ADC_PIN0;
const int ledPin = LED_PIN0;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  pinMode(potPin, INPUT);
  if (ledPin >= 0)
    pinMode(ledPin, OUTPUT);

  analogSetPinAttenuation(potPin, ADC_11db);
}

int curstate = -1;

void updateState(int val)
{
  if ((val < 1024) && (curstate != 0))
  {
    if (ledPin >= 0)
      digitalWrite(ledPin, HIGH);
    curstate = 0;
    Serial.println("Threshold 1->0 detected");
  }

  if ((val >= 1024) && (curstate != 1))
  {
    if (ledPin >= 0)
      digitalWrite(ledPin, LOW);
    curstate = 1;
    Serial.println("Threshold 0->1 detected");
  }
}

void loop()
{
  // Reading potentiometer value
  int potValue = analogRead(potPin);
  Serial.printf("pot: %d\n", potValue);

  updateState(potValue);

  delay(500);
}
