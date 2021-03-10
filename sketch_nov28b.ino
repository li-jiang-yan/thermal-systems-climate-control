#include <dht11.h>
#include <FastLED.h>
#define LEDPIN 4
#define NUMOFLEDS 9
#define DHT11PIN 2

dht11 DHT11;

int heaterPin = A3;
int val = 0;         // variable to store the read value
int val2 = 0;

CRGB leds[NUMOFLEDS];

void setup()
{
  Serial.begin(9600);

  pinMode(heaterPin, OUTPUT);
  FastLED.addLeds<WS2812, LEDPIN, GRB>(leds, NUMOFLEDS);
 
}

void loop()
{
  Serial.println();

  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.print("Potentiometer voltage (V): ");
  Serial.println(voltage);

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);

  if (DHT11.temperature < 20.25) {
    val2 = 1023.0;
    analogWrite(heaterPin, val2);
    Serial.print("Heating up...");
    } else {
      val2 = 0;
      analogWrite(heaterPin, val2);
      }

  if (voltage < 1) {
    val = 255;
    } else {
      val = 0;
      }

  for (int i = 0; i <= 8; i++) {
    leds[i] = CHSV(0, 0, val);
    }
  FastLED.show();

  if (DHT11.humidity > 55 || DHT11.temperature > 35) {
    analogWrite(A4, 1023.0);
    }


}
