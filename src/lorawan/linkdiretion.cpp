// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#include "linkdirection.h"

const char* toString(linkDirection theDirection) {
    switch (theDirection) {
        case linkDirection::uplink:
            return "uplink";
            break;
        case linkDirection::downlink:
            return "downlink";
            break;
        default:
            return "unknown";
            break;
    }
}