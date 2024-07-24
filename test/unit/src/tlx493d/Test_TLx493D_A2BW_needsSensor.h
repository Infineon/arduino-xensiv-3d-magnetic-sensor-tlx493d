// test includes
#include "Test_includes.h"

#include "TLx493D_A2BW_defines.h"
#include "TLx493D_A2BW_enums.h"
#include "TLx493D_A2BW.h"


void TLx493D_A2BW_needsSensor_suiteSetup(void);
void TLx493D_A2BW_needsSensor_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static TLx493D_t dut;


// test includes that may require dut
#include "Test_tlx493d_commonFunctions_needsSensor.h"
#include "Test_tlx493d_common.h"
#include "Test_tlx493d_gen_2_common.h"


// define test group name
TEST_GROUP(TLx493D_A2BW_needsSensor);
TEST_GROUP(TLx493D_A2BW_needsSensorInternal);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(TLx493D_A2BW_needsSensorInternal)
{
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(TLx493D_A2BW_needsSensorInternal)
{
}


// Define all relevant tests for the sensor device
/**
 * Define tests for unsupported common functionality.
 */
TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkUnsupportedFunctionality)
{
}


/**
 * Define tests for supported common functionality.
 * Requires that the registers have been read once, in setDefaultConfig.
 */

TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkSupportedFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut) );
    // tlx493d_printRegisters(&dut);
 
    TEST_ASSERT_TRUE( dut.functions->hasValidData(&dut) );      // fails sometimes with readRegisters()
    TEST_ASSERT_TRUE( dut.functions->hasValidBusParity(&dut) ); // fails sometimes with readRegisters()
    TEST_ASSERT_TRUE( dut.functions->hasValidTBit(&dut) );      // fails sometimes with readRegisters()

    TEST_ASSERT_TRUE( dut.functions->isFunctional(&dut) );
    TEST_ASSERT_TRUE( dut.functions->hasValidFuseParity(&dut) );
    TEST_ASSERT_TRUE( dut.functions->hasValidConfigurationParity(&dut) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkGetMagneticFieldAndTemperature)
{
    double xfr, yfr, zfr, tfr, tfr0;

    TEST_ASSERT_TRUE( dut.functions->getTemperature(&dut, &tfr0) );
    TEST_ASSERT_FLOAT_WITHIN( 20.0, 25.0, tfr0 );
    tlx493d_printRegisters(&dut);

    dut.functions->calculateMagneticField(&dut, &xfr, &yfr, &zfr);
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, xfr );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, yfr );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, zfr );

    dut.functions->calculateMagneticFieldAndTemperature(&dut, &xfr, &yfr, &zfr, &tfr);
    TEST_ASSERT_EQUAL_FLOAT( tfr, tfr0 );
    TEST_ASSERT_FLOAT_WITHIN( 20.0, 25.0, tfr );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, xfr );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, yfr );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, zfr );


    // TLx493D_FULL_RANGE_e
    int16_t xfrr, yfrr, zfrr, tfrr;
    dut.functions->calculateRawMagneticFieldAndTemperature(&dut, &xfrr, &yfrr, &zfrr, &tfrr);

    int16_t xfrr2, yfrr2, zfrr2, tfrr2;
    tlx493d_gen_2_convertTemperatureToRaw(&dut, tfr0, &tfrr2);
    dut.functions->calculateRawMagneticFieldAtTemperature(&dut, tfr, TLx493D_FULL_RANGE_e, xfr, yfr, zfr, &xfrr2, &yfrr2, &zfrr2);

    TEST_ASSERT_EQUAL_INT16( tfrr, tfrr2 );
    TEST_ASSERT_EQUAL_INT16( xfrr, xfrr2 );
    TEST_ASSERT_EQUAL_INT16( yfrr, yfrr2 );
    TEST_ASSERT_EQUAL_INT16( zfrr, zfrr2 );

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // TLx493D_SHORT_RANGE_e
    double xsr, ysr, zsr, tsr, tsr0;

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->getTemperature(&dut, &tsr0) );
    tlx493d_printRegisters(&dut);

    int16_t xsrr, ysrr, zsrr, tsrr;
    dut.functions->calculateMagneticFieldAndTemperature(&dut, &xsr, &ysr, &zsr, &tsr);
    dut.functions->calculateRawMagneticFieldAndTemperature(&dut, &xsrr, &ysrr, &zsrr, &tsrr);

    int16_t xsrr3, ysrr3, zsrr3, tsrr3;
    tlx493d_gen_2_convertTemperatureToRaw(&dut, tsr0, &tsrr3);
    dut.functions->calculateRawMagneticFieldAtTemperature(&dut, tsrr, TLx493D_SHORT_RANGE_e, xsr, ysr, zsr, &xsrr3, &ysrr3, &zsrr3);

    TEST_ASSERT_EQUAL_FLOAT( tsr, tsr0 );
    TEST_ASSERT_EQUAL_INT16( tsrr, tsrr3 );
    TEST_ASSERT_EQUAL_INT16( xsrr, xsrr3 );
    TEST_ASSERT_EQUAL_INT16( ysrr, ysrr3 );
    TEST_ASSERT_EQUAL_INT16( zsrr, zsrr3 );


    TEST_ASSERT_FLOAT_WITHIN( 1, tfr0, tsr0 );
    TEST_ASSERT_FLOAT_WITHIN( 1, xsr, xfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, ysr, yfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, zsr, zfr );


    // back to TLx493D_FULL_RANGE_e
    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_FULL_RANGE_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkBasicFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkConfigMeasurementFunctionality)
{
    // Unsupported
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_VHall_Bias_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_Spintest_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_SAT_test_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_BxTemp_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_BzTemp_e) );


    // Supported
    // TLx493D_BxBy_e
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxBy_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_DT_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_AM_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x80, tlx493d_common_returnBitfield(&dut, A2BW_BZ_MSBS_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x80, tlx493d_common_returnBitfield(&dut, A2BW_TEMP_MSBS_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_TEMP_LSBS_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_BZ_LSBS_e) );


    // TLx493D_BxByBz_e
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxByBz_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_DT_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_AM_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x80, tlx493d_common_returnBitfield(&dut, A2BW_TEMP_MSBS_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_TEMP_LSBS_e) );


    // TLx493D_BxByBzTemp_e
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxByBzTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_DT_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_AM_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkConfigTriggerFunctionality)
{
    // switch to LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );

    // Low-power mode only supports this trigger
    TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_NO_ADC_ON_READ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_TRIG_e) );


    // MCM supports other modes, so enable MCM first
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_MASTER_CONTROLLED_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );

    // try triggers
    TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_ADC_ON_READ_AFTER_REG_05_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_GREATER_OR_EQUAL_INT8( 0b10, tlx493d_common_returnBitfield(&dut, A2BW_TRIG_e) );
    TEST_ASSERT_LESS_OR_EQUAL_INT8( 0b11, tlx493d_common_returnBitfield(&dut, A2BW_TRIG_e) );

    // Not to be used with our default config CA = 0, INT = 1 !
    // TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_ADC_ON_READ_BEFORE_FIRST_MSB_e) );
    // TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_TRIG_e) );

    TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_NO_ADC_ON_READ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_TRIG_e) );


    // switch back to LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkConfigSensitivityFunctionality)
{
    double sf;

    // supported
    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_EXTRA_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_X2_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_X4_READWRITE_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 4.0, sf );


    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_X2_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_X4_READWRITE_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 2.0, sf );
   

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_FULL_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_X2_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_X4_READWRITE_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 1.0, sf );
}


