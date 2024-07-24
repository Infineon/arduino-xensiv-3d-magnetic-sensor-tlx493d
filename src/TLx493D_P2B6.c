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
#include "TLx493D_P2B6_defines.h"
#include "TLx493D_P2B6_enums.h"
#include "TLx493D_P2B6.h"


static TLx493D_Register_t TLx493D_P2B6_regDef[] = {
    { /* P2B6_BX_MSBS_e, */    TLx493D_READ_MODE_e,        0x00, 0xFF, 0, 8 },
    { /* P2B6_BY_MSBS_e, */    TLx493D_READ_MODE_e,        0x01, 0xFF, 0, 8 },
    { /* P2B6_BZ_MSBS_e, */    TLx493D_READ_MODE_e,        0x02, 0xFF, 0, 8 },
    { /* P2B6_TEMP_MSBS_e, */  TLx493D_READ_MODE_e,        0x03, 0xFF, 0, 8 },
    { /* P2B6_BX_LSBS_e, */    TLx493D_READ_MODE_e,        0x04, 0xF0, 4, 4 },
    { /* P2B6_BY_LSBS_e, */    TLx493D_READ_MODE_e,        0x04, 0x0F, 0, 4 },
    { /* P2B6_TEMP_LSBS_e, */  TLx493D_READ_MODE_e,        0x05, 0xC0, 6, 2 },
    { /* P2B6_ID_e, */         TLx493D_READ_MODE_e,        0x05, 0x30, 4, 2 },
    { /* P2B6_BZ_LSBS_e, */    TLx493D_READ_MODE_e,        0x05, 0x0F, 0, 4 },
    { /* P2B6_P_e, */          TLx493D_READ_MODE_e,        0x06, 0x80, 7, 1 },
    { /* P2B6_FF_e, */         TLx493D_READ_MODE_e,        0x06, 0x40, 6, 1 },
    { /* P2B6_CF_e, */         TLx493D_READ_MODE_e,        0x06, 0x20, 5, 1 },
    { /* P2B6_T_e, */          TLx493D_READ_MODE_e,        0x06, 0x10, 4, 1 },
    { /* P2B6_PD3_e, */        TLx493D_READ_MODE_e,        0x06, 0x08, 3, 1 },
    { /* P2B6_PD0_e, */        TLx493D_READ_MODE_e,        0x06, 0x04, 2, 1 },
    { /* P2B6_FRM_e, */        TLx493D_READ_MODE_e,        0x06, 0x03, 0, 2 },
    { /* P2B6_XL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x07, 0xFF, 0, 8 },
    { /* P2B6_XH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x08, 0xFF, 0, 8 },
    { /* P2B6_YL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x09, 0xFF, 0, 8 },
    { /* P2B6_YH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0A, 0xFF, 0, 8 },
    { /* P2B6_ZL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0B, 0xFF, 0, 8 },
    { /* P2B6_ZH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0C, 0xFF, 0, 8 },
    { /* P2B6_WA_e, */         TLx493D_READ_MODE_e,        0x0D, 0x80, 7, 1 },
    { /* P2B6_WU_e, */         TLx493D_READ_WRITE_MODE_e,  0x0D, 0x40, 6, 1 },
    { /* P2B6_XH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0D, 0x38, 3, 3 },
    { /* P2B6_XL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0D, 0x07, 0, 3 },
    { /* P2B6_TST_e, */        TLx493D_READ_WRITE_MODE_e,  0x0E, 0xC0, 6, 2 },
    { /* P2B6_YH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0E, 0x38, 3, 3 },  
    { /* P2B6_YL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0E, 0x07, 0, 3 },
    { /* P2B6_PH_e, */         TLx493D_READ_WRITE_MODE_e,  0x0F, 0xC0, 6, 2 },
    { /* P2B6_ZH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0F, 0x38, 3, 3 },
    { /* P2B6_ZL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0F, 0x07, 0, 3 },
    { /* P2B6_DT_e, */         TLx493D_READ_WRITE_MODE_e,  0x10, 0x80, 7, 1 },
    { /* P2B6_AM_e, */         TLx493D_READ_WRITE_MODE_e,  0x10, 0x40, 6, 1 },
    { /* P2B6_TRIG_e, */       TLx493D_READ_WRITE_MODE_e,  0x10, 0x30, 4, 2 },
    { /* P2B6_X2_e, */         TLx493D_READ_WRITE_MODE_e,  0x10, 0x08, 3, 1 },
    { /* P2B6_TL_MAG_e, */     TLx493D_READ_WRITE_MODE_e,  0x10, 0x06, 1, 2 },
    { /* P2B6_CP_e, */         TLx493D_READ_WRITE_MODE_e,  0x10, 0x01, 0, 1 },
    { /* P2B6_FP_e, */         TLx493D_READ_WRITE_MODE_e,  0x11, 0x80, 7, 1 },
    { /* P2B6_IICADR_e, */     TLx493D_READ_WRITE_MODE_e,  0x11, 0x60, 5, 2 },
    { /* P2B6_PR_e, */         TLx493D_READ_WRITE_MODE_e,  0x11, 0x10, 4, 1 },
    { /* P2B6_CA_e, */         TLx493D_READ_WRITE_MODE_e,  0x11, 0x08, 3, 1 },
    { /* P2B6_INT_e, */        TLx493D_READ_WRITE_MODE_e,  0x11, 0x04, 2, 1 },
    { /* P2B6_MODE_e, */       TLx493D_READ_WRITE_MODE_e,  0x11, 0x03, 0, 2 },
    { /* P2B6_PRD_e, */        TLx493D_READ_WRITE_MODE_e,  0x13, 0xE0, 5, 3 },
    { /* P2B6_TYPE_e, */       TLx493D_READ_MODE_e,        0x16, 0x30, 4, 2 },
    { /* P2B6_HWV_e, */        TLx493D_READ_MODE_e,        0x16, 0x0F, 0, 4 },
};


