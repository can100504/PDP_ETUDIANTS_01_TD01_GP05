// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13 
#define DHTTYPE    DHT11   

#define uS_TO_S_FACTOR 1000000  
#define TIME_TO_SLEEP 5    
RTC_DATA_ATTR int bootCount = 0;    

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if(bootCount == 0) 
  {  
    bootCount = bootCount+1;  
  }else  
  {  
     if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }
  }        
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);  
  esp_deep_sleep_start(); 
}

void loop() {
}