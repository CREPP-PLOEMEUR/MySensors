/*
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 * ........................
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
 * Version 1.2 : Régis PIDOUX
 * Version 1.3 : Nicolas LE GUERROUE (2021, 13th of may)
 * 
 * DESCRIPTION
 * This sketch provides an example of how to implement a humidity/temperature
 * sensor using a DHT11/DHT-22.
 *  
 * For more information, please visit:
 * http://www.mysensors.org/build/humidity
 * 
 */


/*!
 * ************************************************************
 * PARAMETRES NRF24
 * ************************************************************
 */
//Mode debug activé
#define MY_DEBUG

// Enable and select radio type attached 
#define MY_RADIO_RF24

#ifndef MY_RF24_PA_LEVEL
#define MY_RF24_PA_LEVEL     RF24_PA_MAX
#endif

#ifndef MY_RF24_CHANNEL
#define MY_RF24_CHANNEL    86
#endif

#ifndef MY_RF24_DATARATE
#define MY_RF24_DATARATE RF24_250KBPS
#endif


/*!
 * ************************************************************
 * PARAMETRES DOMOTICZ
 * ************************************************************
 */
#define MY_NODE_ID 30         //Noeud dans Domoticz

//Valeurs entre 1 et 254
#define CHILD_ID_BATT 31      //Identifiant Domoticz pour le niveau de batterie
#define CHILD_ID_TEMP 32      //Identifiant Domoticz pour la température
#define CHILD_ID_HUM 33       //Identifiant Domoticz pour l'humidité

//Temps entre deux envois de données
static const uint64_t UPDATE_INTERVAL = 10000;   

//Nombre au bout duquel la sonde envoie les données même si elles n'ont pas changés
static const uint8_t FORCE_UPDATE_N_READS = 10;


 /*!
  * ************************************************************
  * INCLUSIONS DES BIBLIOTHEQUES
  * ************************************************************
  */

#include <MyConfig.h>
#include <MySensors.h>  
#include <SPI.h>
#include <DHT.h>


/*!
 * ************************************************************
 * BATTERIE
 * ************************************************************
 */
//Partie pour mesure Batterie
int BATTERY_SENSE_PIN = A0;

float oldBatteryV = 0;//Sauvegarde du niveau de batterie

const float r1_value = 1000000.0; //Valeur de la résistance la plus proche de l'alimentation de la batterie
const float r2_value = 330000.0; //Valeur de la résistance la plus proche de la masse


/*!
 * ************************************************************
 * DHT22/DHT11
 * ************************************************************
 */
//Broche de données du DHT22 (ou DHT11)
#define DHT_DATA_PIN 3

#define DHT_TYPE DHT22 //use DHT11 or DHT22

//définir une valeur si le capteur à un offset permanent par rapport à la température réelle
#define SENSOR_TEMP_OFFSET 0

float lastTemp;   //Dernière valeur de température lue
float lastHum;    //dernière valeur d'humidité lue


bool metric = true;
float batteryV;

/*!
 * ************************************************************
 * INSTANCES et OBJETS
 * ************************************************************
 */

//Création d'un message pour un capteur d'humidité
MyMessage msgHum(CHILD_ID_HUM, V_HUM);
//Création d'un message pour un capteur de température
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
//Création d'un message pour un multimètre
MyMessage msgBatt(CHILD_ID_BATT, V_VOLTAGE);

//Capteur DHT
DHT dht(DHT_DATA_PIN,DHT_TYPE);


void presentation()  
{ 
  
  sendSketchInfo("GATEWAY_USER", "1.0");
  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
  present(CHILD_ID_BATT,  S_MULTIMETER);
  
  //metric = getControllerConfig().isMetric;
  
}//Fin presentation


void setup()
{

  //Référence de tension interne
#if defined(__AVR_ATmega2560__)
  analogReference(INTERNAL1V1);
#else
  analogReference(DEFAULT);   // ref 3.3v au lieu de INTERNAL pour 1.1v
#endif


  Serial.begin(9600);
  dht.begin();
  
}//End setup


void loop()       {
  
  
  //Batterie
  int sensorValue = analogRead(BATTERY_SENSE_PIN); //Valeur lue en sortie du Convertisseur Analogique Numérique 10 bits (résolution de 5mV)
  batteryV = (1.0/(r2_value/(r1_value+r2_value)))*float(sensorValue)*(3.3/1023.0);
 
#ifdef MY_DEBUG
  Serial.print("Tension batterie = ");
  Serial.print(batteryV);
  Serial.println(" V");
  
#endif
  
  //DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  
#ifdef MY_DEBUG
  //Si impossible de lire le DHT
  if (isnan(h) || isnan(t)) {
    Serial.print("Impossible de lire les données du DHT sur la broche");
    Serial.print(DHT_DATA_PIN);
    Serial.println(" de l'Arduino");
  }//Fin if

  Serial.print("Humidité : ");
  Serial.println(h);
  Serial.print("Temperature : ");
  Serial.println(t);
  
#endif

  //ENVOI DES DONNEES

  send(msgBatt.set(batteryV, 38));        //  envoi tension batterie
  send(msgHum.set(h, 38));                //  envoi humidité
  send(msgTemp.set(t, 38));               //  envoi température

  sleep(UPDATE_INTERVAL);                 //Attente
}
