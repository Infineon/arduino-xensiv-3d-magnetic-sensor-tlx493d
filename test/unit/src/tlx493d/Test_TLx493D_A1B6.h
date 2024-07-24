// std includes
#include <string.h>

// test includes
#include "Test_includes.h"

#include "TLx493D_A1B6_defines.h"
#include "TLx493D_A1B6_enums.h"
#include "TLx493D_A1B6.h"


void TLx493D_A1B6_suiteSetUp(void);
void TLx493D_A1B6_suiteTearDown(void);

//defines


// variables used in the tests below that have to be accessed in the setup and tear down methods
static TLx493D_t dut;


// test includes that may require dut
#include "Test_tlx493d_common.h"


// define test group name
TEST_GROUP(TLx493D_A1B6);


// Setup method called before every individual test defined for this test group
TEST_SETUP(TLx493D_A1B6)
{
    (void) TLx493D_A1B6_init(&dut);

    // certain compilers might not initialize the memory locations allocated by malloc()
    // so to ensure that the static (noSensor) unit tests pass, memset() is used to 
    // initialize to 0.
    memset(dut.regMap, 0, dut.regMapSize);
}


// Tear down method called before every individual test defined for this test group
TEST_TEAR_DOWN(TLx493D_A1B6)
{
    (void) TLx493D_A1B6_deinit(&dut);
}


/**
 * Define tests for unsupported common functionality
 */
TEST(TLx493D_A1B6, checkUnsupportedFunctionality)
{
    static double  xl, xh, yl, yh, zl, zh, t;
    static int16_t xl_i, xh_i, yl_i, yh_i, zl_i, zh_i;

    TEST_ASSERT( dut.functions->setTrigger(&dut, (TLx493D_TriggerType_t)0) == false );
    TEST_ASSERT( dut.functions->setSensitivity(&dut, (TLx493D_SensitivityType_t)0) == false );
    TEST_ASSERT( dut.functions->enable1ByteReadMode(&dut) == false );
    TEST_ASSERT( dut.functions->enableCollisionAvoidance(&dut) == false );
    TEST_ASSERT( dut.functions->disableCollisionAvoidance(&dut) == false );
    TEST_ASSERT( dut.functions->setUpdateRate(&dut, (TLx493D_UpdateRateType_t)0) == false );
    TEST_ASSERT( dut.functions->calculateFuseParity(&dut) == false );
    TEST_ASSERT( dut.functions->calculateBusParity(&dut) == false );    
    TEST_ASSERT( dut.functions->hasWakeUp(&dut) == false );
    TEST_ASSERT( dut.functions->isWakeUpEnabled(&dut) == false );
    TEST_ASSERT( dut.functions->enableWakeUpMode(&dut) == false );
    TEST_ASSERT( dut.functions->disableWakeUpMode(&dut) == false );

    TEST_ASSERT( dut.functions->setWakeUpThresholdsAsInteger(&dut, xh_i, xl_i, yh_i, yl_i, zh_i, zl_i) == false );
    TEST_ASSERT( dut.functions->setWakeUpThresholds(&dut, t, xh, xl, yh, yl, zh, zl) == false );

    TEST_ASSERT( dut.functions->softwareReset(&dut) == false );
    TEST_ASSERT( dut.functions->calculateFuseParity(&dut) == false );
    TEST_ASSERT( dut.functions->calculateBusParity(&dut) == false );

    TEST_ASSERT( dut.functions->hasValidBusParity(&dut) == false );
    TEST_ASSERT( dut.functions->hasValidConfigurationParity(&dut) == false );
    TEST_ASSERT( dut.functions->getSensitivityScaleFactor(&dut) == false );
}

/**
 * Define tests for supported common functionality.
 * Requires that the registers have been read once, in setDefaultConfig.
 */
TEST(TLx493D_A1B6, checkSupportedFunctionality)
{
    TEST_ASSERT( dut.functions->init(&dut) == true );
    TEST_ASSERT( dut.functions->deinit(&dut) == true );
}

TEST(TLx493D_A1B6, checkResetValues)
{
    for(uint8_t i = 0; i < dut.regMapSize; ++i) {
        TEST_ASSERT( dut.regMap[i] == 0 );
    }

    dut.functions->setResetValues(&dut);

    // reserved values mirrored from READ to WRITE registers
    TEST_ASSERT_EQUAL( dut.regMap[dut.regDef[A1B6_W_RES_1_e].address + GEN_1_WRITE_REGISTERS_OFFSET], dut.regMap[dut.regDef[A1B6_R_RES_1_e].address] );
    TEST_ASSERT_EQUAL( dut.regMap[dut.regDef[A1B6_W_RES_2_e].address + GEN_1_WRITE_REGISTERS_OFFSET], dut.regMap[dut.regDef[A1B6_R_RES_2_e].address] );
    TEST_ASSERT_EQUAL( dut.regMap[dut.regDef[A1B6_W_RES_3_e].address + GEN_1_WRITE_REGISTERS_OFFSET], dut.regMap[dut.regDef[A1B6_R_RES_3_e].address] );

    TEST_ASSERT( dut.regMap[0x01 + GEN_1_WRITE_REGISTERS_OFFSET] == 0x00 ); // MOD1
    TEST_ASSERT( dut.regMap[0x03 + GEN_1_WRITE_REGISTERS_OFFSET] == 0x00 ); // MOD2
}