static TLx493D_CommonFunctions_t TLx493D_P2B6_commonFunctions = {
    .init                           = TLx493D_P2B6_init,
    .deinit                         = TLx493D_P2B6_deinit,

    .readRegisters                  = TLx493D_P2B6_readRegisters,
    .readRegistersAndCheck          = TLx493D_P2B6_readRegistersAndCheck,

    .calculateRawTemperature        = TLx493D_P2B6_calculateRawTemperature,
    .getRawTemperature              = TLx493D_P2B6_getRawTemperature,

    .calculateRawMagneticField      = TLx493D_P2B6_calculateRawMagneticField,
    .getRawMagneticField            = TLx493D_P2B6_getRawMagneticField,

    .calculateRawMagneticFieldAndTemperature = TLx493D_P2B6_calculateRawMagneticFieldAndTemperature,
    .getRawMagneticFieldAndTemperature       = TLx493D_P2B6_getRawMagneticFieldAndTemperature,

    .calculateTemperature           = TLx493D_P2B6_calculateTemperature,
    .getTemperature                 = TLx493D_P2B6_getTemperature,

    .calculateMagneticField         = TLx493D_P2B6_calculateMagneticField,
    .getMagneticField               = TLx493D_P2B6_getMagneticField,

    .calculateMagneticFieldAndTemperature = TLx493D_P2B6_calculateMagneticFieldAndTemperature,
    .getMagneticFieldAndTemperature = TLx493D_P2B6_getMagneticFieldAndTemperature,

    /** functions related to the "Config" register. */
    .setMeasurement                 = TLx493D_P2B6_setMeasurement,
    .setTrigger                     = TLx493D_P2B6_setTrigger,
    .setSensitivity                 = TLx493D_P2B6_setSensitivity,
    
    /** functions related to the "Mod1" and "Mod2" registers. */
    .setDefaultConfig               = TLx493D_P2B6_setDefaultConfig,
    .setIICAddress                  = TLx493D_P2B6_setIICAddress,
    .enable1ByteReadMode            = TLx493D_P2B6_enable1ByteReadMode,

    .enableInterrupt                = TLx493D_P2B6_enableInterrupt,
    .disableInterrupt               = TLx493D_P2B6_disableInterrupt,

    .enableCollisionAvoidance       = TLx493D_P2B6_enableCollisionAvoidance,
    .disableCollisionAvoidance      = TLx493D_P2B6_disableCollisionAvoidance,

    .setPowerMode                   = TLx493D_P2B6_setPowerMode,
    .setUpdateRate                  = TLx493D_P2B6_setUpdateRate,

    /** functions related to the "Diag" register. */
    .hasValidData                   = TLx493D_P2B6_hasValidData,
    .isFunctional                   = TLx493D_P2B6_isFunctional,

    /** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
    .hasWakeUp                      = TLx493D_P2B6_hasWakeUp,
    .isWakeUpEnabled                = TLx493D_P2B6_isWakeUpEnabled,
    .enableWakeUpMode               = TLx493D_P2B6_enableWakeUpMode,
    .disableWakeUpMode              = TLx493D_P2B6_disableWakeUpMode,

    .setWakeUpThresholdsAsInteger   = TLx493D_P2B6_setWakeUpThresholdsAsInteger,
    .setWakeUpThresholds            = TLx493D_P2B6_setWakeUpThresholds,

    .softwareReset                  = TLx493D_P2B6_softwareReset,

    .printRegisters                 = TLx493D_P2B6_printRegisters,

    /** functions used internally and not accessible through the common interface. */
    .calculateFuseParity            = TLx493D_P2B6_calculateFuseParity,
    .calculateBusParity             = TLx493D_P2B6_calculateBusParity,
    .calculateConfigurationParity   = TLx493D_P2B6_calculateConfigurationParity,

    .hasValidFuseParity             = TLx493D_P2B6_hasValidFuseParity,
    .hasValidBusParity              = TLx493D_P2B6_hasValidBusParity,
    .hasValidConfigurationParity    = TLx493D_P2B6_hasValidConfigurationParity,
 
    .hasValidWakeUpParity           = TLx493D_P2B6_hasValidWakeUpParity,
    .isInTestMode                   = TLx493D_P2B6_isInTestMode,
    
    .hasValidTBit                   = TLx493D_P2B6_hasValidTBit,

    .setResetValues                 = TLx493D_P2B6_setResetValues,

    .selectIICAddress               = TLx493D_P2B6_selectIICAddress,

    .calculateRawMagneticFieldAtTemperature  = TLx493D_P2B6_calculateRawMagneticFieldAtTemperature,

    .getSensitivityScaleFactor      = TLx493D_P2B6_getSensitivityScaleFactor,
};


