/** std includes. */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** project c includes. */
#include "CommunicationInterface.h"
#include "Logger.h"

#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"

#include "tlx493d_gen_2_common_defines.h"
#include "tlx493d_gen_2_common.h"

/** sensor specicifc includes. */
#include "TLx493D_A2BW_defines.h"
#include "TLx493D_A2BW_enums.h"
#include "TLx493D_A2BW.h"


static TLx493D_Register_t TLx493D_A2BW_regDef[] = {
    { /* A2BW_BX_MSBS_e, */    TLx493D_READ_MODE_e,         0x00,   0xFF,   0,  8 },
    { /* A2BW_BY_MSBS_e, */    TLx493D_READ_MODE_e,         0x01,   0xFF,   0,  8 },
    { /* A2BW_BZ_MSBS_e, */    TLx493D_READ_MODE_e,         0x02,   0xFF,   0,  8 },
    { /* A2BW_TEMP_MSBS_e, */  TLx493D_READ_MODE_e,         0x03,   0xFF,   0,  8 },
    { /* A2BW_BX_LSBS_e, */    TLx493D_READ_MODE_e,         0x04,   0xF0,   4,  4 },
    { /* A2BW_BY_LSBS_e, */    TLx493D_READ_MODE_e,         0x04,   0x0F,   0,  4 },
    { /* A2BW_TEMP_LSBS_e, */  TLx493D_READ_MODE_e,         0x05,   0xC0,   6,  2 },
    { /* A2BW_ID_e, */         TLx493D_READ_MODE_e,         0x05,   0x30,   4,  2 },
    { /* A2BW_BZ_LSBS_e, */    TLx493D_READ_MODE_e,         0x05,   0x0F,   0,  4 },
    { /* A2BW_P_e, */          TLx493D_READ_MODE_e,         0x06,   0x80,   7,  1 },
    { /* A2BW_FF_e, */         TLx493D_READ_MODE_e,         0x06,   0x40,   6,  1 },
    { /* A2BW_CF_e, */         TLx493D_READ_MODE_e,         0x06,   0x20,   5,  1 },
    { /* A2BW_T_e, */          TLx493D_READ_MODE_e,         0x06,   0x10,   4,  1 },
    { /* A2BW_PD3_e, */        TLx493D_READ_MODE_e,         0x06,   0x08,   3,  1 },
    { /* A2BW_PD0_e, */        TLx493D_READ_MODE_e,         0x06,   0x04,   2,  1 },
    { /* A2BW_FRM_e, */        TLx493D_READ_MODE_e,         0x06,   0x03,   0,  2 },
    { /* A2BW_DT_e, */         TLx493D_READ_WRITE_MODE_e,   0x10,   0x80,   7,  1 },
    { /* A2BW_AM_e, */         TLx493D_READ_WRITE_MODE_e,   0x10,   0x40,   6,  1 },
    { /* A2BW_TRIG_e, */       TLx493D_READ_WRITE_MODE_e,   0x10,   0x30,   4,  2 },
    { /* A2BW_X2_e, */         TLx493D_READ_WRITE_MODE_e,   0x10,   0x08,   3,  1 },
    { /* A2BW_TL_MAG_e, */     TLx493D_READ_WRITE_MODE_e,   0x10,   0x06,   1,  2 },
    { /* A2BW_CP_e, */         TLx493D_READ_WRITE_MODE_e,   0x10,   0x01,   0,  1 },
    { /* A2BW_FP_e, */         TLx493D_READ_WRITE_MODE_e,   0x11,   0x80,   7,  1 },
    { /* A2BW_IICADR_e, */     TLx493D_READ_WRITE_MODE_e,   0x11,   0x60,   5,  2 },
    { /* A2BW_PR_e, */         TLx493D_READ_WRITE_MODE_e,   0x11,   0x10,   4,  1 },
    { /* A2BW_CA_e, */         TLx493D_READ_WRITE_MODE_e,   0x11,   0x08,   3,  1 },
    { /* A2BW_INT_e, */        TLx493D_READ_WRITE_MODE_e,   0x11,   0x04,   2,  1 },
    { /* A2BW_MODE_e, */       TLx493D_READ_WRITE_MODE_e,   0x11,   0x03,   0,  2 },
    { /* A2BW_PRD_e, */        TLx493D_READ_WRITE_MODE_e,   0x13,   0x80,   7,  1 },
    { /* A2BW_X4_e, */         TLx493D_WRITE_MODE_e,        0x14,   0x01,   0,  1 },
    { /* A2BW_TYPE_e, */       TLx493D_READ_MODE_e,         0x16,   0x30,   4,  2 },
    { /* A2BW_HWV_e, */        TLx493D_READ_MODE_e,         0x16,   0x0F,   0,  4 },

    /* From here on write-only fields are listed. These are not part of the registers set !*/
    { /* A2BW_X4_READWRITE_e, */    TLx493D_READ_WRITE_MODE_e,   0x17,   0x01,   0,  1 },
};


