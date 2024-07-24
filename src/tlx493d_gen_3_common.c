/** std includes. */
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

/** project c includes. */
#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"
#include "CommunicationInterface.h"
#include "Logger.h"

#include "tlx493d_gen_3_common_defines.h"
#include "tlx493d_gen_3_common.h"


static void tlx493d_gen_3_shiftDataInRegisters(TLx493D_t *sensor, uint8_t channelSaveBF) {
    uint8_t channel = tlx493d_common_returnBitfield(sensor, channelSaveBF);

    uint8_t offset = 0;

    switch(channel) {
        /** TLx493D_BxTemp_e */
        case 0b1100 : offset = 2;
                      break;

        /** TLx493D_BxBy_e */
        case 0b1101 : offset = 4;
                      break;
        
        /** TLx493D_BzTemp_e */
        case 0b1110 : offset = 0;
                      break;
        
        default : return;
    }

    uint8_t regCopy[sensor->regMapSize];
    (void) memcpy(regCopy, sensor->regMap, sensor->regMapSize);
    (void) memcpy(sensor->regMap + offset + 4, regCopy + offset, (size_t) (sensor->regMapSize - offset - 4));
    (void) memset(sensor->regMap + offset, 0, 4);
}


bool tlx493d_gen_3_readRegisters(TLx493D_t *sensor, uint8_t channelSaveBF) {
    bool b = tlx493d_common_readRegisters(sensor);
    tlx493d_gen_3_shiftDataInRegisters(sensor, channelSaveBF);
    return b;
}


bool tlx493d_gen_3_readRegistersAndCheck(TLx493D_t *sensor, uint8_t channelSaveBF) {
    bool b = tlx493d_common_readRegistersAndCheck(sensor);
    tlx493d_gen_3_shiftDataInRegisters(sensor, channelSaveBF);
    return b;
}


void tlx493d_gen_3_calculateRawTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, int16_t *temperature) {
    tlx493d_common_calculateRawTemperature(sensor, tempMSBBF, tempLSBBF, temperature);
}


void tlx493d_gen_3_calculateRawMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                             uint8_t bzMSBBF, uint8_t bzLSBBF, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_common_calculateRawMagneticField(sensor, bxMSBBF, bxLSBBF, byMSBBF, byLSBBF, bzMSBBF, bzLSBBF, x, y, z);
}


void tlx493d_gen_3_calculateTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, double *temperature) {
    int16_t value = 0;
    tlx493d_common_concatBytes(sensor, tempMSBBF, tempLSBBF, &value);
    *temperature = (((double) value - GEN_3_TEMP_OFFSET) / GEN_3_TEMP_SENSITIVITY) + GEN_3_TEMP_REF;
}


