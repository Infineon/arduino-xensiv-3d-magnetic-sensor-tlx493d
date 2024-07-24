#ifndef TEST_TLX493D_COMMON_H
#define TEST_TLX493D_COMMON_H


// std includes
#include <string.h>

// test includes
#include "Test_includes.h"


// Variables used in the tests below that have to be accessed in the setup and tear down methods.
// The "dut" variable is taken from the respective sensor that the common functions are applied to.


// define test group name
TEST_GROUP(SensorsCommon);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(SensorsCommon)
{
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(SensorsCommon)
{
}


TEST_IFX(SensorsCommon, checkParityFunctionality)
{
    // even parity values
    uint8_t data   = 0x00;
    uint8_t parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );

    data   = 0x33;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getOddParity(parity) );

    data   = 0x55;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getOddParity(parity) );
    
    data   = 0xAA;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getOddParity(parity) );

    data   = 0x36;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getOddParity(parity) );

    data   = 0xFF;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x00, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getOddParity(parity) );

    // odd parity values
    data   = 0x01;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0x80;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0x37;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0x86;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0x68;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0xF8;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );

    data   = 0xF7;
    parity = tlx493d_common_calculateParity(data);
    TEST_ASSERT_EQUAL_HEX8( 0x01, parity );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_getEvenParity(parity) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_getOddParity(parity) );
}


TEST_IFX(SensorsCommon, checkConcatBytes)
{
    enum RegisterNames {
        MSB0 = 0,
        MSB1,
        MSB2,
        MSB3,
        LSB0,
        LSB1,
        LSB2,
        LSB3,
    };


    TLx493D_Register_t regDef[] = {
        { /* MSB0, */  TLx493D_READ_MODE_e,  0x00, 0xFF, 0, 8 },
        { /* MSB1, */  TLx493D_READ_MODE_e,  0x01, 0x0F, 0, 4 },
        { /* MSB2, */  TLx493D_READ_MODE_e,  0x02, 0x3F, 0, 6 }, 
        { /* MSB3, */  TLx493D_READ_MODE_e,  0x03, 0xF6, 1, 7 },

        { /* LSB0, */  TLx493D_READ_MODE_e,  0x04, 0xFF, 0, 8 },
        { /* LSB1, */  TLx493D_READ_MODE_e,  0x05, 0x0F, 0, 4 },
        { /* LSB2, */  TLx493D_READ_MODE_e,  0x06, 0xC0, 6, 2 },
        { /* LSB3, */  TLx493D_READ_MODE_e,  0x07, 0x0F, 0, 4 },
    };

    TLx493D_Register_t *regDefSave = dut.regDef;
    dut.regDef = regDef;

    uint8_t saveRegs[8];
    memcpy(saveRegs, dut.regMap, 8);

    dut.regMap[0x00] = 0x11;
    dut.regMap[0x01] = 0x33;
    dut.regMap[0x02] = 0x77;
    dut.regMap[0x03] = 0xFF;

    dut.regMap[0x04] = 0x00;
    dut.regMap[0x05] = 0x22;
    dut.regMap[0x06] = 0x77;
    dut.regMap[0x07] = 0xFF;


    int16_t result = 0;
    tlx493d_common_concatBytes(&dut, MSB0, LSB0, &result);
    TEST_ASSERT_EQUAL_HEX16( 0x1100, result );

    result = 0;
    tlx493d_common_concatBytes(&dut, MSB1, LSB1, &result);
    TEST_ASSERT_EQUAL_HEX8( 0x32, result );

    result = 0;
    tlx493d_common_concatBytes(&dut, MSB2, LSB2, &result);
    TEST_ASSERT_EQUAL_HEX32( 0xFFFFFFDD, result );

    result = 0;
    tlx493d_common_concatBytes(&dut, MSB3, LSB3, &result);
    TEST_ASSERT_EQUAL_HEX32( 0xFFFFFFBF, result );

    dut.regDef = regDefSave;
    memcpy(dut.regMap, saveRegs, 8);
}


TEST_IFX(SensorsCommon, checkGetTypeAsString)
{
    TLx493D_SupportedSensorType_t sensorType = dut.sensorType;

    dut.sensorType = TLx493D_A2B6_e;
    TEST_ASSERT_EQUAL_STRING( "TLx493D_A2B6", tlx493d_common_getTypeAsString(&dut) );
    
    TEST_ASSERT_FALSE( tlx493d_init(&dut, (TLx493D_SupportedSensorType_t) 0x19) );

    dut.sensorType = (TLx493D_SupportedSensorType_t) 0x19;
    TEST_ASSERT_EQUAL_STRING( "ERROR : Unknown sensorType !", tlx493d_common_getTypeAsString(&dut) );

    dut.sensorType = sensorType;
}


// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(SensorsCommon)
{
    RUN_TEST_CASE(SensorsCommon, checkParityFunctionality);
    RUN_TEST_CASE(SensorsCommon, checkConcatBytes);
    RUN_TEST_CASE(SensorsCommon, checkGetTypeAsString);
}


#endif // TEST_SENSORS_COMMON_H
