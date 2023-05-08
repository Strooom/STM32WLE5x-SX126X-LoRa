// #############################################################################
// ### This file is part of the source code for the MuMo project             ###
// ### https://github.com/Strooom/MuMo-v2-Node-SW                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################
#include <unity.h>
#include <cstring>
#include "nvs.h"
#include "sx126x.h"
#include "eventbuffer.h"
#include "applicationevent.h"
#include "lorawan.h"

void setUp(void) {}           // before test
void tearDown(void) {}        // after test

nonVolatileStorage nvs;
eventBuffer<loRaWanEvent, 16U> loraWanEventBuffer;
eventBuffer<applicationEvent, 16U> applicationEventBuffer;
sx126x theRadio;
// extern uint8_t mockSx126xDataBuffer[256];

// Test vector is a message actually accepted on the network server
// constexpr uint32_t testVectorLength  = 43;
// uint8_t testVector[testVectorLength] = {
//     0x60,                                                                                                                                                                                      // macHeader : downlink unconfirmed
//     0x92, 0x3B, 0x0B, 0x26,                                                                                                                                                                    // deviceAddress = 0x260B3B92
//     0x00,                                                                                                                                                                                      // frameControl
//     0x3B, 0x00,                                                                                                                                                                                // FrameCount = 0x003B
//     0x00,                                                                                                                                                                                      // framePort = 0
//     0x11, 0x7C, 0xD9, 0xC4, 0xD5, 0x27, 0xA1, 0x78, 0xBD, 0x07, 0x88, 0x8B, 0x67, 0x52, 0xBC, 0xE4, 0x47, 0x26, 0xF9, 0x2B, 0x62, 0x89, 0xC3, 0x06, 0x2F, 0x69, 0x96, 0x4D, 0xD9, 0x18,        // framePayload, 30 bytes, encrypted
//     0x22, 0x58, 0x5F, 0x55};                                                                                                                                                                   // mic

void test_offsetsTx() {
    LoRaWAN theNetwork;

    theNetwork.setOffsetsAndLengthsTx(30U);
    TEST_ASSERT_EQUAL_UINT32(43, theNetwork.loRaPayloadLength);

    // This fakes the read of a LoRa msg from the radio into rawMessage buffer
    theNetwork.loRaPayloadLength = testVectorLength;
    memcpy(theNetwork.rawMessage + theNetwork.b0BlockLength, testVector, testVectorLength);

    theNetwork.setOffsetsAndLengthsRx(theNetwork.loRaPayloadLength);
    TEST_ASSERT_EQUAL_UINT32(0, theNetwork.frameOptionsLength);
    TEST_ASSERT_EQUAL_UINT32(7, theNetwork.frameHeaderLength);
    TEST_ASSERT_EQUAL_UINT32(30, theNetwork.framePayloadLength);

    TEST_ASSERT_EQUAL_UINT32(theNetwork.b0BlockLength + 8, theNetwork.framePortOffset);
    TEST_ASSERT_EQUAL_UINT32(theNetwork.b0BlockLength + 9, theNetwork.framePayloadOffset);
    TEST_ASSERT_EQUAL_UINT32(theNetwork.b0BlockLength + 39, theNetwork.micOffset);

    // Now let's double check and test some of the contents at the offsets
    TEST_ASSERT_EQUAL_UINT32(0x60, theNetwork.rawMessage[theNetwork.headerOffset]);               // macHeader
    TEST_ASSERT_EQUAL_UINT32(0x92, theNetwork.rawMessage[theNetwork.deviceAddressOffset]);        // first byte (LSB) of DevAddr
    TEST_ASSERT_EQUAL_UINT32(0, theNetwork.rawMessage[theNetwork.frameControlOffset]);            // frameControl
    TEST_ASSERT_EQUAL_UINT32(0x3B, theNetwork.rawMessage[theNetwork.frameCountOffset]);           // first byte (LSB) of frameCount
    TEST_ASSERT_EQUAL_UINT32(0x22, theNetwork.rawMessage[theNetwork.micOffset]);                  // first byte of MIC

    // TODO : I need an additional test with frameOptions NOT empty
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_offsetsTx);
    UNITY_END();
}