void tlx493d_gen_3_calculateMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                          uint8_t bzMSBBF, uint8_t bzLSBBF, uint8_t tempMSBBF, uint8_t tempLSBBF,
                                          double *x, double *y, double *z) {
    int16_t valueX = 0;
    int16_t valueY = 0;
    int16_t valueZ = 0;

    tlx493d_common_concatBytes(sensor, bxMSBBF, bxLSBBF, &valueX);
    tlx493d_common_concatBytes(sensor, byMSBBF, byLSBBF, &valueY);
    tlx493d_common_concatBytes(sensor, bzMSBBF, bzLSBBF, &valueZ);

    double sf = sensor->functions->getSensitivityScaleFactor(sensor);

    int16_t rawTemp;
    tlx493d_gen_3_calculateRawTemperature(sensor, tempMSBBF, tempLSBBF, &rawTemp);
    double temp = (double) rawTemp;

    *x = ((GEN_3_O0x + temp * (GEN_3_O1x + temp * (GEN_3_O2x + temp * GEN_3_O3x)))
          + ((double) valueX) * (GEN_3_L0x + temp * (GEN_3_L1x + temp * (GEN_3_L2x + temp * GEN_3_L3x))) / sf)
       / GEN_3_FULL_RANGE_FIELD_SENSITIVITY;

    *y = ((GEN_3_O0y + temp * (GEN_3_O1y + temp * (GEN_3_O2y + temp * GEN_3_O3y)))
          + ((double) valueY) * (GEN_3_L0y + temp * (GEN_3_L1y + temp * (GEN_3_L2y + temp * GEN_3_L3y))) / sf)
       / GEN_3_FULL_RANGE_FIELD_SENSITIVITY;

    *z = ((GEN_3_O0z + temp * (GEN_3_O1z + temp * (GEN_3_O2z + temp * GEN_3_O3z)))
          + ((double) valueZ) * (GEN_3_L0z + temp * (GEN_3_L1z + temp * (GEN_3_L2z + temp * GEN_3_L3z))) / sf)
       / GEN_3_FULL_RANGE_FIELD_SENSITIVITY;


/*
    double sensitivity = sf * GEN_3_FULL_RANGE_FIELD_SENSITIVITY;
    double r    = sf;

    *x = (r * (GEN_3_O0x + temp * (GEN_3_O1x + temp * (GEN_3_O2x + temp * GEN_3_O3x)))
            + ((double) valueX) * (GEN_3_L0x + temp * (GEN_3_L1x + temp * (GEN_3_L2x + temp * GEN_3_L3x))))
        / sensitivity;

    *y = (r * (GEN_3_O0y + temp * (GEN_3_O1y + temp * (GEN_3_O2y + temp * GEN_3_O3y)))
            + ((double) valueY) * (GEN_3_L0y + temp * (GEN_3_L1y + temp * (GEN_3_L2y + temp * GEN_3_L3y))))
        / sensitivity;

    *z = (r * (GEN_3_O0z + temp * (GEN_3_O1z + temp * (GEN_3_O2z + temp * GEN_3_O3z)))
            + ((double) valueZ) * (GEN_3_L0z + temp * (GEN_3_L1z + temp * (GEN_3_L2z + temp * GEN_3_L3z))))
        / sensitivity;
*/
}


bool tlx493d_gen_3_setMeasurement(TLx493D_t *sensor, uint8_t channelBF, uint8_t channelSaveBF, TLx493D_MeasurementType_t val) {
    uint8_t channel = 0;

    switch(val) {
        case TLx493D_BxByBzTemp_e : channel = 0b0000;
                                    break;

/*
        case TLx493D_VHall_Bias_e : channel = 0b0001;
                                    break;
        
        case TLx493D_Spintest_e : channel = 0b0010;
                                  break;

        case TLx493D_SAT_test_e : channel = 0b1000;
                                  break;
*/

        case TLx493D_BxTemp_e : channel = 0b1100;
                                break;

        case TLx493D_BxBy_e : channel = 0b1101;
                              break;
        
        case TLx493D_BzTemp_e : channel = 0b1110;
                                break;
        
        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_MeasurementType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, channelBF, channel);
    tlx493d_common_setBitfield(sensor, channelSaveBF, channel);

    return tlx493d_common_writeRegister(sensor, channelBF);
}


/** This option depends on PR and MODE. */
bool tlx493d_gen_3_setTrigger(TLx493D_t *sensor, uint8_t trigBF, TLx493D_TriggerType_t val) {
    uint8_t trig = 0;

    switch(val) {
        case TLx493D_NO_TRIGGER_e : trig = 0b00;
                                    break;

        case TLx493D_ADC_ON_READ_e : trig = 0b01;
                                     break;
        
        case TLx493D_ADC_ON_STOP_CONDITION_e : trig = 0b10;
                                               break;
        
        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_TriggerType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, trigBF, trig);

    return tlx493d_common_writeRegister(sensor, trigBF);
}


