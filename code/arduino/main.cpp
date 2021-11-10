#include <Arduino.h>
#include "Adafruit_VEML7700.h"
#include "Adafruit_seesaw.h"

Adafruit_VEML7700 veml = Adafruit_VEML7700();
Adafruit_seesaw ss;

void setup()
{
  Serial.begin(9600);
  Serial.println("Adafruit VEML7700 & Soil Sensor Test");

  while (!Serial)
  {
    delay(10);
  } 
  
   /************Initial VEML7700****************/

  if (!veml.begin())
  {
    Serial.println("Sensor not found");
    while(1);
  }
  Serial.println("Sensor found");

  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  Serial.print(F("Gain: "));
  switch (veml.getGain())
  {
    case VEML7700_GAIN_1: Serial.println("1"); break;
    case VEML7700_GAIN_2: Serial.println("2"); break;
    case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
    case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
  }

  Serial.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime())
  {
    case VEML7700_IT_25MS: Serial.println("25"); break;
    case VEML7700_IT_50MS: Serial.println("50"); break;
    case VEML7700_IT_100MS: Serial.println("100"); break;
    case VEML7700_IT_200MS: Serial.println("200"); break;
    case VEML7700_IT_400MS: Serial.println("400"); break;
    case VEML7700_IT_800MS: Serial.println("800"); break;
  }

  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);

  /************Initial Soil Sensor****************/
 
  if (!ss.begin(0x36))
  {
    Serial.println("ERROR! seesaw not found");
    while(1);
  }
  else
  {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop()
{
  /************VEML7700****************/
  Serial.println("Measurement brightness:");
  Serial.print("Lux: "); Serial.println(veml.readLux());
  Serial.print("White: "); Serial.println(veml.readWhite());
  Serial.print("Raw ALS: "); Serial.println(veml.readALS()); //rotes Umgebungslicht
  Serial.println("");

  uint16_t irq = veml.interruptStatus();
  if (irq & VEML7700_INTERRUPT_LOW)
  {
    Serial.println("** Low threshold"); 
  }
  if (irq & VEML7700_INTERRUPT_HIGH)
  {
    Serial.println("** High threshold"); 
  }
  delay(100);

  /************Soil Sensor****************/

  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.println("Measurement soil mositure & temperature:");
  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  Serial.println("");
  delay(3000);
}
