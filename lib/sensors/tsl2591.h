// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>
#include "sensor.h"

// Represents an AMS TSL2591 sensor

class tsl2591 : public sensor {
  public:
    static bool isPresent();        // detect if there is an TSL2591 on the I2C bus
    const char* getName();          //
    static bool reset();            // soft-reset
    bool initialize();              //
    bool doMeasurement();           //
    bool goSleep();                 //

    static constexpr uint8_t i2cAddress{0x29};        // default I2C address for this sensor

    // Registers
    // static constexpr uint8_t chipIdRegister{0xD0};        // address of register holding chipId

    // Commands
    // static constexpr uint8_t softResetCommand{0xB6};

    // Other
    // static constexpr uint8_t chipIdValue{0x61};        // value to expect at the chipIdregister, this allows to discover/recognize the BME68x

  private:
    bool readRegisters() const;        // TODO add parameters
    bool writeRegisters();             // TODO add parameters
    void calculateLuminosity();        //
};