bool tlx493d_gen_3_setSensitivity(TLx493D_t *sensor, uint8_t shortBF, uint8_t xtrShortBF, TLx493D_SensitivityType_t val) {
    uint8_t shortVal      = 0;
    uint8_t extraShortVal = 0;

    switch(val) {
        case TLx493D_FULL_RANGE_e : shortVal      = 0;
                                    extraShortVal = 0;
                                    break;

        case TLx493D_SHORT_RANGE_e : shortVal      = 1;
                                     extraShortVal = 0;
                                     break;

        case TLx493D_EXTRA_SHORT_RANGE_e : shortVal      = 0;
                                           extraShortVal = 1;
                                           break;
        
        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_SensitivityType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, shortBF, shortVal);
    tlx493d_common_setBitfield(sensor, xtrShortBF, extraShortVal);

    return tlx493d_common_writeRegister(sensor, shortBF);
}


bool tlx493d_gen_3_setDefaultConfig(TLx493D_t *sensor, uint8_t caBF, uint8_t intBF) {
    tlx493d_common_setBitfield(sensor, caBF, 0);
    tlx493d_common_setBitfield(sensor, intBF, 1);
    return sensor->functions->enable1ByteReadMode(sensor);
}


bool tlx493d_gen_3_setIICAddress(const TLx493D_t *sensor, uint8_t iicadrBF, TLx493D_IICAddressType_t addr) {
    (void) addr;
    (void) iicadrBF;
    (void) addr;
    
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setIICAddress");
    return false;
}


bool tlx493d_gen_3_set1ByteReadMode(TLx493D_t *sensor, uint8_t prBF, uint8_t pr) {
    tlx493d_common_setBitfield(sensor, prBF, pr);
    return tlx493d_common_writeRegister(sensor, prBF);
}


bool tlx493d_gen_3_setCollisionAvoidance(TLx493D_t *sensor, uint8_t caBF, uint8_t ca) {
    tlx493d_common_setBitfield(sensor, caBF, ca);
    return tlx493d_common_writeRegister(sensor, caBF);
}


bool tlx493d_gen_3_setInterrupt(TLx493D_t *sensor, uint8_t intBF, uint8_t irq) {
    tlx493d_common_setBitfield(sensor, intBF, irq);
    return tlx493d_common_writeRegister(sensor, intBF);
}


bool tlx493d_gen_3_setPowerMode(TLx493D_t *sensor, uint8_t modeBF, TLx493D_PowerModeType_t val) {
    uint8_t mode = 0;

    switch(val) {
        case TLx493D_LOW_POWER_MODE_e : mode = 0b0;
                                        break;

        case TLx493D_MASTER_CONTROLLED_MODE_e : mode = 0b1;
                                                break;

        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_PowerModeType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, modeBF, mode);
    return tlx493d_common_writeRegister(sensor, modeBF);
}


bool tlx493d_gen_3_setUpdateRate(TLx493D_t *sensor, uint8_t fUpdateBF, TLx493D_UpdateRateType_t val) {
    uint8_t rate = 0;

    switch(val) {
        case TLx493D_UPDATE_RATE_1000_HZ_e : rate = 0b00;
                                             break;

        case TLx493D_UPDATE_RATE_125_HZ_e : rate = 0b01;
                                            break;

        case TLx493D_UPDATE_RATE_31_HZ_e : rate = 0b10;
                                           break;

        case TLx493D_UPDATE_RATE_16_HZ_e : rate = 0b11;
                                           break;

        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_UpdateRateType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, fUpdateBF, rate);
    return tlx493d_common_writeRegister(sensor, fUpdateBF);
}


bool tlx493d_gen_3_hasValidData(const TLx493D_t *sensor, uint8_t measBF) {
    return tlx493d_common_returnBitfield(sensor, measBF) != 0U;

/*
    return !sensor->functions->isInTestMode(sensor) && (tlx493d_common_returnBitfield(sensor, measBF) != 0);
*/
}


bool tlx493d_gen_3_isFunctional(const TLx493D_t *sensor) {
    return sensor->functions->hasValidFuseParity(sensor);
}


bool tlx493d_gen_3_isWakeUpEnabled(const TLx493D_t *sensor, uint8_t wuBF) {
    return tlx493d_common_returnBitfield(sensor, wuBF) != 0U;
}


