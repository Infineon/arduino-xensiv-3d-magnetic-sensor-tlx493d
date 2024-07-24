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
#include "TLx493D_A2B6_defines.h"
#include "TLx493D_A2B6_enums.h"
#include "TLx493D_A2B6.h"


static TLx493D_Register_t TLx493D_A2B6_regDef[] = {
    { /* A2B6_BX_MSBS_e, */   TLx493D_READ_MODE_e,        0x00, 0xFF, 0, 8 },
    { /* A2B6_BY_MSBS_e, */   TLx493D_READ_MODE_e,        0x01, 0xFF, 0, 8 },
    { /* A2B6_BZ_MSBS_e, */   TLx493D_READ_MODE_e,        0x02, 0xFF, 0, 8 }, 
    { /* A2B6_TEMP_MSBS_e, */ TLx493D_READ_MODE_e,        0x03, 0xFF, 0, 8 },
    { /* A2B6_BX_LSBS_e, */   TLx493D_READ_MODE_e,        0x04, 0xF0, 4, 4 },
    { /* A2B6_BY_LSBS_e, */   TLx493D_READ_MODE_e,        0x04, 0x0F, 0, 4 },
    { /* A2B6_TEMP_LSBS_e, */ TLx493D_READ_MODE_e,        0x05, 0xC0, 6, 2 },
    { /* A2B6_ID_e, */        TLx493D_READ_MODE_e,        0x05, 0x30, 4, 2 },
    { /* A2B6_BZ_LSBS_e, */   TLx493D_READ_MODE_e,        0x05, 0x0F, 0, 4 },
    { /* A2B6_P_e, */         TLx493D_READ_MODE_e,        0x06, 0x80, 7, 1 },
    { /* A2B6_FF_e, */        TLx493D_READ_MODE_e,        0x06, 0x40, 6, 1 },
    { /* A2B6_CF_e, */        TLx493D_READ_MODE_e,        0x06, 0x20, 5, 1 },
    { /* A2B6_T_e, */         TLx493D_READ_MODE_e,        0x06, 0x10, 4, 1 },
    { /* A2B6_PD3_e, */       TLx493D_READ_MODE_e,        0x06, 0x08, 3, 1 },
    { /* A2B6_PD0_e, */       TLx493D_READ_MODE_e,        0x06, 0x04, 2, 1 },
    { /* A2B6_FRM_e, */       TLx493D_READ_MODE_e,        0x06, 0x03, 0, 2 },
    { /* A2B6_DT_e, */        TLx493D_READ_WRITE_MODE_e,  0x10, 0x80, 7, 1 },
    { /* A2B6_AM_e, */        TLx493D_READ_WRITE_MODE_e,  0x10, 0x40, 6, 1 },
    { /* A2B6_TRIG_e, */      TLx493D_READ_WRITE_MODE_e,  0x10, 0x30, 4, 2 },
    { /* A2B6_X2_e, */        TLx493D_READ_WRITE_MODE_e,  0x10, 0x08, 3, 1 },
    { /* A2B6_TL_MAG_e, */    TLx493D_READ_WRITE_MODE_e,  0x10, 0x06, 1, 2 },
    { /* A2B6_CP_e, */        TLx493D_READ_WRITE_MODE_e,  0x10, 0x01, 0, 1 },
    { /* A2B6_FP_e, */        TLx493D_READ_WRITE_MODE_e,  0x11, 0x80, 7, 1 },
    { /* A2B6_IICADR_e, */    TLx493D_READ_WRITE_MODE_e,  0x11, 0x60, 5, 2 },
    { /* A2B6_PR_e, */        TLx493D_READ_WRITE_MODE_e,  0x11, 0x10, 4, 1 },
    { /* A2B6_CA_e, */        TLx493D_READ_WRITE_MODE_e,  0x11, 0x08, 3, 1 },
    { /* A2B6_INT_e, */       TLx493D_READ_WRITE_MODE_e,  0x11, 0x04, 2, 1 },
    { /* A2B6_MODE_e, */      TLx493D_READ_WRITE_MODE_e,  0x11, 0x03, 0, 2 },

    /** Does not match register overview in manual, but fits and default value textual description of register PRD ! */
    /* {                      TLx493D_READ_WRITE_MODE_e,  0x13, 0xE0, 5, 3 }, */

    { /* A2B6_PRD_e, */       TLx493D_READ_WRITE_MODE_e,  0x13, 0x80, 7, 1 },
    { /* A2B6_TYPE_e, */      TLx493D_READ_MODE_e,        0x16, 0x30, 4, 2 },
    { /* A2B6_HWV_e, */       TLx493D_READ_MODE_e,        0x16, 0x0F, 0, 4 },
};


