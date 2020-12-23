/**
 * Main Arduino code.
 * This whole project is made for the stratospheric balloon project "PROJECT JUMBO"
 * By Samuel Kroiß & David Schäffler 
 * Contributors: Samuel Kroiß, David Schäffler, Regina Schmid, Benedikt Rosenstetter
 * Date: 29.11.2020
**/

/*
 * ALL PINS:m
 * 
 * Digital
 * 30: SensorTemperature - Data
 * 33: SensorHumidityTemperature - Power Reset
 * 34: SensorHumidityTemperature - Data
 * 38: SensorGas - Preheat
 * 42: SensorDust - Data
 * 46: RemoteBeeper - Speaker
 * 50: SDController - MISO
 * 51: SDController - MOSI
 * 52: SDController - SCK
 * 53: SDController - CS
 * 
 * Analog
 * A6: SensorGas - Red
 * A7: SensorGas - Nox
 * A8: SensorGyroscope - X
 * A9: SensorGyroscope - Y
 * A10: SensorGyroscope- Z
 * A15: SensorUV - UV
 * 
 * Communication:
 * 20 (SDA): Timer - SDA
 * 21 (SCL): Timer - SCL
 */