// Check if setDefaultConfig worked properly and data can be read and expected values are set.
TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModeDefaultConfigFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    tlx493d_printRegisters(&dut);

    TEST_ASSERT_EQUAL_HEX8( 0x00, dut.regMap[A2BW_CONFIG_REG_e] & 0xFE );
    TEST_ASSERT_EQUAL_HEX8( 0x94, dut.regMap[A2BW_MOD1_REG_e] ); // PR on, CA on
    TEST_ASSERT_EQUAL_HEX8( 0x01, dut.regMap[A2BW_MOD2_REG_e] );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModeIICAddressFunctionality)
{
    // tlx493d_printRegisters(&dut);
    // logPrint("addr : %x", dut.comLibIFParams.i2c_params.address << 1);

    TEST_ASSERT_TRUE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A3_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x03, tlx493d_common_returnBitfield(&dut, A2BW_IICADR_e) );
    TEST_ASSERT_TRUE( TLx493D_A2BW_hasValidIICadr(&dut) );

    TEST_ASSERT_TRUE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A2_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x02, tlx493d_common_returnBitfield(&dut, A2BW_IICADR_e) );
    TEST_ASSERT_TRUE( TLx493D_A2BW_hasValidIICadr(&dut) );

    TEST_ASSERT_TRUE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A1_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_IICADR_e) );
    TEST_ASSERT_TRUE( TLx493D_A2BW_hasValidIICadr(&dut) );

    TEST_ASSERT_TRUE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A0_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_IICADR_e) );
    TEST_ASSERT_TRUE( TLx493D_A2BW_hasValidIICadr(&dut) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModeCollisionAvoidanceFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->disableCollisionAvoidance(&dut) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_CA_e) );

    TEST_ASSERT_TRUE( dut.functions->enableCollisionAvoidance(&dut) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_CA_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModeInterruptFunctionality)
{
    // TEST_ASSERT_TRUE( dut.functions->enableInterrupt(&dut) );
    // TEST_ASSERT_EQUAL_HEX8( (dut.regMap[A2BW_MOD1_REG_e] & 0x04) == 0x00 );

    TEST_ASSERT_TRUE( dut.functions->disableInterrupt(&dut) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_INT_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModePowerModeFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_FAST_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x03, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );

    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_MASTER_CONTROLLED_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );

    // forbidden
    TEST_ASSERT_NOT_EQUAL( 0x10, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );

    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, A2BW_MODE_e) );
}