static TLx493D_CommonFunctions_t TLx493D_A2BW_commonFunctions = {
    .init                           = TLx493D_A2BW_init,
    .deinit                         = TLx493D_A2BW_deinit,

    .readRegisters                  = TLx493D_A2BW_readRegisters,
    .readRegistersAndCheck          = TLx493D_A2BW_readRegistersAndCheck,

    .calculateRawTemperature        = TLx493D_A2BW_calculateRawTemperature,
    .getRawTemperature              = TLx493D_A2BW_getRawTemperature,

    .calculateRawMagneticField      = TLx493D_A2BW_calculateRawMagneticField,
    .getRawMagneticField            = TLx493D_A2BW_getRawMagneticField,

    .calculateRawMagneticFieldAndTemperature = TLx493D_A2BW_calculateRawMagneticFieldAndTemperature,
    .getRawMagneticFieldAndTemperature       = TLx493D_A2BW_getRawMagneticFieldAndTemperature,

    .calculateTemperature           = TLx493D_A2BW_calculateTemperature,
    .getTemperature                 = TLx493D_A2BW_getTemperature,
    
    .calculateMagneticField         = TLx493D_A2BW_calculateMagneticField,
    .getMagneticField               = TLx493D_A2BW_getMagneticField,
    
    .calculateMagneticFieldAndTemperature = TLx493D_A2BW_calculateMagneticFieldAndTemperature,
    .getMagneticFieldAndTemperature = TLx493D_A2BW_getMagneticFieldAndTemperature,

    /** functions related to the "Config" register. */
    .setMeasurement                 = TLx493D_A2BW_setMeasurement,
    .setTrigger                     = TLx493D_A2BW_setTrigger,
    .setSensitivity                 = TLx493D_A2BW_setSensitivity,

    /** functions related to the "Mod1" and "Mod2" registers. */
    .setDefaultConfig               = TLx493D_A2BW_setDefaultConfig,
    .setIICAddress                  = TLx493D_A2BW_setIICAddress,
    .enable1ByteReadMode            = TLx493D_A2BW_enable1ByteReadMode,

    .enableInterrupt                = TLx493D_A2BW_enableInterrupt,
    .disableInterrupt               = TLx493D_A2BW_disableInterrupt,

    .enableCollisionAvoidance       = TLx493D_A2BW_enableCollisionAvoidance,
    .disableCollisionAvoidance      = TLx493D_A2BW_disableCollisionAvoidance,

    .setPowerMode                   = TLx493D_A2BW_setPowerMode,
    .setUpdateRate                  = TLx493D_A2BW_setUpdateRate,

    /** functions related to the "Diag" register. */
    .hasValidData                   = TLx493D_A2BW_hasValidData,
    .isFunctional                   = TLx493D_A2BW_isFunctional,

    /** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
    .hasWakeUp                      = TLx493D_A2BW_hasWakeUp,
    .isWakeUpEnabled                = TLx493D_A2BW_isWakeUpEnabled,
    .enableWakeUpMode               = TLx493D_A2BW_enableWakeUpMode,
    .disableWakeUpMode              = TLx493D_A2BW_disableWakeUpMode,

    .setWakeUpThresholdsAsInteger   = TLx493D_A2BW_setWakeUpThresholdsAsInteger,
    .setWakeUpThresholds            = TLx493D_A2BW_setWakeUpThresholds,

    .softwareReset                  = TLx493D_A2BW_softwareReset,

    .printRegisters                 = TLx493D_A2BW_printRegisters,

    /** functions used internally and not accessible through the common interface. */
    .calculateFuseParity            = TLx493D_A2BW_calculateFuseParity,
    .calculateBusParity             = TLx493D_A2BW_calculateBusParity,
    .calculateConfigurationParity   = TLx493D_A2BW_calculateConfigurationParity,

    .hasValidFuseParity             = TLx493D_A2BW_hasValidFuseParity,
    .hasValidBusParity              = TLx493D_A2BW_hasValidBusParity,
    .hasValidConfigurationParity    = TLx493D_A2BW_hasValidConfigurationParity,
 
    .hasValidWakeUpParity           = TLx493D_A2BW_hasValidWakeUpParity,
    .isInTestMode                   = TLx493D_A2BW_isInTestMode,
    
    .hasValidTBit                   = TLx493D_A2BW_hasValidTBit,
    
    .setResetValues                 = TLx493D_A2BW_setResetValues,

    .selectIICAddress               = TLx493D_A2BW_selectIICAddress,

    .calculateRawMagneticFieldAtTemperature = TLx493D_A2BW_calculateRawMagneticFieldAtTemperature,

    .getSensitivityScaleFactor      = TLx493D_A2BW_getSensitivityScaleFactor,
};


