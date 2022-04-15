/**
 * @file veml7700.h
 * @author Nikhil Shinde
 * @brief Function prototypes for VEML7700 driver
 * 
 * This file contains the function prototypes for VEML7700 
 * ambient light sensor. This also has macros, global variables or 
 * required constants.
 * 
 * @ref name "text"
 * @version 0.1
 * @date 2022-04-14
 * @bug No known bugs
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __VEML7700_H__
#define __VEML7700_H__

#include <stdint.h>

#define VEML7700_ADDR           0x10

/**
 * @brief Macros for command code of command registers
 */
#define VEML7700_ALS_CONF_0     0x00
#define VEML7700_ALS_WH         0x01
#define VEML7700_ALS_WL         0x02
#define VEML7700_PWR_SAVE       0x03
#define VEML7700_ALS_DATA       0x04
#define VEML7700_WHITE_DATA     0x05
#define VEML7700_ALS_INT_DATA   0x06

/**
 * @brief Macros for ALS Configuration register
 */
#define VEML7700_ALS_GAIN_1     0x00 // ALS gain x 1
#define VEML7700_ALS_GAIN_2     0x01 // ALS gain x 2
#define VEML7700_ALS_GAIN_1_8   0x02 // ALS gain x 1/8
#define VEML7700_ALS_GAIN_1_4   0x03 // ALS gain x 1/4

#define VEML7700_ALS_IT_25      0x0C // ALS IT 25 ms
#define VEML7700_ALS_IT_50      0x08 // ALS IT 50 ms
#define VEML7700_ALS_IT_100     0x00 // ALS IT 100 ms
#define VEML7700_ALS_IT_200     0x01 // ALS IT 200 ms
#define VEML7700_ALS_IT_400     0x02 // ALS IT 400 ms
#define VEML7700_ALS_IT_800     0x03 // ALS IT 800 ms

#define VEML7700_ALS_PERS_1     0x00 // ALS PERS 1
#define VEML7700_ALS_PERS_2     0x01 // ALS PERS 2
#define VEML7700_ALS_PERS_4     0x02 // ALS PERS 4
#define VEML7700_ALS_PERS_8     0x03 // ALS PERS 8

#define VEML7700_ALS_INT_D      0x00 // ALS INT disable
#define VEML7700_ALS_INT_E      0x01 // ALS INT enable
#define VEML7700_ALS_SD_ON      0x00 // ALS power on
#define VEML7700_ALS_SD_OFF     0x01 // ALS shut down

/**
 * @brief High, low threshold windows setting. Not used
 */
#define VEML7700_ALS_WH_VAL     0x0000 // High threshold windows setting
#define VEML7700_ALS_WL_VAL     0x0000 // Low threshold windows setting

/**
 * @brief Power saving modes, enable setting
 */
#define VEML7700_PSM_1          0x00 // Mode 1
#define VEML7700_PSM_2          0x01 // Mode 2
#define VEML7700_PSM_3          0x02 // Mode 3
#define VEML7700_PSM_4          0x03 // Mode 4

#define VEML7700_PSM_DISABLE    0x00 // Disable PSM
#define VEML7700_PSM_ENABLE     0x01 // Enable PSM

/**
 * @brief Struct containing sensor's fd and address
 */
typedef struct veml7700{
    int fd;
    unsigned char addr;
}veml7700;

/**
 * @brief Initialise the sensor.
 * 
 * Returns a pointer to a struct about the sensor's fd and address
 * 
 * @param busname pointer to i2c bus name on which sensor is mapped. e.g. "/dev/apalis-i2c1"
 * @return veml7700* 
 */
veml7700* vemlInit(char* busname);

/**
 * @brief Destroy the sensor struct and close the fd.
 * 
 * @param alsDev pointer to struct used to initialise the sensor
 * @return 0
 */
int vemlDestroy(veml7700* alsDev);

/**
 * @brief Write data to the sensor. Sets appropriate errno on error.
 * 
 * @param alsDev pointer to struct used to initialise the sensor
 * @param commandCode command to write to the sensor. e.g. 0x00
 * @param LSB LSB of data to be written to sensor
 * @param MSB MSB of data to be written to sensor
 * @return 0 on success, -1 on error.  
 */
int vemlWrite(veml7700* alsDev, unsigned char commandCode, unsigned char LSB, unsigned char MSB);

/**
 * @brief 
 * 
 * @param alsDev pointer to struct used to initialise the sensor
 * @param commandCode command to write to sensor. e.g. 0x04
 * @return a uint16_t integer of received data from sensor 
 */
uint16_t vemlRead(veml7700* alsDev, unsigned char commandCode);

int veml7700Enable(int enable);

int veml7700Disable(int disable);

int veml7700SetGain();

int veml7700GetGain();

int veml7700SetPSM();

uint16_t veml7700ReadALS();

uint16_t veml7700ReadWhite();

uint16_t veml7700CheckInterrupt();

#endif // __VEML7700_H__