bool TLx493D_P2B6_init(TLx493D_t *sensor) {
    return tlx493d_common_init(sensor, GEN_2_REG_MAP_SIZE, TLx493D_P2B6_regDef, &TLx493D_P2B6_commonFunctions, TLx493D_P2B6_e, TLx493D_I2C_e);
}


bool TLx493D_P2B6_deinit(TLx493D_t *sensor) {
    return tlx493d_common_deinit(sensor);
}


bool TLx493D_P2B6_readRegisters(TLx493D_t *sensor) {
    return tlx493d_common_readRegisters(sensor);
}


bool TLx493D_P2B6_readRegistersAndCheck(TLx493D_t *sensor) {
    return tlx493d_common_readRegistersAndCheck(sensor);
}


void TLx493D_P2B6_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    tlx493d_gen_2_calculateRawTemperature(sensor, P2B6_TEMP_MSBS_e, P2B6_TEMP_LSBS_e, temperature);
}


bool TLx493D_P2B6_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    return tlx493d_common_getRawTemperature(sensor, temperature);
}


void TLx493D_P2B6_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticField(sensor, P2B6_BX_MSBS_e, P2B6_BX_LSBS_e, P2B6_BY_MSBS_e, P2B6_BY_LSBS_e, P2B6_BZ_MSBS_e, P2B6_BZ_LSBS_e, x, y, z);
}


bool TLx493D_P2B6_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    return tlx493d_common_getRawMagneticField(sensor, x, y, z);
}


void TLx493D_P2B6_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    TLx493D_P2B6_calculateRawMagneticField(sensor, x, y, z);
    TLx493D_P2B6_calculateRawTemperature(sensor, temperature);
}


bool TLx493D_P2B6_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    return tlx493d_common_getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


void TLx493D_P2B6_calculateTemperature(TLx493D_t *sensor, double *temp) {
    tlx493d_gen_2_calculateTemperature(sensor, P2B6_TEMP_MSBS_e, P2B6_TEMP_LSBS_e, temp);
}


bool TLx493D_P2B6_getTemperature(TLx493D_t *sensor, double *temp) {
    return tlx493d_common_getTemperature(sensor, temp);
}


void TLx493D_P2B6_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    tlx493d_gen_2_calculateMagneticField(sensor, P2B6_BX_MSBS_e, P2B6_BX_LSBS_e, P2B6_BY_MSBS_e, P2B6_BY_LSBS_e, P2B6_BZ_MSBS_e, P2B6_BZ_LSBS_e, x, y, z);
}