bool TLx493D_A2BW_init(TLx493D_t *sensor) {
    return tlx493d_common_init(sensor, GEN_2_REG_MAP_SIZE, TLx493D_A2BW_regDef, &TLx493D_A2BW_commonFunctions, TLx493D_A2BW_e, TLx493D_I2C_e);
}


bool TLx493D_A2BW_deinit(TLx493D_t *sensor) {
    return tlx493d_common_deinit(sensor);
}


bool TLx493D_A2BW_readRegisters(TLx493D_t *sensor) {
    return tlx493d_common_readRegisters(sensor);
}


bool TLx493D_A2BW_readRegistersAndCheck(TLx493D_t *sensor) {
    return tlx493d_common_readRegistersAndCheck(sensor);
}


void TLx493D_A2BW_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    tlx493d_gen_2_calculateRawTemperature(sensor, A2BW_TEMP_MSBS_e, A2BW_TEMP_LSBS_e, temperature);
}


bool TLx493D_A2BW_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    return tlx493d_common_getRawTemperature(sensor, temperature);
}


void TLx493D_A2BW_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticField(sensor, A2BW_BX_MSBS_e, A2BW_BX_LSBS_e, A2BW_BY_MSBS_e, A2BW_BY_LSBS_e, A2BW_BZ_MSBS_e, A2BW_BZ_LSBS_e, x, y, z);
}


bool TLx493D_A2BW_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    return tlx493d_common_getRawMagneticField(sensor, x, y, z);
}


void TLx493D_A2BW_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    TLx493D_A2BW_calculateRawMagneticField(sensor, x, y, z);
    TLx493D_A2BW_calculateRawTemperature(sensor, temperature);
}


bool TLx493D_A2BW_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    return tlx493d_common_getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


void TLx493D_A2BW_calculateTemperature(TLx493D_t *sensor, double *temp) {
    tlx493d_gen_2_calculateTemperature(sensor, A2BW_TEMP_MSBS_e, A2BW_TEMP_LSBS_e, temp);
}

bool TLx493D_A2BW_getTemperature(TLx493D_t *sensor, double *temp) {
    return tlx493d_common_getTemperature(sensor, temp);
}

void TLx493D_A2BW_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    tlx493d_gen_2_calculateMagneticField(sensor, A2BW_BX_MSBS_e, A2BW_BX_LSBS_e, A2BW_BY_MSBS_e, A2BW_BY_LSBS_e, A2BW_BZ_MSBS_e, A2BW_BZ_LSBS_e, x, y, z);
}

bool TLx493D_A2BW_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    return tlx493d_common_getMagneticField(sensor, x, y, z);
}


void TLx493D_A2BW_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    TLx493D_A2BW_calculateMagneticField(sensor, x, y, z);
    TLx493D_A2BW_calculateTemperature(sensor, temp);
}


bool TLx493D_A2BW_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    return tlx493d_common_getMagneticFieldAndTemperature(sensor, x, y, z, temp);
}


bool TLx493D_A2BW_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val) {
    return tlx493d_gen_2_setMeasurement(sensor, A2BW_DT_e, A2BW_AM_e, A2BW_CP_e, val);
}


bool TLx493D_A2BW_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t trigger) {
    return tlx493d_gen_2_setTrigger(sensor, A2BW_TRIG_e, A2BW_CP_e, trigger);
}


bool TLx493D_A2BW_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val) {
    uint8_t shortVal      = 0;
    uint8_t extraShortVal = 0;

    switch(val) {
        case TLx493D_FULL_RANGE_e  : shortVal      = 0;
                                     extraShortVal = 0;
                                     break;

        case TLx493D_SHORT_RANGE_e : shortVal      = 1;
                                     extraShortVal = 0;
                                     break;
        
        case TLx493D_EXTRA_SHORT_RANGE_e : shortVal      = 1;
                                           extraShortVal = 1;
                                           break;

        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_SensitivityType_t");
                  return false;
    }

    tlx493d_common_setBitfield(sensor, A2BW_X4_READWRITE_e, extraShortVal);
    return tlx493d_gen_2_setOneConfigBitfield(sensor, A2BW_X2_e, A2BW_CP_e, shortVal) ? tlx493d_gen_2_setOneConfigBitfield(sensor, A2BW_X4_e, A2BW_CP_e, extraShortVal)
                                                                                      : false;
}


bool TLx493D_A2BW_setDefaultConfig(TLx493D_t *sensor) {
    return tlx493d_gen_2_setDefaultConfig(sensor, A2BW_CP_e, A2BW_CA_e, A2BW_INT_e);
}


bool TLx493D_A2BW_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address) {
    return tlx493d_gen_2_setIICAddress(sensor, A2BW_IICADR_e, A2BW_FP_e, address);
}


