/*
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0: Henrik EKblad
 * Version 1.1 - 2016-07-20: Converted to MySensors v2.0 and added various improvements - Torben Woltjen (mozzbozz)
 * 
 * DESCRIPTION
 * This sketch provides an example of how to implement a humidity/temperature
 * sensor using a DHT11/DHT-22.
 *  
 * For more information, please visit:
 * http://www.mysensors.org/build/humidity
 * 
 */

// Maj Rpx 2018 03 08    / 2020 5 9 UPDATE_INTERVAL & updint  Version test Florian
// Enable debug prints
//#define MY_DEBUG

// Enable and select radio type attached 
#define MY_RADIO_RF24
//#define MY_RADIO_RFM69
//#define MY_RS485
// Set LOW transmit power level as default, if you have an amplified NRF-module and
// power your radio separately with a good regulator you can turn up PA level.
//#define MY_RF24_PA_LEVEL RF24_PA_MAX       // Par défaut dans MyConfig.h
// PA levels
//#define RF24_PA_MIN   (0) -18dB
//#define RF24_PA_LOW   (1) -12dB
//#define RF24_PA_HIGH  (2) -6dB
//#define RF24_PA_MAX   (3)  0dB
//#define MY_RF24_DATARATE RF24_250KBPS      // Par défaut dans MyConfig.h
// data rate
//#define RF24_1MBPS     (0)
//#define RF24_2MBPS    (1)
//#define RF24_250KBPS  (2)
// Le canal par défaut est 76 passé à 98  dans MyConfig.h
#ifndef MY_RF24_PA_LEVEL
#define MY_RF24_PA_LEVEL     RF24_PA_MAX
#endif

#ifndef MY_RF24_CHANNEL
//#define MY_RF24_CHANNEL    107
#define MY_RF24_CHANNEL    90        //Modifié  4/2018 canal 106 pour gateway w5100 ip 185
#endif

//
// version 2020 5 9     RdC USB 94    SSol Eth185  90    Etage  Eth186  98
//
#ifndef MY_RF24_DATARATE
#define MY_RF24_DATARATE RF24_250KBPS   //Valeur par défaut conservée
#endif





#define MY_NODE_ID 1         // numéro du noeud premier noeud de Florian


// Partie pour mesure Batterie
int BATTERY_SENSE_PIN = A0;  // select the input pin for the battery sense point

//unsigned long SLEEP_TIME = 900000;  // sleep time between reads (seconds * 1000 milliseconds) pas utile on utilise celui du DHT
float oldBatteryV = 0;

#include <MyConfig.h>
// Partie pour DHT
#include <SPI.h>
#include <MySensors.h>  
#include <DHT.h>

// Set this to the pin you connected the DHT's data pin to
#define DHT_DATA_PIN 3

// Set this offset if the sensor has a permanent small offset to the real temperatures
#define SENSOR_TEMP_OFFSET 0

// Sleep time between sensor updates (in milliseconds)
// Must be >1000ms for DHT22 and >2000ms for DHT11
static const uint64_t UPDATE_INTERVAL = 15000;   // passé à 30 sec fois 2 dans sleep
//static const uint64_t UPDATE_INTERVAL = 5000;

// Force sending an update of the temperature after n sensor reads, so a controller showing the
// timestamp of the last update doesn't show something like 3 hours in the unlikely case, that
// the value didn't change since;
// i.e. the sensor would force sending an update every UPDATE_INTERVAL*FORCE_UPDATE_N_READS [ms]
static const uint8_t FORCE_UPDATE_N_READS = 10;

#define CHILD_ID_HUM 0
#define CHILD_ID_TEMP 1
#define CHILD_ID_BATT 20

float lastTemp;
float lastHum;
uint8_t nNoUpdatesTemp;
uint8_t nNoUpdatesHum;
int nNoUpdatesVolt = 16;
bool metric = true;
float batteryV;
//float oldBatteryV;
float vr1; float vr2; float vcoeffbatt;
float updint;


MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
MyMessage msgBatt(CHILD_ID_BATT, V_VOLTAGE);

DHT dht(10,DHT22);


void presentation()  
{ 
//Pour mesure batterie
  // Send the sketch version information to the gateway and Controller
 // sendSketchInfo("Battery Meter", "1.0");
// Pour DHT
  // Send the sketch version information to the gateway
  sendSketchInfo("Temperature Humidity & Batterie", "1.1");
  
  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
  present(CHILD_ID_BATT,  S_MULTIMETER);
  
  metric = getControllerConfig().isMetric;
}


