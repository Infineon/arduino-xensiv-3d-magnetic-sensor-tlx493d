// test includes
#include "Test_includes.h"

#include "TLx493D_P3I8_defines.h"
#include "TLx493D_P3I8_enums.h"
#include "TLx493D_P3I8.h"


void TLx493D_P3I8_needsSensor_suiteSetup(void);
void TLx493D_P3I8_needsSensor_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static TLx493D_t dut;


// test includes that may require dut
#include "Test_tlx493d_commonFunctions_needsSensor.h"
#include "Test_tlx493d_common.h"
#include "Test_tlx493d_gen_3_common.h"


// define test group name
TEST_GROUP(TLx493D_P3I8_needsSensor);
TEST_GROUP(TLx493D_P3I8_needsSensorInternal);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(TLx493D_P3I8_needsSensorInternal)
{
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(TLx493D_P3I8_needsSensorInternal)
{
}


// Define all relevant tests for the sensor device
/**
 * Define tests for unsupported common functionality.
 */
TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkUnsupportedFunctionality)
{
    TEST_ASSERT_FALSE( dut.functions->hasValidBusParity(&dut) );
    TEST_ASSERT_FALSE( dut.functions->hasValidConfigurationParity(&dut) );
    TEST_ASSERT_FALSE( dut.functions->hasValidTBit(&dut) );
 
    TEST_ASSERT_FALSE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A0_e) );
    TEST_ASSERT_FALSE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A1_e) );
    TEST_ASSERT_FALSE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A2_e) );
    TEST_ASSERT_FALSE( dut.functions->setIICAddress(&dut, TLx493D_IIC_ADDR_A3_e) );

    TEST_ASSERT_FALSE( dut.functions->enable1ByteReadMode(&dut) );
    TEST_ASSERT_FALSE( dut.functions->enableCollisionAvoidance(&dut) );
    TEST_ASSERT_FALSE( dut.functions->disableCollisionAvoidance(&dut) );
    // tlx493d_printRegisters(&dut);
}


/**
 * Define tests for supported common functionality.
 * Requires that the registers have been read once, in setDefaultConfig.
 */
TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkSupportedFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut) );
    // tlx493d_printRegisters(&dut);
 
    TEST_ASSERT_TRUE( dut.functions->hasValidData(&dut) ); // fails sometimes

    TEST_ASSERT_TRUE( dut.functions->isFunctional(&dut) );
    TEST_ASSERT_TRUE( dut.functions->hasValidFuseParity(&dut) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkGetMagneticFieldAndTemperature)
{
    double xfr, yfr, zfr, tfr, tfr0;

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_FULL_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->getTemperature(&dut, &tfr0) );
    TEST_ASSERT_FLOAT_WITHIN( 20.0, 25.0, tfr0 );
    // tlx493d_printRegisters(&dut);

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
    tlx493d_gen_3_convertTemperatureToRaw(&dut, tfr0, &tfrr2);
    dut.functions->calculateRawMagneticFieldAtTemperature(&dut, tfrr, TLx493D_FULL_RANGE_e, xfr, yfr, zfr, &xfrr2, &yfrr2, &zfrr2);

    TEST_ASSERT_EQUAL_INT16( tfrr, tfrr2 );
    TEST_ASSERT_EQUAL_INT16( xfrr, xfrr2 );
    TEST_ASSERT_EQUAL_INT16( yfrr, yfrr2 );
    TEST_ASSERT_EQUAL_INT16( zfrr, zfrr2 );

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // TLx493D_SHORT_RANGE_e
    double xsr, ysr, zsr, tsr, tsr0;

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->getTemperature(&dut, &tsr0) );
    // tlx493d_printRegisters(&dut);

    int16_t xsrr, ysrr, zsrr, tsrr;
    dut.functions->calculateMagneticFieldAndTemperature(&dut, &xsr, &ysr, &zsr, &tsr);
    dut.functions->calculateRawMagneticFieldAndTemperature(&dut, &xsrr, &ysrr, &zsrr, &tsrr);

    int16_t xsrr3, ysrr3, zsrr3, tsrr3;
    tlx493d_gen_3_convertTemperatureToRaw(&dut, tsr0, &tsrr3);
    dut.functions->calculateRawMagneticFieldAtTemperature(&dut, tsrr, TLx493D_SHORT_RANGE_e, xsr, ysr, zsr, &xsrr3, &ysrr3, &zsrr3);

    TEST_ASSERT_EQUAL_FLOAT( tsr, tsr0 );
    TEST_ASSERT_EQUAL_INT16( tsrr, tsrr3 );
    TEST_ASSERT_EQUAL_INT16( xsrr, xsrr3 );
    TEST_ASSERT_EQUAL_INT16( ysrr, ysrr3 );
    TEST_ASSERT_EQUAL_INT16( zsrr, zsrr3 );


    TEST_ASSERT_FLOAT_WITHIN( 2, tfr0, tsr0 );
    TEST_ASSERT_FLOAT_WITHIN( 1, xsr, xfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, ysr, yfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, zsr, zfr );


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // TLx493D_EXTRA_SHORT_RANGE_e
    double xesr, yesr, zesr, tesr, tesr0;

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_EXTRA_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->getTemperature(&dut, &tesr0) );
    // tlx493d_printRegisters(&dut);

    int16_t xesrr, yesrr, zesrr, tesrr;
    dut.functions->calculateMagneticFieldAndTemperature(&dut, &xesr, &yesr, &zesr, &tesr);
    dut.functions->calculateRawMagneticFieldAndTemperature(&dut, &xesrr, &yesrr, &zesrr, &tesrr);

    int16_t xesrr3, yesrr3, zesrr3, tesrr3;
    tlx493d_gen_3_convertTemperatureToRaw(&dut, tesr0, &tesrr3);
    dut.functions->calculateRawMagneticFieldAtTemperature(&dut, tesrr, TLx493D_EXTRA_SHORT_RANGE_e, xesr, yesr, zesr, &xesrr3, &yesrr3, &zesrr3);

    TEST_ASSERT_EQUAL_FLOAT( tesr, tesr0 );
    TEST_ASSERT_EQUAL_INT16( tesrr, tesrr3 );
    TEST_ASSERT_EQUAL_INT16( xesrr, xesrr3 );
    TEST_ASSERT_EQUAL_INT16( yesrr, yesrr3 );
    TEST_ASSERT_EQUAL_INT16( zesrr, zesrr3 );


    TEST_ASSERT_FLOAT_WITHIN( 2, tfr0, tesr0 );
    TEST_ASSERT_FLOAT_WITHIN( 1, xesr, xfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, yesr, yfr );
    TEST_ASSERT_FLOAT_WITHIN( 1, zesr, zfr );


    // back to TLx493D_FULL_RANGE_e
    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_FULL_RANGE_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkBasicFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut));
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkConfigMeasurementFunctionality)
{
    // switch to LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );


    // Unsupported
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_BxByBz_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_VHall_Bias_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_Spintest_e) );
    TEST_ASSERT_FALSE( dut.functions->setMeasurement(&dut, TLx493D_SAT_test_e) );


    // logPrint("TLx493D_BxTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1100, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1100, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );
   

    // logPrint("TLx493D_BxBy_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxBy_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1101, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1101, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // logPrint("TLx493D_BzTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BzTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1110, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1110, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // logPrint("TLx493D_BxByBzTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxByBzTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b0000, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b0000, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // switch to MCM
    // logPrint("MCM mode\n");
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_MASTER_CONTROLLED_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );


    // logPrint("TLx493D_BxTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1100, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1100, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );
   

    // logPrint("TLx493D_BxBy_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxBy_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1101, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1101, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // logPrint("TLx493D_BzTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BzTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b1110, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b1110, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // logPrint("TLx493D_BxByBzTemp_e\n");
    TEST_ASSERT_TRUE( dut.functions->setMeasurement(&dut, TLx493D_BxByBzTemp_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b0000, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_e) );
    TEST_ASSERT_EQUAL_HEX8( 0b0000, tlx493d_common_returnBitfield(&dut, P3I8_CHANNEL_SEL_SAVE_e) );


    // switch to LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkConfigTriggerFunctionality)
{
    // In low-power mode trigger selection is ignored !

    // MCM supports other modes, so enable MCM first
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_MASTER_CONTROLLED_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );

    // try triggers
    // There is no stop condition for SPI interfaces, so ignore this mode !
    TEST_ASSERT_FALSE( dut.functions->setTrigger(&dut, TLx493D_ADC_ON_STOP_CONDITION_e) );
    // TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_ADC_ON_STOP_CONDITION_e) );
    // TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    // TEST_ASSERT_GREATER_OR_EQUAL_INT8( 0b10, tlx493d_common_returnBitfield(&dut, P3I8_TRIGGER_SEL_e) );
    // TEST_ASSERT_LESS_OR_EQUAL_INT8( 0b11, tlx493d_common_returnBitfield(&dut, P3I8_TRIGGER_SEL_e) );

    //
    TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_ADC_ON_READ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b01, tlx493d_common_returnBitfield(&dut, P3I8_TRIGGER_SEL_e) );

    //
    TEST_ASSERT_TRUE( dut.functions->setTrigger(&dut, TLx493D_NO_TRIGGER_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b00, tlx493d_common_returnBitfield(&dut, P3I8_TRIGGER_SEL_e) );


    // switch back to LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkConfigSensitivityFunctionality)
{
    double sf;

    // Unsupported
    TEST_ASSERT( (tlx493d_common_returnBitfield(&dut, P3I8_SHORT_EN_e) & tlx493d_common_returnBitfield(&dut, P3I8_XTR_SHORT_EN_e)) != 1 );

    
    // supported
    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_EXTRA_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_XTR_SHORT_EN_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_SHORT_EN_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 4.0, sf );


    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_SHORT_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_XTR_SHORT_EN_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_SHORT_EN_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 2.0, sf );
    

    TEST_ASSERT_TRUE( dut.functions->setSensitivity(&dut, TLx493D_FULL_RANGE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_XTR_SHORT_EN_e) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_SHORT_EN_e) );

    sf = dut.functions->getSensitivityScaleFactor(&dut);
    TEST_ASSERT_EQUAL_FLOAT( 1.0, sf );
}


