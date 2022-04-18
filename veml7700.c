/**
 * @file veml7700.c
 * @author Nikhil Shinde
 * @brief Userspace library for VEML7700 ambient light sensor
 * 
 * https://www.kernel.org/doc/html/latest/i2c/dev-interface.html
 * @version 0.1
 * @date 2022-04-14
 * @bug No known bugs
 * @copyright Copyright (c) 2022
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "veml7700.h"

veml7700* vemlInit(char* busname){
    veml7700* newSensor = (veml7700*)malloc(sizeof(veml7700));
    if(newSensor == NULL){
        perror("[Init Error]: ");
        exit(1);
    }
    if((newSensor->fd = open(busname, O_RDWR)) < 0){
        perror("[Init Error]: ");
        exit(1);
    } 
    newSensor->addr = VEML7700_ADDR;

    return newSensor;
}

int vemlDestroy(veml7700* alsDev){
    close(alsDev->fd);
    free(alsDev);

    return 0;
}

int vemlWrite(veml7700* alsDev, unsigned char commandCode, unsigned char LSB, unsigned char MSB){
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    unsigned char data[] = {commandCode, LSB, MSB};

    msgs[0].addr = alsDev->addr;
    msgs[0].flags = 0;
    msgs[0].len = 3;
    msgs[0].buf = data;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if(ioctl(alsDev->fd, I2C_RDWR, &msgset) < 0){
        perror("[Write Error]: ");
        return -1;
    }    
    return 0;
}

uint16_t vemlRead(veml7700* alsDev, unsigned char commandCode){
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    unsigned char out[] = {commandCode};
    unsigned char data[2];

    msgs[0].addr = alsDev->addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = out;

    msgs[1].addr = alsDev->addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = 2;
    msgs[1].buf = data;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 2;

    if(ioctl(alsDev->fd, I2C_RDWR, &msgset) < 0){
        perror("[Read Error]: ");
        return -1;
    }
   // unsigned char init[3][3] = {
    //                 {0x00, 0x00, 0x18},
    //                 {0x01, 0x00, 0x00},
    //                 {0x02, 0x00, 0x00}
    // };

    // int i;
    // for(i=0; i<3; i++){
    //     vemlWrite(newSensor, init[i], 2);
    // }

    return data[1]*256 + data[0];
};

int veml7700Enable(veml7700* alsDev){
    vemlWrite(alsDev, VEML7700_ALS_CONF_0, VEML7700_ALS_SD_ON, 0x00);
    usleep(5*1000); // Sleep 5ms
    
    return 0;
}

int veml7700Disable(veml7700* alsDev){
    vemlWrite(alsDev, VEML7700_ALS_CONF_0, VEML7700_ALS_SD_OFF, 0x00);

    return 0;
}

uint16_t veml7700Config(veml7700* alsDev, unsigned char gain, unsigned char intTime, unsigned char pers, unsigned char intEn){
    uint16_t word;
    uint8_t lsb, msb;

    word = 0x0000 | (gain << 11) | (intTime << 6) | (pers << 4) | (intEn << 1);
    lsb = word & 0xFF;
    msb = word >> 8;
    vemlWrite(alsDev, VEML7700_ALS_CONF_0, lsb, msb);

    return word;
}

__uint16_t veml7700SetPSM(unsigned char psmMode, unsigned char psmEnable){
    uint16_t word = 0x0000;

    word = word | (psmMode << 1);
    word = word | psmEnable;

    return word;
}

/**
// can be done directly

uint16_t veml7700ReadALS(){
    
}

uint16_t veml7700ReadWhite(){

}

uint16_t veml7700CheckInterrupt(){

}
**/