void setup()
//Pour mesure batterie
{
// use the 1.1 V internal reference
#if defined(__AVR_ATmega2560__)
  analogReference(INTERNAL1V1);
#else
  analogReference(DEFAULT);   // ref 3.3v au lieu de INTERNAL pour 1.1v
#endif
 // 1M, 470K divider across battery and using internal ADC ref of 1.1V
  // Sense point is bypassed with 0.1 uF cap to reduce noise at that point
  // ((1e6+470e3)/470e3)*1.1 = Vmax = 3.44 Volts // ((1e6+330e3)/330e3)*1.1 = Vmax = 4,433333333 Volts
  // 3.44/1023 = Volts per bit = 0.003363075
  // 4.44/1023 = Volts per bit = 0,004329427  
//float vr1; float vr2; float vcoeffbatt;
     if ( MY_NODE_ID == 1) {
  vr1 = 987300; vr2 = 994000;
     }
    if ( MY_NODE_ID == 2) {
  vr1 = 994000; vr2 = 325000;
     }
    if ( MY_NODE_ID == 3) {
  vr1 = 990000; vr2 = 333000;
     }
    if ( MY_NODE_ID == 4) {
  vr1 = 1032000; vr2 = 329000;
     }
     if ( MY_NODE_ID == 6) {
  vr1 = 1002000; vr2 = 325100;
     }
    if ( MY_NODE_ID == 7) {
  vr1 = 993500; vr2 = 329000;
     }
    if ( MY_NODE_ID == 8) {
  vr1 = 988200; vr2 = 327200;
     }
    if ( MY_NODE_ID == 9) {
  vr1 = 1006100; vr2 = 325300;
     }
  vcoeffbatt = ((vr1+vr2)/vr2)/1023*3.3 ;


// Pour DHT

 // dht.setup(DHT_DATA_PIN); // set data pin of DHT sensor
 /* if (UPDATE_INTERVAL <= dht.getMinimumSamplingPeriod()) {
#ifdef MY_DEBUG
    Serial.println("Warning: UPDATE_INTERVAL is smaller than supported by the sensor!");
#endif
  }*/
  // Sleep for the time of the minimum sampling period to give the sensor time to power up
  // (otherwise, timeout errors might occure for the first reading)
  //sleep(dht.getMinimumSamplingPeriod());
}


void loop()      
//Pour mesure batterie
{
  // get the battery Voltage
  int sensorValue = analogRead(BATTERY_SENSE_PIN);
#ifdef MY_DEBUG
  Serial.println(sensorValue);
#endif

  // 1M, 470K divider across battery and using internal ADC ref of 1.1V
  // Sense point is bypassed with 0.1 uF cap to reduce noise at that point
  // ((1e6+470e3)/470e3)*1.1 = Vmax = 3.44 Volts // ((1e6+330e3)/330e3)*1.1 = Vmax = 4,433333333 Volts
  // 3.44/1023 = Volts per bit = 0.003363075
  // 4.44/1023 = Volts per bit = 0,004329427  

  //int batteryPcnt = sensorValue / 10;
    float batteryV  = sensorValue * vcoeffbatt ;      //      0.004329427 ;     // 0.003363075;

#ifdef MY_DEBUG
  Serial.print("Battery Voltage: ");
  Serial.print(batteryV);
  Serial.println(" V");

 // Serial.print("Battery percent: ");
 // Serial.print(batteryPcnt);
 // Serial.println(" %");
#endif

  if (batteryV != oldBatteryV  || nNoUpdatesVolt > 15) {
    // Power up radio after sleep si  la tension change ou si aucun envoi en 15 lectures
   send(msgBatt.set(batteryV, 38));       //  envoi batt V      

  // sendBatteryLevel(batteryV);                      //  envoi batt V
  // sendBatteryLevel(batteryPcnt);                      //  envoi batt%
  //  oldBatteryPcnt = batteryPcnt;
    oldBatteryV = batteryV;
    nNoUpdatesVolt = 0;                // raz du compteur
  }
 else {
 ++nNoUpdatesVolt ;         // incremente le compteur 
 }


//Pour DHT
  
  // Force reading sensor, so it works also after sleep()
  dht.read(true);
  
  // Get temperature from DHT library
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed reading temperature from DHT!");
  } else if (temperature != lastTemp || nNoUpdatesTemp == FORCE_UPDATE_N_READS) {
    // Only send temperature if it changed since the last measurement or if we didn't send an update for n times
    lastTemp = temperature;
    if (!metric) {
      temperature = dht.readTemperature();
    }
    // Reset no updates counter
    nNoUpdatesTemp = 0;
    temperature += SENSOR_TEMP_OFFSET;
    send(msgTemp.set(temperature, 1));        // envoi temp avec 1 !!!

    #ifdef MY_DEBUG
    Serial.print("T: ");
    Serial.println(temperature);
    #endif
  } else {
    // Increase no update counter if the temperature stayed the same
    ++nNoUpdatesTemp;
  }

  // Get humidity from DHT library
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed reading humidity from DHT");
  } else if (humidity != lastHum || nNoUpdatesHum == FORCE_UPDATE_N_READS) {
    // Only send humidity if it changed since the last measurement or if we didn't send an update for n times
    lastHum = humidity;
    // Reset no updates counter
    nNoUpdatesHum = 0;
    send(msgHum.set(humidity, 1));         // envoi hum
    
    #ifdef MY_DEBUG
    Serial.print("H: ");
    Serial.println(humidity);
    #endif
  } else {
    // Increase no update counter if the humidity stayed the same
    nNoUpdatesHum++;
  }

  // Sleep for a while to save energy
   updint = UPDATE_INTERVAL*2;
  sleep(updint); 
}
