#include <stdio.h>
#include <unistd.h>
#include "veml7700.h"

char* i2cBus = "/dev/apalis-i2c1";

int main(void){
    unsigned char buffer[3];
    veml7700* lightSensor = vemlInit(i2cBus);
    
    vemlWrite(lightSensor, 0x00, 0x00, 0x18);

    buffer[0] = 0x04;

    sleep(1);

    vemlWrite(lightSensor, VEML7700_ALS_CONF_0, 0x00, 0x18);
    
    uint16_t lux = vemlRead(lightSensor, VEML7700_ALS_DATA);

    printf("%f", lux*0.0576);
    
    vemlDestroy(lightSensor);
    
    return 0;
}