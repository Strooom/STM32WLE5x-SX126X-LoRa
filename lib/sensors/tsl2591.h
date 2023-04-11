// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#pragma once
#include <stdint.h>

// Represents an AMS TSL2591 sensor

class tsl2591 {
  public:
    static bool isPresent();                 // detect if there is an TSL2591 on the I2C bus
    static bool initialize();                //
    static float readVisibleLight();         //
    static float readInfraredLight();        //
    static bool goSleep();                   //

    static constexpr uint8_t i2cAddress{0x29};        // default I2C address for this sensor
    static constexpr uint8_t halTrials{0x03};         // ST HAL requires a 'retry' parameters
    static constexpr uint8_t halTimeout{0x10};        // ST HAL requires a 'timeout' in ms

    // Registers
    enum class registers : uint8_t {
        enable  = 0x00,        // enables states and interrupts
        config  = 0x01,        // ALS gain and integration time configuration
        ailtl   = 0x04,        // ALS interrupt low threshold low byte
        ailth   = 0x05,        // ALS interrupt low threshold high byte
        aihtl   = 0x06,        // ALS interrupt high threshold low byte
        aihth   = 0x07,        // ALS interrupt high threshold high byte
        npailtl = 0x08,        // No Persist ALS interrupt low threshold low byte
        npailth = 0x09,        // No Persist ALS interrupt low threshold high byte
        npaihtl = 0x0A,        // No Persist ALS interrupt high threshold low byte
        npaihth = 0x0B,        // No Persist ALS interrupt high threshold high byte
        persist = 0x0C,        // Interrupt persistence filter
        pid     = 0x11,        // Package ID
        id      = 0x12,        // Device ID
        status  = 0x13,        // Device status
        c0datal = 0x14,        // Channel 0 ADC low data byte
        c0datah = 0x15,        // Channel 0 ADC high data byte
        c1datal = 0x16,        // Channel 1 ADC low data byte
        c1datah = 0x17,        // Channel 1 ADC high data byte
    };

    // Commands
    enum class commands : uint8_t {
    };

    // Other
    static constexpr uint8_t chipIdValue = 0x50;        // value to expect at the chipIdregister, this allows to discover/recognize the TSL2591
    static constexpr uint8_t commandMask = 0xA0;        // 1010 0000: bits 7 and 5 for 'command normal'
    static constexpr uint8_t powerOn     = 0x01;
    static constexpr uint8_t powerOff    = 0x00;

    enum class integrationTimes : uint32_t {
        integrationTime100ms = 100,        // [ms]
        integrationTime200ms = 200,
        integrationTime300ms = 300,
        integrationTime400ms = 400,
        integrationTime500ms = 500,
        integrationTime600ms = 600,
    };

    enum class gains : uint32_t {
        gain1x    = 1,
        gain25x   = 25,
        gain428x  = 428,
        gain9876x = 9876,

    };

  private:
    static bool testI2cAddress(uint8_t addressToTest);                          //
    static uint8_t readRegister(registers aRegister);                           //
    static void writeRegister(registers aRegister, const uint8_t value);        //

    static void calculateLight();        //
};