bool TLx493D_P2B6_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    return tlx493d_common_getMagneticField(sensor, x, y, z);
}


void TLx493D_P2B6_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    TLx493D_P2B6_calculateMagneticField(sensor, x, y, z);
    TLx493D_P2B6_calculateTemperature(sensor, temp);
}


bool TLx493D_P2B6_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    return tlx493d_common_getMagneticFieldAndTemperature(sensor, x, y, z, temp);
}


bool TLx493D_P2B6_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val) {
    return tlx493d_gen_2_setMeasurement(sensor, P2B6_DT_e, P2B6_AM_e, P2B6_CP_e, val);
}


/** This option depends on PR and MODE. */
bool TLx493D_P2B6_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t val) {
    return tlx493d_gen_2_setTrigger(sensor, P2B6_TRIG_e, P2B6_CP_e, val);
}


bool TLx493D_P2B6_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val) {
    return tlx493d_gen_2_setSensitivity(sensor, TLx493D_HAS_X2_e, P2B6_X2_e, 0, P2B6_CP_e, val);
}


bool TLx493D_P2B6_setDefaultConfig(TLx493D_t *sensor) {
    return tlx493d_gen_2_setDefaultConfig(sensor, P2B6_CP_e, P2B6_CA_e, P2B6_INT_e);
}


bool TLx493D_P2B6_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address) {
    return tlx493d_gen_2_setIICAddress(sensor, P2B6_IICADR_e, P2B6_FP_e, address);
}


bool TLx493D_P2B6_enable1ByteReadMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_set1ByteReadMode(sensor, P2B6_PR_e, P2B6_FP_e, P2B6_PRD_e, 1);
}


bool TLx493D_P2B6_enableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, P2B6_CA_e, P2B6_FP_e, 0);
}


bool TLx493D_P2B6_disableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_2_setCollisionAvoidance(sensor, P2B6_CA_e, P2B6_FP_e, 1);
}


bool TLx493D_P2B6_enableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, P2B6_INT_e, P2B6_FP_e, 0);
}


bool TLx493D_P2B6_disableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_2_setInterrupt(sensor, P2B6_INT_e, P2B6_FP_e, 1);
}


bool TLx493D_P2B6_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
    return tlx493d_gen_2_setPowerMode(sensor, P2B6_MODE_e, P2B6_FP_e, mode);
}


bool TLx493D_P2B6_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val) {
    return tlx493d_gen_2_setUpdateRate(sensor, P2B6_FP_e, P2B6_PRD_e, val);
}


bool TLx493D_P2B6_hasValidData(const TLx493D_t *sensor) {
    return( tlx493d_gen_2_hasValidData(sensor, P2B6_MODE_e, P2B6_PD3_e, P2B6_PD0_e) );

/*
    return( tlx493d_gen_2_hasValidData(sensor) && (tlx493d_common_returnBitfield(sensor, P2B6_MODE_e) == 0b11 ? true
                                                                       : (tlx493d_common_returnBitfield(sensor, P2B6_PD0_e) == 1) && (tlx493d_common_returnBitfield(sensor, P2B6_PD3_e) == 1) );
*/                                                
}


bool TLx493D_P2B6_isFunctional(const TLx493D_t *sensor) {
    return tlx493d_gen_2_isFunctional(sensor);
}


bool TLx493D_P2B6_hasWakeUp(const TLx493D_t *sensor) {
    (void) sensor;
    return true;
}


bool TLx493D_P2B6_isWakeUpEnabled(const TLx493D_t *sensor) {
    return tlx493d_gen_2_isWakeUpEnabled(sensor, P2B6_WA_e);
}

bool TLx493D_P2B6_enableWakeUpMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_enableWakeUpMode(sensor, P2B6_TST_e, P2B6_WU_e, P2B6_CP_e);
}


bool TLx493D_P2B6_disableWakeUpMode(TLx493D_t *sensor) {
    return tlx493d_gen_2_disableWakeUpMode(sensor, P2B6_WU_e, P2B6_CP_e);
}