bool tlx493d_gen_3_enableWakeUpMode(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF) {
    bool b = true;

    if( sensor->functions->isInTestMode(sensor) ) {
        logWarn("Sensor %s was in test mode, changed to normal mode in order to enable wake up !", tlx493d_common_getTypeAsString(sensor));
        b &= sensor->functions->setMeasurement(sensor, TLx493D_BxByBzTemp_e);
    }

    tlx493d_common_setBitfield(sensor, wuBF, 1);
    tlx493d_common_setBitfield(sensor, wucpBF, 1);
    b &= tlx493d_gen_3_setWakeUpParity(sensor, wuBF, wupBF);
    b &= sensor->functions->readRegisters(sensor);

    if( ! sensor->functions->hasValidWakeUpParity(sensor) ) {
        logError("Wake up parity is not correct, cannot enter wake up mode for sensor %s !", tlx493d_common_getTypeAsString(sensor));
        return false;
    }

    return b;
}


bool tlx493d_gen_3_disableWakeUpMode(TLx493D_t *sensor, uint8_t intBF, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF) {
    tlx493d_common_setBitfield(sensor, wuBF, 0);
    tlx493d_common_setBitfield(sensor, wucpBF, 0);
    bool b = tlx493d_gen_3_setWakeUpParity(sensor, wuBF, wupBF);

    return b && tlx493d_gen_3_setInterrupt(sensor, intBF, 1);
}


bool tlx493d_gen_3_writeWakeupParityRelatedRegisters(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF) {
    tlx493d_common_setBitfield(sensor, wucpBF, tlx493d_common_returnBitfield(sensor, wuBF));
    tlx493d_common_setBitfield(sensor, wupBF, tlx493d_gen_3_calculateWakeUpParity(sensor, wuBF));

    uint8_t txBuffer[9] = {
                              0x0C,
                              sensor->regMap[0x0C],
                              sensor->regMap[0x0D],
                              sensor->regMap[0x0E],
                              sensor->regMap[0x0F],
                              sensor->regMap[0x10],
                              sensor->regMap[0x11],
                              sensor->regMap[0x12],
                              sensor->regMap[0x13],
                           };

    return tlx493d_transfer(sensor, txBuffer, sizeof(txBuffer), NULL, 0);
}


bool tlx493d_gen_3_setThreshold(TLx493D_t *sensor, uint8_t msbsBF, uint8_t lsbsBF, int16_t threshold10Bits) {
    const TLx493D_Register_t *msbs = &sensor->regDef[msbsBF];
    const TLx493D_Register_t *lsbs = &sensor->regDef[lsbsBF];

    uint8_t lower = (uint8_t) (((uint8_t) threshold10Bits) & (lsbs->mask >> lsbs->offset));
    uint8_t upper = (uint8_t) (((uint8_t) (threshold10Bits >> lsbs->numBits)) & (msbs->mask >> msbs->offset));

    tlx493d_common_setBitfield(sensor, msbsBF, upper);
    tlx493d_common_setBitfield(sensor, lsbsBF, lower);

    return true;
}


bool tlx493d_gen_3_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF,
                                                uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                                uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                                uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                                int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    bool retVal = tlx493d_gen_3_setThreshold(sensor, xlMSBBF, xlLSBBF, xlTh);
    retVal &= tlx493d_gen_3_setThreshold(sensor, xhMSBBF, xhLSBBF, xhTh);

    retVal &= tlx493d_gen_3_setThreshold(sensor, ylMSBBF, ylLSBBF, ylTh);
    retVal &= tlx493d_gen_3_setThreshold(sensor, yhMSBBF, yhLSBBF, yhTh);

    retVal &= tlx493d_gen_3_setThreshold(sensor, zlMSBBF, zlLSBBF, zlTh);
    retVal &= tlx493d_gen_3_setThreshold(sensor, zhMSBBF, zhLSBBF, zhTh);

    retVal &= tlx493d_gen_3_writeWakeupParityRelatedRegisters(sensor, wuBF, wucpBF, wupBF);

    return retVal;
}