// Check if setDefaultConfig worked properly and data can be read and expected values are set.
TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkModeDefaultConfigFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    TEST_ASSERT_EQUAL_HEX8( 0x62, dut.regMap[P3I8_MOD1_REG_e] );
    TEST_ASSERT_EQUAL_HEX8( 0x00, dut.regMap[P3I8_MOD2_REG_e] );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkModeInterruptFunctionality)
{
    // TEST_ASSERT_TRUE( dut.functions->enableInterrupt(&dut) );
    // TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_INT_DIS_e) );

    TEST_ASSERT_TRUE( dut.functions->disableInterrupt(&dut) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_INT_DIS_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkModePowerModeFunctionality)
{
    // Unsupported
    TEST_ASSERT_FALSE( dut.functions->setPowerMode(&dut, TLx493D_FAST_MODE_e) );


    // Supported
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_MASTER_CONTROLLED_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );


    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkModeUpdateRateFunctionality)
{
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );

    // Supported
    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_125_HZ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b01, tlx493d_common_returnBitfield(&dut, P3I8_F_UPDATE_SEL_e) );

    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_31_HZ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b10, tlx493d_common_returnBitfield(&dut, P3I8_F_UPDATE_SEL_e) );

    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_16_HZ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b11, tlx493d_common_returnBitfield(&dut, P3I8_F_UPDATE_SEL_e) );

    TEST_ASSERT_TRUE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_1000_HZ_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegistersAndCheck(&dut));
    TEST_ASSERT_EQUAL_HEX8( 0b00, tlx493d_common_returnBitfield(&dut, P3I8_F_UPDATE_SEL_e) );


    // Unsupported
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_97_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_24_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_12_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_6_HZ_e) );

    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_3_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_0_4_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_0_05_HZ_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_770_HZ_e) );

    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_SLOW_e) );
    TEST_ASSERT_FALSE( dut.functions->setUpdateRate(&dut, TLx493D_UPDATE_RATE_FAST_e) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkWakeUpSettingsFunctionality)
{
    // Valid only in LPM
    TEST_ASSERT_TRUE( dut.functions->setPowerMode(&dut, TLx493D_LOW_POWER_MODE_e) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x00, tlx493d_common_returnBitfield(&dut, P3I8_MODE_SEL_e) );


    TEST_ASSERT_TRUE( dut.functions->disableWakeUpMode(&dut) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut) );
    TEST_ASSERT_FALSE( dut.functions->isWakeUpEnabled(&dut) );
    TEST_ASSERT_EQUAL_HEX8( 0x01, tlx493d_common_returnBitfield(&dut, P3I8_INT_DIS_e) );

    // Not safely testable
    // TEST_ASSERT_TRUE( dut.functions->enableWakeUpMode(&dut) );
    // TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));
    // TEST_ASSERT_TRUE( dut.functions->isWakeUpEnabled(&dut) );
    // TEST_ASSERT_TRUE( dut.functions->disableWakeUpMode(&dut) );
}