bool TLx493D_A2BW_enable1ByteReadMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_set1ByteReadMode(sensor, A2BW_PR_e, A2BW_FP_e, A2BW_PRD_e, 1);
}


bool TLx493D_A2BW_enableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, A2BW_CA_e, A2BW_FP_e, 0);
}


bool TLx493D_A2BW_disableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, A2BW_CA_e, A2BW_FP_e, 1);
}


bool TLx493D_A2BW_enableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, A2BW_INT_e, A2BW_FP_e, 0);
}


bool TLx493D_A2BW_disableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, A2BW_INT_e, A2BW_FP_e, 1);
}


bool TLx493D_A2BW_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
    return tlx493d_gen_2_setPowerMode(sensor, A2BW_MODE_e, A2BW_FP_e, mode);
}


bool TLx493D_A2BW_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val) {
    return tlx493d_gen_2_setUpdateRateFastSlow(sensor, A2BW_FP_e, A2BW_PRD_e, val);
}


bool TLx493D_A2BW_hasValidData(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidData(sensor, A2BW_MODE_e, A2BW_PD3_e, A2BW_PD0_e);
}


bool TLx493D_A2BW_isFunctional(const TLx493D_t *sensor) {
    return tlx493d_gen_2_isFunctional(sensor);
}


bool TLx493D_A2BW_hasWakeUp(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasWakeUp");
    return false;
}


bool TLx493D_A2BW_isWakeUpEnabled(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isWakeUpEnabled");
    return false;
}


bool TLx493D_A2BW_enableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "enableWakeUpMode");
    return false;
}


bool TLx493D_A2BW_disableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "disableWakeUpMode");
    return false;
}


bool TLx493D_A2BW_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    (void) xlTh;
    (void) xhTh;
    (void) ylTh;
    (void) yhTh;
    (void) zlTh;
    (void) zhTh;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setWakeUpThresholdsAsInteger");
    return false;
}


/** thesholds im mT, to be converted to proper format */
bool TLx493D_A2BW_setWakeUpThresholds(TLx493D_t *sensor,
                                      double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
    (void) temperature;
    (void) xLow;
    (void) xHigh;
    (void) yLow;
    (void) yHigh;
    (void) zLow;
    (void) zHigh;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setWakeUpThresholds");
    return false;
}


bool TLx493D_A2BW_softwareReset(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "softwareReset");
    return false;
}


uint8_t TLx493D_A2BW_calculateFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateFuseParity(sensor, A2BW_FP_e, A2BW_PRD_e);
}


uint8_t TLx493D_A2BW_calculateBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateBusParity(sensor, 5);
}


uint8_t TLx493D_A2BW_calculateConfigurationParity(TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateConfigurationParity(sensor, A2BW_CP_e);
}


bool TLx493D_A2BW_hasValidFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidFuseParity(sensor, A2BW_FF_e);
}


bool TLx493D_A2BW_hasValidBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidBusParity(sensor, A2BW_P_e);
}


bool TLx493D_A2BW_hasValidConfigurationParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidConfigurationParity(sensor, A2BW_CF_e);
}


bool TLx493D_A2BW_hasValidWakeUpParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidWakeUpParity");
    return false;
}


bool TLx493D_A2BW_isInTestMode(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isInTestMode");
    return false;
}


bool TLx493D_A2BW_hasValidIICadr(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidIICadr(sensor, A2BW_ID_e, A2BW_IICADR_e);
}


bool TLx493D_A2BW_hasValidTBit(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidTBit(sensor, A2BW_T_e);
}


void TLx493D_A2BW_setResetValues(TLx493D_t *sensor) {
    sensor->regMap[0x10] = 0x01; /** CONFIG */
    sensor->regMap[0x11] = 0x80; /** MOD1 : A0 : 0x80, A1 : 0x20, A2 : 0x40, A3 : 0xE0 */
    sensor->regMap[0x13] = 0x00; /** MOD2 */
    sensor->regMap[0x14] = 0x00; /** CONFIG2 */

    /** A2BW_X4_READWRITE_e */
    sensor->regMap[0x17] = 0x00;
}


uint8_t TLx493D_A2BW_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    return tlx493d_gen_2_selectIICAddress(sensor, addr);
}


void TLx493D_A2BW_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticFieldAtTemperature(sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
}


double TLx493D_A2BW_getSensitivityScaleFactor(const TLx493D_t *sensor) {
    return tlx493d_gen_2_getSensitivityScaleFactor(sensor, TLx493D_HAS_X4_e, A2BW_X2_e, A2BW_X4_READWRITE_e);
}


void TLx493D_A2BW_printRegisters(const TLx493D_t *sensor) {
    logPrintRegisters(sensor, TLX493D_A2BW_REGISTER_HEADLINE); 
}
