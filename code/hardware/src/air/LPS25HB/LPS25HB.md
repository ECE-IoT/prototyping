# Air-Pressure Sensor - LPS25HB

## LPS25HB
- 3,3 to 5V power and I/O
- Range: 260-1260 hPa
- Accuracy: 0.2 hPa after calibration
            +-1 hPa before calibration
- maximum Sampling Rate: 25Hz
- Body size: 25mm X 25mm X 7,6mm
- Form Faktor: STEMMA QT / Qwiic
- Current Consumption: High resolution mode: 25µA
                      low power mode: 4µA
- Communication Interface: I2C, SPI
> More information can be found [here](https://www.adafruit.com/product/4530)
>or [here] (https://learn.adafruit.com/adafruit-lps25-pressure-sensor)


## Libraries
- Adafruit LPS2X Library
- Adafruit BusIO Library
- Adafruit Unified Sensor Library

## Implementation
// Basic demo for pressure readings from Adafruit LPS2X
#include <Wire.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>

// For SPI mode, we need a CS pin
#define LPS_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LPS_SCK 13
#define LPS_MISO 12
#define LPS_MOSI 11

Adafruit_LPS25 lps;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit LPS25 test!");

  // Try to initialize!
  if (!lps.begin_I2C()) {
  //if (!lps.begin_SPI(LPS_CS)) {
  //if (!lps.begin_SPI(LPS_CS, LPS_SCK, LPS_MISO, LPS_MOSI)) {
    Serial.println("Failed to find LPS25 chip");
    while (1) { delay(10); }
  }
  Serial.println("LPS25 Found!");

//  lps.setDataRate(LPS25_RATE_12_5_HZ);
  Serial.print("Data rate set to: ");
  switch (lps.getDataRate()) {
    case LPS25_RATE_ONE_SHOT: Serial.println("One Shot"); break;
    case LPS25_RATE_1_HZ: Serial.println("1 Hz"); break;
    case LPS25_RATE_7_HZ: Serial.println("7 Hz"); break;
    case LPS25_RATE_12_5_HZ: Serial.println("12.5 Hz"); break;
    case LPS25_RATE_25_HZ: Serial.println("25 Hz"); break;

  }
}

void loop() {
  sensors_event_t temp;
  sensors_event_t pressure;
  lps.getEvent(&pressure, &temp);// get pressure
  Serial.print("Temperature: ");Serial.print(temp.temperature);Serial.println(" degrees C");
  Serial.print("Pressure: ");Serial.print(pressure.pressure);Serial.println(" hPa");
  Serial.println("");
  delay(100);
}