TEST_IFX(TLx493D_A2BW_needsSensorInternal, checkModeUpdateRateFunctionality)
{
    // Supported
    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_SLOW_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1, tlx493d_common_returnBitfield(&dut, A2BW_PRD_e) );

    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_FAST_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b0, tlx493d_common_returnBitfield(&dut, A2BW_PRD_e) );


    // Unsupported
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_1000_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_770_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_125_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_97_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_31_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_24_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_16_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_12_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_6_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_3_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_0_4_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_0_05_HZ_e) );
}


static TEST_GROUP_RUNNER(TLx493D_A2BW_needsSensorInternal)
{
    // First test default config applied in runner setup method 
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeDefaultConfigFunctionality);

    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkSupportedFunctionality);

    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkBasicFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkGetMagneticFieldAndTemperature);

    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkConfigMeasurementFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkConfigTriggerFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkConfigSensitivityFunctionality);

    // RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeDefaultConfigFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeIICAddressFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeCollisionAvoidanceFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeInterruptFunctionality);
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModePowerModeFunctionality);

    // MOD2
    RUN_TEST_CASE(TLx493D_A2BW_needsSensorInternal, checkModeUpdateRateFunctionality);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(TLx493D_A2BW_needsSensor)
{
    TLx493D_A2BW_needsSensor_suiteSetup();

    RUN_TEST_GROUP(TLx493D_A2BW_needsSensorInternal);
    
    // // run common functions tests
    RUN_TEST_GROUP(SensorsCommonFunctions);

    // // run gen 2 common functions tests
    RUN_TEST_GROUP(SensorsGen2Common);
    RUN_TEST_GROUP(SensorsCommon);

    TLx493D_A2BW_needsSensor_suiteTearDown();
}
