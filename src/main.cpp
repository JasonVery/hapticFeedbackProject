#include <Arduino.h>
#include <TwaiCan.h>
#include <MKSServoCAN.h>

#define MOTOR_ID 1

TwaiCan bus(GPIO_NUM_4, GPIO_NUM_5);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    if (!MKSServoCAN::begin(&bus))
    {
        Serial.println("CAN init failed");
        while (1)
            ;
    }

    MKSServoCAN::queryStatus(MOTOR_ID);
    MKSServoCAN::speedMode(MOTOR_ID, 50, 50, 0);
}

void loop()
{
    MKSServoCAN::pollResponses();
    delay(100);
}