TEST_IFX(TLx493D_P3I8_needsSensorInternal, checkWakeUpThresholdFunctionality)
{
    // pos. numbers
                                                              //   xlTh,         xhTh,        ylTh,        yhTh,        zlTh,        zhTh);
    TEST_ASSERT_TRUE( dut.functions->setWakeUpThresholdsAsInteger(&dut, 0x0ABC >> 2, 0x00BC >> 2, 0x000C >> 2, 0x0FBC >> 2, 0x0F0C >> 2, 0x0F00 >> 2) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    // threshold 10 bits explicit (+ 2 implicit set to 0)
    // MSBs
    TEST_ASSERT_EQUAL_HEX8( 0x0ABC >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_MSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( 0x00BC >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_MSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( 0x000C >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_MSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( 0x0FBC >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_MSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( 0x0F0C >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_MSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( 0x0F00 >> 4, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_MSBS_e) ); // ZH

    // LSBs
    TEST_ASSERT_EQUAL_HEX8( (0x0ABC >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_LSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( (0x00BC >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_LSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( (0x000C >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_LSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( (0x0FBC >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_LSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( (0x0F0C >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_LSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( (0x0F00 >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_LSBS_e) ); // ZH


    // // neg. numbers in hex format
    TEST_ASSERT_TRUE( dut.functions->setWakeUpThresholdsAsInteger(&dut, ((int16_t) 0x8ABC) >> 2, ((int16_t) 0x80BC) >> 2, ((int16_t) 0x800C) >> 2,
                                                                        ((int16_t) 0x8FBC) >> 2, ((int16_t) 0x8F0C) >> 2, ((int16_t) 0x8F00) >> 2) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    // MSBs
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8ABC) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_MSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x80BC) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_MSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x800C) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_MSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8FBC) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_MSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8F0C) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_MSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8F00) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_MSBS_e) ); // ZH

    // LSBs
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8ABC) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_LSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x80BC) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_LSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x800C) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_LSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8FBC) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_LSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8F0C) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_LSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) 0x8F00) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_LSBS_e) ); // ZH


    // neg. numbers in int format
    TEST_ASSERT_TRUE( dut.functions->setWakeUpThresholdsAsInteger(&dut, -1 >> 2, -2 >> 2, -16 >> 2, -100 >> 2, -256 >> 2, -1024 >> 2) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    // MSBs
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -1) >> 4) & 0xFF,    tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_MSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -2) >> 4) & 0xFF,    tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_MSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -16) >> 4) & 0xFF,   tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_MSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -100) >> 4) & 0xFF,  tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_MSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -256) >> 4) & 0xFF,  tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_MSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -1024) >> 4) & 0xFF, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_MSBS_e) ); // ZH

    // LSBs
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -1) >> 2) & 0x03,    tlx493d_common_returnBitfield(&dut, P3I8_WU_XL_LSBS_e) ); // XL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -2) >> 2) & 0x03,    tlx493d_common_returnBitfield(&dut, P3I8_WU_XH_LSBS_e) ); // XH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -16) >> 2) & 0x03,   tlx493d_common_returnBitfield(&dut, P3I8_WU_YL_LSBS_e) ); // YL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -100) >> 2) & 0x03,  tlx493d_common_returnBitfield(&dut, P3I8_WU_YH_LSBS_e) ); // YH
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -256) >> 2) & 0x03,  tlx493d_common_returnBitfield(&dut, P3I8_WU_ZL_LSBS_e) ); // ZL
    TEST_ASSERT_EQUAL_HEX8( (((int16_t) -1024) >> 2) & 0x03, tlx493d_common_returnBitfield(&dut, P3I8_WU_ZH_LSBS_e) ); // ZH


    TEST_ASSERT_TRUE( dut.functions->setWakeUpThresholds(&dut, 25.0, -5.0, 5.0, -5.0, 5.0, -5.0, 5.0) );
    TEST_ASSERT_TRUE( dut.functions->readRegisters(&dut));

    int16_t th    = 0;
    uint8_t delta = 2;

    // X
    tlx493d_common_concatBytes(&dut, P3I8_WU_XL_MSBS_e, P3I8_WU_XL_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, -153,  th ); // XL

    tlx493d_common_concatBytes(&dut, P3I8_WU_XH_MSBS_e, P3I8_WU_XH_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, 154,  th ); // XH

    // Y
    tlx493d_common_concatBytes(&dut, P3I8_WU_YL_MSBS_e, P3I8_WU_YL_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, -152,  th ); // YL

    tlx493d_common_concatBytes(&dut, P3I8_WU_YH_MSBS_e, P3I8_WU_YH_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, 155,  th ); // YH

    // Z
    tlx493d_common_concatBytes(&dut, P3I8_WU_ZL_MSBS_e, P3I8_WU_ZL_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, -151,  th ); // ZL

    tlx493d_common_concatBytes(&dut, P3I8_WU_ZH_MSBS_e, P3I8_WU_ZH_LSBS_e, &th);
    TEST_ASSERT_INT16_WITHIN( delta, 152,  th ); // ZH
}


static TEST_GROUP_RUNNER(TLx493D_P3I8_needsSensorInternal)
{
    // First test default config applied in runner setup method 
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkModeDefaultConfigFunctionality);

    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkSupportedFunctionality);

    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkBasicFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkGetMagneticFieldAndTemperature);

    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkConfigMeasurementFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkConfigTriggerFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkConfigSensitivityFunctionality);

    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkModeInterruptFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkModePowerModeFunctionality);

    // MOD2
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkModeUpdateRateFunctionality);

    // WakeUp functionality
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkWakeUpSettingsFunctionality);
    RUN_TEST_CASE(TLx493D_P3I8_needsSensorInternal, checkWakeUpThresholdFunctionality);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(TLx493D_P3I8_needsSensor)
{
    TLx493D_P3I8_needsSensor_suiteSetup();

    RUN_TEST_GROUP(TLx493D_P3I8_needsSensorInternal);
     
    // run common functions tests
    RUN_TEST_GROUP(SensorsCommonFunctions);

    // run gen 3 common functions tests
    RUN_TEST_GROUP(SensorsGen3Common);
    RUN_TEST_GROUP(SensorsCommon);

    TLx493D_P3I8_needsSensor_suiteTearDown();
}