static TLx493D_CommonFunctions_t TLx493D_A2B6_commonFunctions = {
    .init                           = TLx493D_A2B6_init,
    .deinit                         = TLx493D_A2B6_deinit,

    .readRegisters                  = TLx493D_A2B6_readRegisters,
    .readRegistersAndCheck          = TLx493D_A2B6_readRegistersAndCheck,

    .calculateRawTemperature        = TLx493D_A2B6_calculateRawTemperature,
    .getRawTemperature              = TLx493D_A2B6_getRawTemperature,

    .calculateRawMagneticField      = TLx493D_A2B6_calculateRawMagneticField,
    .getRawMagneticField            = TLx493D_A2B6_getRawMagneticField,

    .calculateRawMagneticFieldAndTemperature = TLx493D_A2B6_calculateRawMagneticFieldAndTemperature,
    .getRawMagneticFieldAndTemperature       = TLx493D_A2B6_getRawMagneticFieldAndTemperature,

    .calculateTemperature           = TLx493D_A2B6_calculateTemperature,
    .getTemperature                 = TLx493D_A2B6_getTemperature,

    .calculateMagneticField         = TLx493D_A2B6_calculateMagneticField,
    .getMagneticField               = TLx493D_A2B6_getMagneticField,

    .calculateMagneticFieldAndTemperature = TLx493D_A2B6_calculateMagneticFieldAndTemperature,
    .getMagneticFieldAndTemperature = TLx493D_A2B6_getMagneticFieldAndTemperature,

    /** functions related to the "Config" register. */
    .setMeasurement                 = TLx493D_A2B6_setMeasurement,
    .setTrigger                     = TLx493D_A2B6_setTrigger,
    .setSensitivity                 = TLx493D_A2B6_setSensitivity,
    
    /** functions related to the "Mod1" and "Mod2" registers. */
    .setDefaultConfig               = TLx493D_A2B6_setDefaultConfig,
    .setIICAddress                  = TLx493D_A2B6_setIICAddress,
    .enable1ByteReadMode            = TLx493D_A2B6_enable1ByteReadMode,
    /** .disable1ByteReadMode           = TLx493D_A2B6_disable1ByteReadMode, */

    .enableInterrupt                = TLx493D_A2B6_enableInterrupt,
    .disableInterrupt               = TLx493D_A2B6_disableInterrupt,

    .enableCollisionAvoidance       = TLx493D_A2B6_enableCollisionAvoidance,
    .disableCollisionAvoidance      = TLx493D_A2B6_disableCollisionAvoidance,

    .setPowerMode                   = TLx493D_A2B6_setPowerMode,
    .setUpdateRate                  = TLx493D_A2B6_setUpdateRate,

    /** functions related to the "Diag" register. */
    .hasValidData                   = TLx493D_A2B6_hasValidData,
    .isFunctional                   = TLx493D_A2B6_isFunctional,

    /** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
    .hasWakeUp                      = TLx493D_A2B6_hasWakeUp,
    .isWakeUpEnabled                = TLx493D_A2B6_isWakeUpEnabled,
    .enableWakeUpMode               = TLx493D_A2B6_enableWakeUpMode,
    .disableWakeUpMode              = TLx493D_A2B6_disableWakeUpMode,

    .setWakeUpThresholdsAsInteger   = TLx493D_A2B6_setWakeUpThresholdsAsInteger,
    .setWakeUpThresholds            = TLx493D_A2B6_setWakeUpThresholds,

    .softwareReset                  = TLx493D_A2B6_softwareReset,

    .printRegisters                 = TLx493D_A2B6_printRegisters,

    /** functions used internally and not accessible through the common interface. */
    .calculateFuseParity            = TLx493D_A2B6_calculateFuseParity,
    .calculateBusParity             = TLx493D_A2B6_calculateBusParity,
    .calculateConfigurationParity   = TLx493D_A2B6_calculateConfigurationParity,

    .hasValidFuseParity             = TLx493D_A2B6_hasValidFuseParity,
    .hasValidBusParity              = TLx493D_A2B6_hasValidBusParity,
    .hasValidConfigurationParity    = TLx493D_A2B6_hasValidConfigurationParity,
 
    .hasValidWakeUpParity           = TLx493D_A2B6_hasValidWakeUpParity,
    .isInTestMode                   = TLx493D_A2B6_isInTestMode,
    
    .hasValidTBit                   = TLx493D_A2B6_hasValidTBit,

    .setResetValues                 = TLx493D_A2B6_setResetValues,

    .selectIICAddress               = TLx493D_A2B6_selectIICAddress,

    .calculateRawMagneticFieldAtTemperature  = TLx493D_A2B6_calculateRawMagneticFieldAtTemperature,

    .getSensitivityScaleFactor      = TLx493D_A2B6_getSensitivityScaleFactor,
};