bool TLx493D_P2B6_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    return tlx493d_gen_2_setWakeUpThresholdsAsInteger(sensor, P2B6_CP_e,
                                                      P2B6_XL_MSBS_e, P2B6_XL_LSBS_e, P2B6_XH_MSBS_e, P2B6_XH_LSBS_e,
                                                      P2B6_YL_MSBS_e, P2B6_YL_LSBS_e, P2B6_YH_MSBS_e, P2B6_YH_LSBS_e,
                                                      P2B6_ZL_MSBS_e, P2B6_ZL_LSBS_e, P2B6_ZH_MSBS_e, P2B6_ZH_LSBS_e,
                                                      xlTh, xhTh, ylTh, yhTh, zlTh, zhTh);
}


bool TLx493D_P2B6_setWakeUpThresholds(TLx493D_t *sensor,
                                      double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
    return tlx493d_gen_2_setWakeUpThresholds(sensor, P2B6_CP_e,
                                             P2B6_XL_MSBS_e, P2B6_XL_LSBS_e, P2B6_XH_MSBS_e, P2B6_XH_LSBS_e,
                                             P2B6_YL_MSBS_e, P2B6_YL_LSBS_e, P2B6_YH_MSBS_e, P2B6_YH_LSBS_e,
                                             P2B6_ZL_MSBS_e, P2B6_ZL_LSBS_e, P2B6_ZH_MSBS_e, P2B6_ZH_LSBS_e,
                                             TLx493D_HAS_X2_e, P2B6_X2_e, 0,
                                             temperature, xLow, xHigh, yLow, yHigh, zLow, zHigh);
}


bool TLx493D_P2B6_softwareReset(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "softwareReset");
    return false;
}



uint8_t TLx493D_P2B6_calculateFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateFuseParity(sensor, P2B6_FP_e, P2B6_PRD_e);
}


uint8_t TLx493D_P2B6_calculateBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateBusParity(sensor, 5);
}


uint8_t TLx493D_P2B6_calculateConfigurationParity(TLx493D_t *sensor) {
    return tlx493d_gen_2_calculateConfigurationParityWakeUp(sensor, P2B6_CP_e);
}


bool TLx493D_P2B6_hasValidFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidFuseParity(sensor, P2B6_FF_e);
}


bool TLx493D_P2B6_hasValidBusParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidBusParity(sensor, P2B6_P_e);
}


bool TLx493D_P2B6_hasValidConfigurationParity(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidConfigurationParity(sensor, P2B6_CF_e);
}


bool TLx493D_P2B6_hasValidWakeUpParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidWakeUpParity");
    return false;
}


bool TLx493D_P2B6_isInTestMode(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isInTestMode");
    return false;
}


bool TLx493D_P2B6_hasValidIICadr(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidIICadr(sensor, P2B6_ID_e, P2B6_IICADR_e);
}


bool TLx493D_P2B6_hasValidTBit(const TLx493D_t *sensor) {
    return tlx493d_gen_2_hasValidTBit(sensor, P2B6_T_e);
}


void TLx493D_P2B6_setResetValues(TLx493D_t *sensor) {
    sensor->regMap[0x07] = 0x80;
    sensor->regMap[0x08] = 0x7F;
    sensor->regMap[0x09] = 0x80;
    sensor->regMap[0x0A] = 0x7F;
    sensor->regMap[0x0B] = 0x80;
    sensor->regMap[0x0C] = 0x7F;
    sensor->regMap[0x0D] = 0x38;
    sensor->regMap[0x0E] = 0x38;
    sensor->regMap[0x0F] = 0x38;  
    sensor->regMap[0x10] = 0x01; /** CONFIG */
    sensor->regMap[0x11] = 0x80; /** MOD1 : A0 : 0x80, A1 : 0x20, A2 : 0x40, A3 : 0xE0 */
    sensor->regMap[0x13] = 0x00; /** MOD2 */
}


uint8_t TLx493D_P2B6_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    return tlx493d_gen_2_selectIICAddress(sensor, addr);
}


void TLx493D_P2B6_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_2_calculateRawMagneticFieldAtTemperature(sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
}


double TLx493D_P2B6_getSensitivityScaleFactor(const TLx493D_t *sensor) {
    return tlx493d_gen_2_getSensitivityScaleFactor(sensor, TLx493D_HAS_X2_e, P2B6_X2_e, 0);
}


void TLx493D_P2B6_printRegisters(const TLx493D_t *sensor) {
    logPrintRegisters(sensor, TLX493D_P2B6_REGISTER_HEADLINE); 
}
