/**
 * Main Arduino code.
 * This whole project is made for the stratospheric balloon project "PROJECT JUMBO"
 * By Samuel Kroiß
 * Contributors: Samuel Kroiß, David Schäffler, Regina Schmid, Benedikt Rosenstetter
 * Copyright (C) 2020.
**/

/*
 * main
 * This file is dedicated for configuring the pins of the Arduino.
*/

#define PIN_ABORT_LOOP 30

/* DS18B20 */
#define PIN_DS18B20 2

/* Dust */
#define PIN_DUST 11

/* UV */
#define PIN_UV A11

/* Gyroskop */
#define PIN_GY_X A8
#define PIN_GY_Y A9
#define PIN_GY_Z A10

/* CJMCU4541 */
#define PIN_CJMCU_PRE 3
#define PIN_CJMCU_NOX A12
#define PIN_CJMCU_RED A13

/* DHT22 */
#define PIN_DHT 4

/* Strommesser */
#define PIN_STROM A14

/* SD */
#define PIN_SD_CHIPSELECT 53

/* Strom */
#define STROM_WIEDERSTAND 0.1

