// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#pragma once
#include <stdint.h>

#ifndef environment_desktop
#include "main.h"                  // required for ITM_Sendchar - TODO : I could reduce the attack surface by only including the core_cm4.h from CMSIS
#include "utilities_conf.h"        // required for UTILS_ENTER_CRITICAL_SECTION and UTILS_EXIT_CRITICAL_SECTION
#else
// dummies so the unit tests on the host compile and run
#define UTILS_ENTER_CRITICAL_SECTION() \
    {}
#define UTILS_EXIT_CRITICAL_SECTION() \
    {}
#endif

// template class for event buffers. Each layer needs it's own buffer, and the events are different types
// This is a circular buffer, so it works FIFO
// push() on an already full buffer, overwrites the oldes event.
// pop() on an empty buffer, returns 0x00
// TODO : this needs to be made thread safe with critical sections. Ideally in this class, but if not possible, then in code that calls it

template <typename eventType, uint32_t bufferLength>
class eventBuffer {
  public:
    static constexpr uint32_t length = bufferLength;

    eventBuffer(){};

    void initialize() {
        head  = 0;
        level = 0;
        // levelMax = 0;
    };

    void push(eventType event) {
        UTILS_ENTER_CRITICAL_SECTION();
        theBuffer[(head + level) % bufferLength] = event;
        if (level < bufferLength) {
            level++;
        } else {
            head = (head + 1) % bufferLength;
        }
        UTILS_EXIT_CRITICAL_SECTION();
    };

    eventType pop() {
        UTILS_ENTER_CRITICAL_SECTION();
        if (level > 0) {
            eventType result = theBuffer[head];
            head             = (head + 1) % bufferLength;
            level--;
            return result;
        } else {
            return static_cast<eventType>(0x00);
        }
        UTILS_EXIT_CRITICAL_SECTION();
    };

    bool isEmpty() const {
        return level == 0;
    };

    bool hasEvents() const {
        return level > 0;
    };

    uint32_t getLevel() const {
        return level;
    };

#ifndef unitTesting
//  private:
#endif
    uint32_t head{0};
    uint32_t level{0};
    eventType theBuffer[bufferLength]{};
    // uint32_t levelMax{0};
};
