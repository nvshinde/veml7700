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

#define VEML7700_ALS_CONF_0     0x00 ///> ALS configuration register command code
#define VEML7700_ALS_WH         0x01 ///> High threshold window setting command code
#define VEML7700_ALS_WL         0x02 ///> Low threshold window setting command code
#define VEML7700_PWR_SAVE       0x03 ///> Power saving modes command code
#define VEML7700_ALS_DATA       0x04 ///> ALS Data command code
#define VEML7700_WHITE_DATA     0x05 ///> White channel output data command code
#define VEML7700_ALS_INT_DATA   0x06 ///> Interrupt status command code

#define VEML7700_ALS_GAIN_1     0x00 ///> ALS gain x 1
#define VEML7700_ALS_GAIN_2     0x01 ///> ALS gain x 2
#define VEML7700_ALS_GAIN_1_8   0x02 ///> ALS gain x 1/8
#define VEML7700_ALS_GAIN_1_4   0x03 ///> ALS gain x 1/4

#define VEML7700_ALS_IT_25      0x0C ///> ALS IT 25 ms
#define VEML7700_ALS_IT_50      0x08 ///> ALS IT 50 ms
#define VEML7700_ALS_IT_100     0x00 ///> ALS IT 100 ms
#define VEML7700_ALS_IT_200     0x01 ///> ALS IT 200 ms
#define VEML7700_ALS_IT_400     0x02 ///> ALS IT 400 ms
#define VEML7700_ALS_IT_800     0x03 ///> ALS IT 800 ms

#define VEML7700_ALS_PERS_1     0x00 ///> ALS PERS 1
#define VEML7700_ALS_PERS_2     0x01 ///> ALS PERS 2
#define VEML7700_ALS_PERS_4     0x02 ///> ALS PERS 4
#define VEML7700_ALS_PERS_8     0x03 ///> ALS PERS 8

#define VEML7700_ALS_INT_D      0x00 ///> ALS INT disable
#define VEML7700_ALS_INT_E      0x01 ///> ALS INT enable
#define VEML7700_ALS_SD_ON      0x00 ///> ALS power on
#define VEML7700_ALS_SD_OFF     0x01 ///> ALS shut down

#define VEML7700_ALS_WH_VAL     0x0000 ///> High threshold windows setting
#define VEML7700_ALS_WL_VAL     0x0000 ///> Low threshold windows setting

#define VEML7700_PSM_1          0x00 ///> PSM Mode 1
#define VEML7700_PSM_2          0x01 ///> PSM Mode 2
#define VEML7700_PSM_3          0x02 ///> PSM Mode 3
#define VEML7700_PSM_4          0x03 ///> PSM Mode 4

#define VEML7700_PSM_DISABLE    0x00 ///> Disable PSM
#define VEML7700_PSM_ENABLE     0x01 ///> Enable PSM

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

/**
 * @brief Enables the sensor
 * 
 * @param alsDev pointer to struct used to initialise the sensor
 * @return 0 
 */
int veml7700Enable(veml7700* alsDev);

/**
 * @brief Disables the sensor
 * 
 * @param alsDev Pointer to struct used to initialise the sensor
 * @return 0
 */
int veml7700Disable(veml7700* alsDev);

/**
 * @brief Configure the sensor
 * 
 * @param alsDev Pointer to struct used to initialise the sensor
 * @param gain Required ALS gain. e.g. VEML7700_ALS_GAIN_1
 * @param intTime Required integration time e.g. VEML7700_ALS_IT_25
 * @param pers ALS persistence protect number setting e.g. VEML7700_ALS_PERS_1
 * @param intEn ALS interrupt enable setting e.g. VEML7700_ALS_INT_D for disable
 * @return uint16_t. The data sent to the sensor
 */
uint16_t veml7700Config(veml7700* alsDev, unsigned char gain, unsigned char intTime, unsigned char pers, unsigned char intEn); 

/**
 * @brief Not used
 * 
 * @return int 
 */
int veml7700SetGain();

/**
 * @brief Not used
 * 
 * @return int 
 */
int veml7700GetGain();

/**
 * @brief Write the power saving modes for the sensor
 * 
 * @param psmMode e.g. VEML7700_PSM_1
 * @param psmEnable e.g. VEML7700_PSM_ENABLE to enable
 * @return uint16_t. Written word 
 */
uint16_t veml7700SetPSM(unsigned char psmMode, unsigned char psmEnable);

/**
 * @brief Unused
 * 
 * @return uint16_t 
 */
uint16_t veml7700ReadALS();

/**
 * @brief Unused
 * 
 * @return uint16_t 
 */
uint16_t veml7700ReadWhite();

/**
 * @brief Unused
 * 
 * @return uint16_t 
 */
uint16_t veml7700CheckInterrupt();

#endif // __VEML7700_H__