bool TLx493D_A2B6_init(TLx493D_t *sensor) {
    return tlx493d_common_init(sensor, GEN_2_REG_MAP_SIZE, TLx493D_A2B6_regDef, &TLx493D_A2B6_commonFunctions, TLx493D_A2B6_e, TLx493D_I2C_e);
}


bool TLx493D_A2B6_deinit(TLx493D_t *sensor) {
    return tlx493d_common_deinit(sensor);
}


bool TLx493D_A2B6_readRegisters(TLx493D_t *sensor) {
    return tlx493d_common_readRegisters(sensor);
}


bool TLx493D_A2B6_readRegistersAndCheck(TLx493D_t *sensor) {
    return tlx493d_common_readRegistersAndCheck(sensor);
}


void TLx493D_A2B6_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    tlx493d_gen_2_calculateRawTemperature(sensor, A2B6_TEMP_MSBS_e, A2B6_TEMP_LSBS_e, temperature);
}


bool TLx493D_A2B6_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    return tlx493d_common_getRawTemperature(sensor, temperature);
}


void TLx493D_A2B6_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticField(sensor, A2B6_BX_MSBS_e, A2B6_BX_LSBS_e, A2B6_BY_MSBS_e, A2B6_BY_LSBS_e, A2B6_BZ_MSBS_e, A2B6_BZ_LSBS_e, x, y, z);
}


bool TLx493D_A2B6_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    return tlx493d_common_getRawMagneticField(sensor, x, y, z);
}


void TLx493D_A2B6_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    TLx493D_A2B6_calculateRawMagneticField(sensor, x, y, z);
    TLx493D_A2B6_calculateRawTemperature(sensor, temperature);
}


bool TLx493D_A2B6_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    return tlx493d_common_getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


void TLx493D_A2B6_calculateTemperature(TLx493D_t *sensor, double *temperature) {
    tlx493d_gen_2_calculateTemperature(sensor, A2B6_TEMP_MSBS_e, A2B6_TEMP_LSBS_e, temperature);
}


bool TLx493D_A2B6_getTemperature(TLx493D_t *sensor, double *temperature) {
    return tlx493d_common_getTemperature(sensor, temperature);
}


