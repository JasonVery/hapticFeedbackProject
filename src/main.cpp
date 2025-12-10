#include <Arduino.h>
#include <TwaiCan.h>
#include <MKSServoCAN.h>
#include <motorControls.h>

#define ID 1

TwaiCan bus(GPIO_NUM_4, GPIO_NUM_5);

motorControls motor;

void setup()
{

    Serial.begin(115200);

    // Default init from MKSSercoCAN library docs
    while (!Serial)
        ;

    if (!MKSServoCAN::begin(&bus))
    {
        Serial.println("CAN init failed");
        while (1)
            ;
    }

    MKSServoCAN::enableMotor(ID, 0);
    MKSServoCAN::setCanResponse(ID, true, true);
}

void loop()
{

    
}
