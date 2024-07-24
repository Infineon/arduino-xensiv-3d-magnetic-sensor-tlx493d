// std includes
#include <string.h>

// test includes
#include "Test_includes.h"

#include "TLx493D_W2BW_defines.h"
#include "TLx493D_W2BW_enums.h"
#include "TLx493D_W2BW.h"


void TLx493D_W2BW_suiteSetUp(void);
void TLx493D_W2BW_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static TLx493D_t dut;


// test includes that may require dut
#include "Test_tlx493d_common.h"
#include "Test_tlx493d_gen_2_common.h"


// define test group name
TEST_GROUP(TLx493D_W2BW);
TEST_GROUP(TLx493D_W2BW_internal);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(TLx493D_W2BW_internal)
{
    TLx493D_W2BW_init(&dut);

    memset(dut.regMap, 0, dut.regMapSize);
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(TLx493D_W2BW_internal)
{
    dut.functions->deinit(&dut);
}


TEST_IFX(TLx493D_W2BW_internal, checkUnsupportedFunctionality)
{
    TEST_ASSERT_FALSE( dut.functions->softwareReset(&dut) );
}


/**
 * Define tests for supported common functionality.
 * Requires that the registers have been read once, in setDefaultConfig.
 */
TEST_IFX(TLx493D_W2BW_internal, checkSupportedFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->init(&dut) );
    TEST_ASSERT_TRUE( dut.functions->deinit(&dut) );

    TEST_ASSERT_TRUE( dut.functions->hasWakeUp(&dut) );
}


TEST_IFX(TLx493D_W2BW_internal, checkResetValues)
{
    for(uint8_t i = 0; i < dut.regMapSize; ++i) {
        TEST_ASSERT_EQUAL_HEX8( 0, dut.regMap[i] );
    }

    dut.functions->setResetValues(&dut);

    TEST_ASSERT_EQUAL_HEX8( 0x80, dut.regMap[0x07] );
    TEST_ASSERT_EQUAL_HEX8( 0x7F, dut.regMap[0x08] );
    TEST_ASSERT_EQUAL_HEX8( 0x80, dut.regMap[0x09] );
    TEST_ASSERT_EQUAL_HEX8( 0x7F, dut.regMap[0x0A] );
    TEST_ASSERT_EQUAL_HEX8( 0x80, dut.regMap[0x0B] );
    TEST_ASSERT_EQUAL_HEX8( 0x7F, dut.regMap[0x0C] );
    TEST_ASSERT_EQUAL_HEX8( 0x38, dut.regMap[0x0D] );
    TEST_ASSERT_EQUAL_HEX8( 0x38, dut.regMap[0x0E] );
    TEST_ASSERT_EQUAL_HEX8( 0x38, dut.regMap[0x0F] );  
    TEST_ASSERT_EQUAL_HEX8( 0x01, dut.regMap[0x10] ); // CONFIG
    TEST_ASSERT_EQUAL_HEX8( 0x80, dut.regMap[0x11] ); // MOD1 : A0 : 0x80, A1 : 0x20, A2 : 0x40, A3 : 0xE0
    TEST_ASSERT_EQUAL_HEX8( 0x00, dut.regMap[0x13] ); // MOD2
    TEST_ASSERT_EQUAL_HEX8( 0x00, dut.regMap[0x14] ); // CONFIG2
}


TEST_IFX(TLx493D_W2BW_internal, checkCalculateMagneticFieldAndTemperature)
{
    double temperature = 0.0;
    dut.functions->calculateTemperature(&dut, &temperature);
    TEST_ASSERT_FLOAT_WITHIN( 1.0, -GEN_2_TEMP_OFFSET * GEN_2_TEMP_RESOLUTION + GEN_2_TEMP_REF, temperature );

    double x = 0.0, y = 0.0, z = 0.0;
    dut.functions->calculateMagneticField(&dut, &x, &y, &z);
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, x );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, y );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, z );

    temperature = 0.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
    dut.functions->calculateMagneticFieldAndTemperature(&dut, &x, &y, &z, &temperature);
    TEST_ASSERT_FLOAT_WITHIN( 1.0, -GEN_2_TEMP_OFFSET * GEN_2_TEMP_RESOLUTION + GEN_2_TEMP_REF, temperature );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, x );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, y );
    TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, z );
}


// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(TLx493D_W2BW_internal)
{
    RUN_TEST_CASE(TLx493D_W2BW_internal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(TLx493D_W2BW_internal, checkSupportedFunctionality);

    RUN_TEST_CASE(TLx493D_W2BW_internal, checkResetValues);
    RUN_TEST_CASE(TLx493D_W2BW_internal, checkCalculateMagneticFieldAndTemperature);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(TLx493D_W2BW)
{
    TLx493D_W2BW_suiteSetUp();

    RUN_TEST_GROUP(TLx493D_W2BW_internal);


#ifndef TEST_TLx493D_W2BW_NEEDS_SENSOR

    // run gen 2 common functions tests
    RUN_TEST_GROUP(SensorsGen2Common);
    RUN_TEST_GROUP(SensorsCommon);

#endif


    TLx493D_W2BW_suiteTearDown();
}