void TLx493D_A2B6_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    tlx493d_gen_2_calculateMagneticField(sensor, A2B6_BX_MSBS_e, A2B6_BX_LSBS_e, A2B6_BY_MSBS_e, A2B6_BY_LSBS_e, A2B6_BZ_MSBS_e, A2B6_BZ_LSBS_e, x, y, z);
}


bool TLx493D_A2B6_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    return tlx493d_common_getMagneticField(sensor, x, y, z);
}


void TLx493D_A2B6_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature) {
    TLx493D_A2B6_calculateMagneticField(sensor, x, y, z);
    TLx493D_A2B6_calculateTemperature(sensor, temperature);
}


bool TLx493D_A2B6_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature) {
    return tlx493d_common_getMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


bool TLx493D_A2B6_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val) {
    return tlx493d_gen_2_setMeasurement(sensor, A2B6_DT_e, A2B6_AM_e, A2B6_CP_e, val);
}


/** This option depends on PR and MODE. */
bool TLx493D_A2B6_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t val) {
    return tlx493d_gen_2_setTrigger(sensor, A2B6_TRIG_e, A2B6_CP_e, val);
}


bool TLx493D_A2B6_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val) {
    return tlx493d_gen_2_setSensitivity(sensor, TLx493D_HAS_X2_e, A2B6_X2_e, 0, A2B6_CP_e, val);
}


/*
bool TLx493D_A2B6_setTC0MagneticTemperatureCompensation(TLx493D_t *sensor) {
    return tlx493d_gen_2_setMagneticTemperatureCompensation(sensor, A2B6_TL_MAG_e, A2B6_CP_e, 0b00);
}
*/

/*
bool TLx493D_A2B6_setTC1MagneticTemperatureCompensation(TLx493D_t *sensor) {
    return tlx493d_gen_2_setMagneticTemperatureCompensation(sensor, A2B6_TL_MAG_e, A2B6_CP_e, 0b01);
}
*/


/*
bool TLx493D_A2B6_setTC2MagneticTemperatureCompensation(TLx493D_t *sensor) {
    return tlx493d_gen_2_setMagneticTemperatureCompensation(sensor, A2B6_TL_MAG_e, A2B6_CP_e, 0b10);
}
*/


/*
bool TLx493D_A2B6_setTC3MagneticTemperatureCompensation(TLx493D_t *sensor) {
    return tlx493d_gen_2_setMagneticTemperatureCompensation(sensor, A2B6_TL_MAG_e, A2B6_CP_e, 0b11);
}
*/


bool TLx493D_A2B6_setDefaultConfig(TLx493D_t *sensor) {
    return tlx493d_gen_2_setDefaultConfig(sensor, A2B6_CP_e, A2B6_CA_e, A2B6_INT_e);
}


bool TLx493D_A2B6_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address) {
    return tlx493d_gen_2_setIICAddress(sensor, A2B6_IICADR_e, A2B6_FP_e, address);
}


bool TLx493D_A2B6_enable1ByteReadMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_set1ByteReadMode(sensor, A2B6_PR_e, A2B6_FP_e, A2B6_PRD_e, 1);
}

/*
bool TLx493D_A2B6_disable1ByteReadMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_set1ByteReadMode(sensor, A2B6_PR_e, A2B6_FP_e, A2B6_PRD_e, 0);
}
*/

bool TLx493D_A2B6_enableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, A2B6_CA_e, A2B6_FP_e, 0);
}


bool TLx493D_A2B6_disableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, A2B6_CA_e, A2B6_FP_e, 1);
}


bool TLx493D_A2B6_enableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, A2B6_INT_e, A2B6_FP_e, 0);
}


bool TLx493D_A2B6_disableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, A2B6_INT_e, A2B6_FP_e, 1);
}


bool TLx493D_A2B6_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
    return tlx493d_gen_2_setPowerMode(sensor, A2B6_MODE_e, A2B6_FP_e, mode);
}


