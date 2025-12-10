#pragma once

#include "Arduino.h"
#include "ICanBus.h"
#include "MKSServoCAN.h"
#include <cstdint>

///  @brief  Extension/Wrapper of the MKSServoCAN library for simple motor controls
class motorControls
{

private:
    float zeroedAngle = 0.0f;
    bool isZeroAngleInit = false;

    
public:
    ///  @brief Initializes MKS SERVO 42D hardware to run in our "Haptic Mode"
    ///  @details Takes in the given motor id and calls corresponding functions defined in MKSServoCAN
    ///  library to set the proper hardware settings. Only needs to be called once during first upload, then can be
    ///  removed from setup entirely.
    void initHapticMode(uint32_t id);

    ///  @brief Sets the current tracked angle to 0 degrees on startup.
    ///  @details This is important as it often boots with a current reading of 359.78.
    ///  It reads the encodercarry functions and wraps the angle to always recieve something in the specefied range
    /// 
    ///  @returns a signed angle between (-360, 360)
    float zeroAngle(uint32_t id);
};