bool tlx493d_gen_3_setWakeUpThresholds(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF,
                                       uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                       uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                       uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                       uint8_t x2BF, uint8_t x4BF,
                                       double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
    int16_t xlTh;
    int16_t ylTh;
    int16_t zlTh;
    int16_t xhTh;
    int16_t yhTh;
    int16_t zhTh;
    int16_t tr;

    tlx493d_gen_3_convertTemperatureToRaw(sensor, temperature, &tr);

    TLx493D_SensitivityType_t sens = tlx493d_gen_3_getSensitivityType(sensor, x2BF, x4BF);

    sensor->functions->calculateRawMagneticFieldAtTemperature(sensor, tr, sens, xLow,  yLow,  zLow,  &xlTh, &ylTh, &zlTh);
    sensor->functions->calculateRawMagneticFieldAtTemperature(sensor, tr, sens, xHigh, yHigh, zHigh, &xhTh, &yhTh, &zhTh);
/** logPrint("sens = %d\n", sens); */
/** logPrintDouble(temperature); */
/** logPrint("\nt = %d\n", tr); */
/** logPrint("xl = %d   xh = %d\n", xlTh, xhTh); */
/** logPrint("yl = %d   yh = %d\n", ylTh, yhTh); */
/** logPrint("zl = %d   zh = %d\n", zlTh, zhTh); */

    return tlx493d_gen_3_setWakeUpThresholdsAsInteger(sensor, wuBF, wucpBF, wupBF,
                                                      xlMSBBF, xlLSBBF, xhMSBBF, xhLSBBF,
                                                      ylMSBBF, ylLSBBF, yhMSBBF, yhLSBBF,
                                                      zlMSBBF, zlLSBBF, zhMSBBF, zhLSBBF,
                                                      xlTh, xhTh, ylTh, yhTh, zlTh, zhTh);
}


bool tlx493d_gen_3_softwareReset(TLx493D_t *sensor, uint8_t resetBF) {
   tlx493d_common_setBitfield(sensor, resetBF, 1);
   return tlx493d_common_writeRegister(sensor, resetBF);
}


bool tlx493d_gen_3_setWakeUpParity(TLx493D_t *sensor, uint8_t wuBF, uint8_t wupBF) {
   tlx493d_common_setBitfield(sensor, wupBF, tlx493d_gen_3_calculateWakeUpParity(sensor, wuBF));
   return tlx493d_common_writeRegister(sensor, wupBF);
}


uint8_t tlx493d_gen_3_calculateWakeUpParity(const TLx493D_t *sensor, uint8_t wuBF) {
    const TLx493D_Register_t *wu     = &sensor->regDef[wuBF];
	uint8_t                   parity = sensor->regMap[wu->address] & wu->mask;

    for(uint8_t i = 0x0CU; i <= 0x12U; ++i) {
        parity ^= sensor->regMap[i];
    }

    parity = (uint8_t) (parity ^ (sensor->regMap[0x13] & 0x0FU));

	return tlx493d_common_getOddParity(tlx493d_common_calculateParity(parity));
}


bool tlx493d_gen_3_hasValidFuseParity(const TLx493D_t *sensor, uint8_t fpfBF) {
    return tlx493d_common_returnBitfield(sensor, fpfBF) != 0U;
}


bool tlx493d_gen_3_hasValidWakeUpParity(const TLx493D_t *sensor, uint8_t wupBF) {
    return tlx493d_common_returnBitfield(sensor, wupBF) != 0U;
}


bool tlx493d_gen_3_isInTestMode(const TLx493D_t *sensor, uint8_t testBF) {
    return tlx493d_common_returnBitfield(sensor, testBF) != 0U;
}


/*
bool tlx493d_gen_3_hasValidIICadr(TLx493D_t *sensor, uint8_t idBF, uint8_t iicAdrBF) {
    return tlx493d_common_returnBitfield(idBF) == tlx493d_common_returnBitfield(iicAdrBF);
}
*/