bool TLx493D_A2B6_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val) {
    return tlx493d_gen_2_setUpdateRateFastSlow(sensor, A2B6_FP_e, A2B6_PRD_e, val);
}


bool TLx493D_A2B6_hasValidData(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidData(sensor, A2B6_MODE_e, A2B6_PD3_e, A2B6_PD0_e);
}


bool TLx493D_A2B6_isFunctional(const TLx493D_t *sensor) {
    return tlx493d_gen_2_isFunctional(sensor);
}


bool TLx493D_A2B6_hasWakeUp(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasWakeUp");
    /** return tlx493d_gen_2_hasWakeUp(sensor, TYPE); */
    return false;
}


bool TLx493D_A2B6_isWakeUpEnabled(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isWakeUpEnabled");
    return false;
}

bool TLx493D_A2B6_enableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "enableWakeUpMode");
    return false;
}

bool TLx493D_A2B6_disableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "disableWakeUpMode");
    return false;
}


bool TLx493D_A2B6_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    (void) xlTh;
    (void) xhTh;
    (void) ylTh;
    (void) yhTh;
    (void) zlTh;
    (void) zhTh;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setWakeUpThresholdsAsInteger");
    return false;
}

bool TLx493D_A2B6_setWakeUpThresholds(TLx493D_t *sensor, double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
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

bool TLx493D_A2B6_softwareReset(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "softwareReset");
    return false;
}


uint8_t TLx493D_A2B6_calculateFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateFuseParity(sensor, A2B6_FP_e, A2B6_PRD_e);
}


uint8_t TLx493D_A2B6_calculateBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateBusParity(sensor, 5);
}


uint8_t TLx493D_A2B6_calculateConfigurationParity(TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateConfigurationParity(sensor, A2B6_CP_e);
}


bool TLx493D_A2B6_hasValidFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidFuseParity(sensor, A2B6_FF_e);
}


bool TLx493D_A2B6_hasValidBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidBusParity(sensor, A2B6_P_e);
}


bool TLx493D_A2B6_hasValidConfigurationParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidConfigurationParity(sensor, A2B6_CF_e);
}


bool TLx493D_A2B6_hasValidWakeUpParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidWakeUpParity");
    return false;
}


bool TLx493D_A2B6_isInTestMode(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isInTestMode");
    return false;
}


bool TLx493D_A2B6_hasValidTBit(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidTBit(sensor, A2B6_T_e);
}


bool TLx493D_A2B6_hasValidIICadr(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidIICadr(sensor, A2B6_ID_e, A2B6_IICADR_e);
}

/*
bool TLx493D_A2B6_hasValidTemperatureData(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidTemperatureData(sensor);
}
*/

/*
bool TLx493D_A2B6_hasValidMagneticFieldData(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidMagneticFieldData(sensor);
}
*/


/*
bool TLx493D_A2B6_hasValidPD0Bit(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidPD0Bit(sensor, PD0);
}
*/


/*
bool TLx493D_A2B6_hasValidPD3Bit(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidPD3Bit(sensor, PD3);
}
*/


void TLx493D_A2B6_setResetValues(TLx493D_t *sensor) {
    sensor->regMap[0x10] = 0x00; /** CONFIG */
    sensor->regMap[0x11] = 0x00; /** MOD1 */
    sensor->regMap[0x13] = 0x00; /** MOD2 */
}


uint8_t TLx493D_A2B6_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    return tlx493d_gen_2_selectIICAddress(sensor, addr);
}


void TLx493D_A2B6_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticFieldAtTemperature(sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
}


double TLx493D_A2B6_getSensitivityScaleFactor(const TLx493D_t *sensor) {
    return tlx493d_gen_2_getSensitivityScaleFactor(sensor, TLx493D_HAS_X2_e, A2B6_X2_e, 0);
}


void TLx493D_A2B6_printRegisters(const TLx493D_t *sensor) {
    logPrintRegisters(sensor, TLX493D_A2B6_REGISTER_HEADLINE); 
}