// Define all relevant tests for the sensor device

TEST(TLx493D_A1B6, calculateTemperature)
{
    double temperature = 0.0;
    TLx493D_A1B6_calculateTemperature(&dut, &temperature);
    TEST_ASSERT_FLOAT_WITHIN( 0, ((0.0-GEN_1_TEMP_OFFSET) * GEN_1_TEMP_MULT) + GEN_1_REF_TEMP, temperature );
}

TEST(TLx493D_A1B6, calculateMagneticField)
{
    double x = 0.0, y = 0.0, z = 0.0;
    TLx493D_A1B6_calculateMagneticField(&dut, &x, &y, &z);
    TEST_ASSERT_FLOAT_WITHIN( 0, 0.0 * GEN_1_MAG_FIELD_MULT, x );
    TEST_ASSERT_FLOAT_WITHIN( 0, 0.0 * GEN_1_MAG_FIELD_MULT, y );
    TEST_ASSERT_FLOAT_WITHIN( 0, 0.0 * GEN_1_MAG_FIELD_MULT, z );
}

TEST(TLx493D_A1B6, setter_BitFields)
{
    memset(dut.regMap,0,dut.regMapSize);

    // for gen1 setBitField is used to set values of WRITE registers (BitFields) only (due to a check for TLx493D_WRITE_MODE_e access)
    // so we test this function only for WRITE BitFields 
    for(uint8_t i=0; i < GEN_1_BITFIELDS_COUNT; i++){
        TLx493D_Register_t *bf = &dut.regDef[i];
        if (bf->accessMode == TLx493D_WRITE_MODE_e){
            TLx493D_A1B6_setBitfield(&dut, i, (pow(2, bf->numBits)-1)); //set all bits of bitfield as HIGH 
            TEST_ASSERT_EQUAL(pow(2,bf->numBits)-1, (dut.regMap[bf->address+GEN_1_WRITE_REGISTERS_OFFSET] & bf->mask) >> bf->offset); // check if it matches the same value, we set above
            // Note: The RegMap in gen1 for WRITE registers is shifted by a constant offset 
        }
    }
}

TEST(TLx493D_A1B6, getter_BitFields)
{
    memset(dut.regMap,0,dut.regMapSize);

    // for gen1 returnBitField is used to get values of READ registers (BitFields) only (due to a check for TLx493D_READ_MODE_e access)
    // so we test this function only for READ BitFields 
    for(uint8_t i=0; i<GEN_1_BITFIELDS_COUNT; i++){
        TLx493D_Register_t *bf = &dut.regDef[i];
        if (bf->accessMode == TLx493D_READ_MODE_e){
            // first set the values (all bits as HIGH) of READ BitFields directly in the regMap
            dut.regMap[bf->address] = (dut.regMap[bf->address] & ~bf->mask) | ((uint8_t)(pow(2,bf->numBits)-1) << bf->offset);
            // then check against the same value as above
            TEST_ASSERT_EQUAL(pow(2,bf->numBits)-1, TLx493D_A1B6_returnBitfield(&dut, i));            
        }
    }
}

// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(TLx493D_A1B6)
{
    TLx493D_A1B6_suiteSetUp();
    RUN_TEST_CASE(TLx493D_A1B6, checkUnsupportedFunctionality);
    RUN_TEST_CASE(TLx493D_A1B6, checkSupportedFunctionality);
    RUN_TEST_CASE(TLx493D_A1B6, checkResetValues);
    RUN_TEST_CASE(TLx493D_A1B6, calculateTemperature);
    RUN_TEST_CASE(TLx493D_A1B6, calculateMagneticField);
    RUN_TEST_CASE(TLx493D_A1B6, setter_BitFields);
    RUN_TEST_CASE(TLx493D_A1B6, getter_BitFields);


#ifndef TEST_TLx493D_A1B6_NEEDS_SENSOR

    // run common functions tests
    RUN_TEST_GROUP(SensorsCommon);

#endif


    TLx493D_A1B6_suiteTearDown();
}