uint8_t tlx493d_gen_3_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    switch(addr) {
        case TLx493D_IIC_ADDR_A0_e : return GEN_3_STD_IIC_ADDR_WRITE_A0;

        case TLx493D_IIC_ADDR_A1_e : return GEN_3_STD_IIC_ADDR_WRITE_A1;

        case TLx493D_IIC_ADDR_A2_e : return GEN_3_STD_IIC_ADDR_WRITE_A2;

        case TLx493D_IIC_ADDR_A3_e : return GEN_3_STD_IIC_ADDR_WRITE_A3;

        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, addr, "TLx493D_IICAddressType_t");
                  return 0;
    }
}


double tlx493d_gen_3_getSensitivityScaleFactor(const TLx493D_t *sensor, TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF) {
    switch(availSens) {
        case TLx493D_HAS_X4_e : {
                                    bool x2IsSet = tlx493d_common_returnBitfield(sensor, x2BF) != 0U;
                                    bool x4IsSet = tlx493d_common_returnBitfield(sensor, x4BF) != 0U;

                                    return x2IsSet ? 2.0 : (x4IsSet ? 4.0 : 1.0);
        }
    
        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, availSens, "TLx493D_AvailableSensitivityType_t");
                  return 0.0;
    }
}


static double tlx493d_gen_3_getSensitivityScaleFactorFromSensitivity(const TLx493D_SensitivityType_t sens) {
    return (sens == TLx493D_FULL_RANGE_e) ? 1.0
                                        : ((sens == TLx493D_SHORT_RANGE_e) ? 2.0 : 4.0);
}


void tlx493d_gen_3_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                          double xInmT, double yInmT, double zInmT,
                                                          int16_t *x, int16_t *y, int16_t *z) {
    (void) sensor;

    double sf   = tlx493d_gen_3_getSensitivityScaleFactorFromSensitivity(sens);
    double temp = (double) rawTemp;

    *x = (int16_t) lround(((xInmT * GEN_3_FULL_RANGE_FIELD_SENSITIVITY - (GEN_3_O0x + temp * (GEN_3_O1x + temp * (GEN_3_O2x + temp * GEN_3_O3x))))
                         / ((GEN_3_L0x + temp * (GEN_3_L1x + temp * (GEN_3_L2x + temp * GEN_3_L3x))) / sf)));

    *y = (int16_t) lround((yInmT * GEN_3_FULL_RANGE_FIELD_SENSITIVITY - (GEN_3_O0y + temp * (GEN_3_O1y + temp * (GEN_3_O2y + temp * GEN_3_O3y))))
                         / ((GEN_3_L0y + temp * (GEN_3_L1y + temp * (GEN_3_L2y + temp * GEN_3_L3y))) / sf));

    *z = (int16_t) lround((zInmT * GEN_3_FULL_RANGE_FIELD_SENSITIVITY - (GEN_3_O0z + temp * (GEN_3_O1z + temp * (GEN_3_O2z + temp * GEN_3_O3z))))
                         / ((GEN_3_L0z + temp * (GEN_3_L1z + temp * (GEN_3_L2z + temp * GEN_3_L3z))) / sf));
}


void tlx493d_gen_3_convertTemperatureToRaw(const TLx493D_t *sensor, double temperature, int16_t *rawTemperature) {
    (void) sensor;

    *rawTemperature = (int16_t) lround((temperature - GEN_3_TEMP_REF) * GEN_3_TEMP_SENSITIVITY + GEN_3_TEMP_OFFSET);

}


TLx493D_SensitivityType_t tlx493d_gen_3_getSensitivityType(const TLx493D_t *sensor, uint8_t x2BF, uint8_t x4BF) {
    bool x2IsSet = tlx493d_common_returnBitfield(sensor, x2BF) != 0U;
    bool x4IsSet = tlx493d_common_returnBitfield(sensor, x4BF) != 0U;

    return x2IsSet ? TLx493D_SHORT_RANGE_e : (x4IsSet ? TLx493D_EXTRA_SHORT_RANGE_e : TLx493D_FULL_RANGE_e);
}
