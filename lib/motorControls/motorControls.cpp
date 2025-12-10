#include "motorControls.h"
#include "Arduino.h"
#include "MKSServoCAN.h"

void motorControls::initHapticMode(uint32_t id)
{

    // defined in mA
    const int workCurrent = 1200;
    // defined as percentage of workCurrent. 0 = ~10-20% of workCurrent
    const int holdCurrent = 0;

    // Mode 4 = serialInterface_Close
    // This allows for communicate through CAN as well as access to encoder data
    MKSServoCAN::setWorkMode(id, 4);
    MKSServoCAN::pollResponses();

    // sets both work and holding current
    MKSServoCAN::setCurrent(id, workCurrent);
    MKSServoCAN::setHoldCurrent(id, holdCurrent);
    MKSServoCAN::pollResponses();

    // soft restart for motor driver
    MKSServoCAN::restart(id);
    MKSServoCAN::pollResponses();
    delay(10000);

    Serial.println("Initialization Complete");

    // For best results, I recommend disconnecting and reconnecting circut from
    // from power for a few seconds as it can be stubborn to change work modes.
}



float motorControls::zeroAngle(uint32_t id)
{
    // Stores the raw angle comming from encoder
    float rawAngle;

    // Angle after shifting based on our chosen zero point
    float currAngle;

    // Stores the previous angle reading so we can see how much the motor moved
    static float lastAngle = 0.0f;

    // How much the angle changed since the last loop
    float delta;

    // Our final usable angle that is returned -> goes from -360 to +360
    static float signedAngle = 0.0f;

    MKSServoCAN::readEncoderCarry(id);
    MKSServoCAN::pollResponses();

    // This function does not come with the library. I added it directly to the SRC
    // It is just a helper function to return the angle found in CAN message 0x30
    rawAngle = MKSServoCAN::getAngleDeg();

    // On boot or when we swtich haptic modes, what ever the encoder reads becomes are intial zero angle
    if (!isZeroAngleInit)
    {
        zeroedAngle = rawAngle;
        isZeroAngleInit = true;
        lastAngle = 0.0f;
        signedAngle = 0.0f;
    }

    // Shift raw angle so our chosen zero point becomes real 0
    currAngle = rawAngle - zeroedAngle;

    // Keep currAngle inside 0–360 range
    while (currAngle < 0)
        currAngle += 360;
    while (currAngle >= 360)
        currAngle -= 360;

    // Compute how much the angle changed since last time
    delta = currAngle - lastAngle;

    // If we jumped across the 0/360 line, adjust delta to show movement
    if (delta > 180)
        delta -= 360;
    if (delta < -180)
        delta += 360;

    // Save angle when we loop around
    lastAngle = currAngle;

    // Add this movement to our running total
    signedAngle += delta;

    // if we wrap around by either +/- 360 we reset our relative observed angle back to 0
    if (signedAngle >= 360 || signedAngle <= -360)
        signedAngle = 0;

    return signedAngle;
}
