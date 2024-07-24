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

#include "tlx493d_gen_3_common_defines.h"
#include "tlx493d_gen_3_common.h"

/** sensor specicifc includes. */
#include "TLx493D_P3B6_defines.h"
#include "TLx493D_P3B6_enums.h"
#include "TLx493D_P3B6.h"


static TLx493D_Register_t TLx493D_P3B6_regDef[] = {
    { /* P3B6_BX_MSBS_e, */       TLx493D_READ_MODE_e,        0x00, 0xFF, 0, 8 },
    { /* P3B6_IIC_ADR_CP_e, */    TLx493D_READ_MODE_e,        0x01, 0xC0, 6, 2 },
    { /* P3B6_BX_LSBS_e, */       TLx493D_READ_MODE_e,        0x01, 0x3F, 0, 6 },
    { /* P3B6_BY_MSBS_e, */       TLx493D_READ_MODE_e,        0x02, 0xFF, 0, 8 },
    { /* P3B6_BY_LSBS_e, */       TLx493D_READ_MODE_e,        0x03, 0x3F, 0, 6 },
    { /* P3B6_BZ_MSBS_e, */       TLx493D_READ_MODE_e,        0x04, 0xFF, 0, 8 },
    { /* P3B6_BZ_LSBS_e, */       TLx493D_READ_MODE_e,        0x05, 0x3F, 0, 6 },
    { /* P3B6_TEMP_MSBS_e, */     TLx493D_READ_MODE_e,        0x06, 0xFF, 0, 8 },
    { /* P3B6_TEMP_LSBS_e, */     TLx493D_READ_MODE_e,        0x07, 0x3F, 0, 6 },
    { /* P3B6_CRC_e, */           TLx493D_READ_MODE_e,        0x08, 0xFF, 0, 8 },
    { /* P3B6_MEAS_FLG_e, */      TLx493D_READ_MODE_e,        0x09, 0x80, 7, 1 },
    { /* P3B6_TEST_FLG_e, */      TLx493D_READ_MODE_e,        0x09, 0x40, 6, 1 },
    { /* P3B6_FRAME_COUNTER_e, */ TLx493D_READ_MODE_e,        0x09, 0x30, 4, 2 },
    { /* P3B6_RST_FLG_e, */       TLx493D_READ_MODE_e,        0x09, 0x08, 3, 1 },
    { /* P3B6_WU_PAR_FLG_e, */    TLx493D_READ_MODE_e,        0x09, 0x04, 2, 1 },
    { /* P3B6_CRC_WR_FLG_e, */    TLx493D_READ_MODE_e,        0x09, 0x02, 1, 1 },
    { /* P3B6_FUSE_PAR_FLG_e, */  TLx493D_READ_MODE_e,        0x09, 0x01, 0, 1 },
    { /* P3B6_MODE_SEL_e, */      TLx493D_READ_WRITE_MODE_e,  0x0A, 0x80, 7, 1 },
    { /* P3B6_INT_DIS_e, */       TLx493D_READ_WRITE_MODE_e,  0x0A, 0x40, 6, 1 },
    { /* P3B6_COLLISION_DIS_e, */ TLx493D_READ_WRITE_MODE_e,  0x0A, 0x20, 5, 1 },
    { /* P3B6_WU_EN_e, */         TLx493D_READ_WRITE_MODE_e,  0x0A, 0x10, 4, 1 },
    { /* P3B6_TRIGGER_SEL_e, */   TLx493D_READ_WRITE_MODE_e,  0x0A, 0x0C, 2, 2 },
    { /* P3B6_PROT_SEL_e, */      TLx493D_READ_WRITE_MODE_e,  0x0A, 0x02, 1, 1 },
    { /* P3B6_CRC_WR_EN_e, */     TLx493D_READ_WRITE_MODE_e,  0x0A, 0x01, 0, 1 },
    { /* P3B6_CHANNEL_SEL_e, */   TLx493D_READ_WRITE_MODE_e,  0x0B, 0xF0, 4, 4 },
    { /* P3B6_F_UPDATE_SEL_e, */  TLx493D_READ_WRITE_MODE_e,  0x0B, 0x0C, 2, 2 },
    { /* P3B6_XTR_SHORT_EN_e, */  TLx493D_READ_WRITE_MODE_e,  0x0B, 0x02, 1, 1 },
    { /* P3B6_SHORT_EN_e, */      TLx493D_READ_WRITE_MODE_e,  0x0B, 0x01, 0, 1 },
    { /* P3B6_WU_XH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0C, 0xFF, 0, 8 },
    { /* P3B6_WU_XL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0D, 0xFF, 0, 8 },
    { /* P3B6_WU_YH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0E, 0xFF, 0, 8 },
    { /* P3B6_WU_YL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x0F, 0xFF, 0, 8 },
    { /* P3B6_WU_ZH_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x10, 0xFF, 0, 8 },
    { /* P3B6_WU_ZL_MSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x11, 0xFF, 0, 8 },
    { /* P3B6_WU_XH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x12, 0xC0, 6, 2 },
    { /* P3B6_WU_XL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x12, 0x30, 4, 2 },
    { /* P3B6_WU_YH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x12, 0x0C, 2, 2 },
    { /* P3B6_WU_YL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x12, 0x03, 0, 2 },
    { /* P3B6_WU_PAR_e, */        TLx493D_READ_WRITE_MODE_e,  0x13, 0x20, 5, 1 },
    { /* P3B6_WU_EN_CP_e, */      TLx493D_WRITE_MODE_e,       0x13, 0x10, 4, 1 },
    { /* P3B6_WU_ZH_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x13, 0x0C, 2, 2 },
    { /* P3B6_WU_ZL_LSBS_e, */    TLx493D_READ_WRITE_MODE_e,  0x13, 0x03, 0, 2 },
    { /* P3B6_RST_FLG_CLR_e, */   TLx493D_WRITE_MODE_e,       0x14, 0x02, 1, 1 },
    { /* P3B6_SOFT_RST_e, */      TLx493D_WRITE_MODE_e,       0x14, 0x01, 0, 1 },
    { /* P3B6_CHIP_ID_0_e, */     TLx493D_READ_MODE_e,        0x15, 0xFF, 0, 8 },
    { /* P3B6_CHIP_ID_1_e, */     TLx493D_READ_MODE_e,        0x16, 0xFF, 0, 8 },
    { /* P3B6_CHIP_ID_2_e, */     TLx493D_READ_MODE_e,        0x17, 0xFF, 0, 8 },
    { /* P3B6_CHIP_ID_3_e, */     TLx493D_READ_MODE_e,        0x18, 0xFF, 0, 8 },
    { /* P3B6_CHIP_ID_4_e, */     TLx493D_READ_MODE_e,        0x19, 0xFF, 0, 8 },
    { /* P3B6_ID_PAR_e, */        TLx493D_READ_MODE_e,        0x1A, 0x40, 6, 1 },
    { /* P3B6_CHIP_ID_5_e, */     TLx493D_READ_MODE_e,        0x1A, 0x3F, 0, 6 },

    /* From here on fields to be saved for proper handling of skip@read are listed. These are not part of the registers set !*/
    { /* P3B6_CHANNEL_SEL_SAVE_e, */ TLx493D_READ_WRITE_MODE_e,  0x1B, 0xF0, 4, 4 },
};


static TLx493D_CommonFunctions_t TLx493D_P3B6_commonFunctions = {
    .init                           = TLx493D_P3B6_init,
    .deinit                         = TLx493D_P3B6_deinit,

    .readRegisters                  = TLx493D_P3B6_readRegisters,
    .readRegistersAndCheck          = TLx493D_P3B6_readRegistersAndCheck,

    .calculateRawTemperature        = TLx493D_P3B6_calculateRawTemperature,
    .getRawTemperature              = TLx493D_P3B6_getRawTemperature,

    .calculateRawMagneticField      = TLx493D_P3B6_calculateRawMagneticField,
    .getRawMagneticField            = TLx493D_P3B6_getRawMagneticField,

    .calculateRawMagneticFieldAndTemperature = TLx493D_P3B6_calculateRawMagneticFieldAndTemperature,
    .getRawMagneticFieldAndTemperature       = TLx493D_P3B6_getRawMagneticFieldAndTemperature,

    .calculateTemperature           = TLx493D_P3B6_calculateTemperature,
    .getTemperature                 = TLx493D_P3B6_getTemperature,

    .calculateMagneticField         = TLx493D_P3B6_calculateMagneticField,
    .getMagneticField               = TLx493D_P3B6_getMagneticField,

    .calculateMagneticFieldAndTemperature = TLx493D_P3B6_calculateMagneticFieldAndTemperature,
    .getMagneticFieldAndTemperature = TLx493D_P3B6_getMagneticFieldAndTemperature,

    /** functions related to the "Config" register. */
    .setMeasurement                 = TLx493D_P3B6_setMeasurement,
    .setTrigger                     = TLx493D_P3B6_setTrigger,
    .setSensitivity                 = TLx493D_P3B6_setSensitivity,

    /** functions related to the "Mod1" and "Mod2" registers. */
    .setDefaultConfig               = TLx493D_P3B6_setDefaultConfig,
    .setIICAddress                  = TLx493D_P3B6_setIICAddress,
    .enable1ByteReadMode            = TLx493D_P3B6_enable1ByteReadMode,

    .enableInterrupt                = TLx493D_P3B6_enableInterrupt,
    .disableInterrupt               = TLx493D_P3B6_disableInterrupt,

    .enableCollisionAvoidance       = TLx493D_P3B6_enableCollisionAvoidance,
    .disableCollisionAvoidance      = TLx493D_P3B6_disableCollisionAvoidance,

    .setPowerMode                   = TLx493D_P3B6_setPowerMode,
    .setUpdateRate                  = TLx493D_P3B6_setUpdateRate,

    /** functions related to the "Diag" register. */
    .hasValidData                   = TLx493D_P3B6_hasValidData,
    .isFunctional                   = TLx493D_P3B6_isFunctional,

    /** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
    .hasWakeUp                      = TLx493D_P3B6_hasWakeUp,
    .isWakeUpEnabled                = TLx493D_P3B6_isWakeUpEnabled,
    .enableWakeUpMode               = TLx493D_P3B6_enableWakeUpMode,
    .disableWakeUpMode              = TLx493D_P3B6_disableWakeUpMode,

    .setWakeUpThresholdsAsInteger   = TLx493D_P3B6_setWakeUpThresholdsAsInteger,
    .setWakeUpThresholds            = TLx493D_P3B6_setWakeUpThresholds,

    .softwareReset                  = TLx493D_P3B6_softwareReset,

    .printRegisters                 = TLx493D_P3B6_printRegisters,

    /** functions used internally and not accessible through the common interface. */
    .calculateFuseParity            = TLx493D_P3B6_calculateFuseParity,
    .calculateBusParity             = TLx493D_P3B6_calculateBusParity,
    .calculateConfigurationParity   = TLx493D_P3B6_calculateConfigurationParity,

    .hasValidFuseParity             = TLx493D_P3B6_hasValidFuseParity,
    .hasValidBusParity              = TLx493D_P3B6_hasValidBusParity,
    .hasValidConfigurationParity    = TLx493D_P3B6_hasValidConfigurationParity,
 
    .hasValidWakeUpParity           = TLx493D_P3B6_hasValidWakeUpParity,
    .isInTestMode                   = TLx493D_P3B6_isInTestMode,
   
    .hasValidTBit                   = TLx493D_P3B6_hasValidTBit,
        
    .setResetValues                 = TLx493D_P3B6_setResetValues,

    .selectIICAddress               = TLx493D_P3B6_selectIICAddress,

    .calculateRawMagneticFieldAtTemperature = TLx493D_P3B6_calculateRawMagneticFieldAtTemperature,

    .getSensitivityScaleFactor      = TLx493D_P3B6_getSensitivityScaleFactor,
};


bool TLx493D_P3B6_init(TLx493D_t *sensor) {
    return tlx493d_common_init(sensor, GEN_3_REG_MAP_SIZE, TLx493D_P3B6_regDef, &TLx493D_P3B6_commonFunctions, TLx493D_P3B6_e, TLx493D_I2C_e);
}


bool TLx493D_P3B6_deinit(TLx493D_t *sensor) {
    return tlx493d_common_deinit(sensor);
}


bool TLx493D_P3B6_readRegisters(TLx493D_t *sensor) {
    return tlx493d_gen_3_readRegisters(sensor, P3B6_CHANNEL_SEL_SAVE_e);
}


bool TLx493D_P3B6_readRegistersAndCheck(TLx493D_t *sensor) {
    return tlx493d_common_readRegistersAndCheck(sensor);
}


void TLx493D_P3B6_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    tlx493d_gen_3_calculateRawTemperature(sensor, P3B6_TEMP_MSBS_e, P3B6_TEMP_LSBS_e, temperature);
}


bool TLx493D_P3B6_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    return tlx493d_common_getRawTemperature(sensor, temperature);
}


void TLx493D_P3B6_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_3_calculateRawMagneticField(sensor, P3B6_BX_MSBS_e, P3B6_BX_LSBS_e, P3B6_BY_MSBS_e, P3B6_BY_LSBS_e, P3B6_BZ_MSBS_e, P3B6_BZ_LSBS_e, x, y, z);
}


bool TLx493D_P3B6_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    return tlx493d_common_getRawMagneticField(sensor, x, y, z);
}


void TLx493D_P3B6_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    TLx493D_P3B6_calculateRawMagneticField(sensor, x, y, z);
    TLx493D_P3B6_calculateRawTemperature(sensor, temperature);
}


bool TLx493D_P3B6_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    return tlx493d_common_getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


void TLx493D_P3B6_calculateTemperature(TLx493D_t *sensor, double *temp) {
    tlx493d_gen_3_calculateTemperature(sensor, P3B6_TEMP_MSBS_e, P3B6_TEMP_LSBS_e, temp);
}


bool TLx493D_P3B6_getTemperature(TLx493D_t *sensor, double *temp) {
    return tlx493d_common_getTemperature(sensor, temp);
}


void TLx493D_P3B6_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    tlx493d_gen_3_calculateMagneticField(sensor, P3B6_BX_MSBS_e, P3B6_BX_LSBS_e, P3B6_BY_MSBS_e, P3B6_BY_LSBS_e, P3B6_BZ_MSBS_e, P3B6_BZ_LSBS_e, P3B6_TEMP_MSBS_e, P3B6_TEMP_LSBS_e, x, y, z);
}


bool TLx493D_P3B6_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
     return tlx493d_common_getMagneticField(sensor, x, y, z);
}


void TLx493D_P3B6_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    TLx493D_P3B6_calculateMagneticField(sensor, x, y, z);
    TLx493D_P3B6_calculateTemperature(sensor, temp);
}


bool TLx493D_P3B6_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    return tlx493d_common_getMagneticFieldAndTemperature(sensor, x, y, z, temp);
}


bool TLx493D_P3B6_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val) {
    return tlx493d_gen_3_setMeasurement(sensor, P3B6_CHANNEL_SEL_e, P3B6_CHANNEL_SEL_SAVE_e, val);
}


bool TLx493D_P3B6_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t val) {
    return tlx493d_gen_3_setTrigger(sensor, P3B6_TRIGGER_SEL_e, val);
}


bool TLx493D_P3B6_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val) {
    return tlx493d_gen_3_setSensitivity(sensor, P3B6_SHORT_EN_e, P3B6_XTR_SHORT_EN_e, val);
}


bool TLx493D_P3B6_setDefaultConfig(TLx493D_t *sensor) {
    bool b = tlx493d_gen_3_setDefaultConfig(sensor, P3B6_COLLISION_DIS_e, P3B6_INT_DIS_e);

    tlx493d_common_setBitfield(sensor, P3B6_RST_FLG_CLR_e, 1);
    b &= tlx493d_common_writeRegister(sensor, P3B6_RST_FLG_CLR_e);

    return b;
}


bool TLx493D_P3B6_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address) {
    return tlx493d_gen_3_setIICAddress(sensor, 0, address);
}


bool TLx493D_P3B6_enable1ByteReadMode(TLx493D_t *sensor) {
    return tlx493d_gen_3_set1ByteReadMode(sensor, P3B6_PROT_SEL_e, 1);
}


bool TLx493D_P3B6_enableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_3_setCollisionAvoidance(sensor, P3B6_COLLISION_DIS_e, 0);
}


bool TLx493D_P3B6_disableCollisionAvoidance(TLx493D_t *sensor) {
    return tlx493d_gen_3_setCollisionAvoidance(sensor, P3B6_COLLISION_DIS_e, 1);
}


bool TLx493D_P3B6_enableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_3_setInterrupt(sensor, P3B6_INT_DIS_e, 0);
}


bool TLx493D_P3B6_disableInterrupt(TLx493D_t *sensor) {
    return tlx493d_gen_3_setInterrupt(sensor, P3B6_INT_DIS_e, 1);
}


bool TLx493D_P3B6_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
    return tlx493d_gen_3_setPowerMode(sensor, P3B6_MODE_SEL_e, mode);
}


bool TLx493D_P3B6_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val) {
    return tlx493d_gen_3_setUpdateRate(sensor, P3B6_F_UPDATE_SEL_e, val);
}


bool TLx493D_P3B6_hasValidData(const TLx493D_t *sensor) {
    return tlx493d_gen_3_hasValidData(sensor, P3B6_MEAS_FLG_e);
}


bool TLx493D_P3B6_isFunctional(const TLx493D_t *sensor) {
    return tlx493d_gen_3_isFunctional(sensor);
}


bool TLx493D_P3B6_hasWakeUp(const TLx493D_t *sensor) {
    (void) sensor;
    return true;
}


bool TLx493D_P3B6_isWakeUpEnabled(const TLx493D_t *sensor) {
    return tlx493d_gen_3_isWakeUpEnabled(sensor, P3B6_WU_EN_e);
}


bool TLx493D_P3B6_enableWakeUpMode(TLx493D_t *sensor) {
    return tlx493d_gen_3_enableWakeUpMode(sensor, P3B6_WU_EN_e, P3B6_WU_EN_CP_e, P3B6_WU_PAR_e);
}


bool TLx493D_P3B6_disableWakeUpMode(TLx493D_t *sensor) {
    return tlx493d_gen_3_disableWakeUpMode(sensor, P3B6_INT_DIS_e, P3B6_WU_EN_e, P3B6_WU_EN_CP_e, P3B6_WU_PAR_e);

}


bool TLx493D_P3B6_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    return tlx493d_gen_3_setWakeUpThresholdsAsInteger(sensor, P3B6_WU_EN_e, P3B6_WU_EN_CP_e, P3B6_WU_PAR_e,
                                                      P3B6_WU_XL_MSBS_e, P3B6_WU_XL_LSBS_e, P3B6_WU_XH_MSBS_e, P3B6_WU_XH_LSBS_e,
                                                      P3B6_WU_YL_MSBS_e, P3B6_WU_YL_LSBS_e, P3B6_WU_YH_MSBS_e, P3B6_WU_YH_LSBS_e,
                                                      P3B6_WU_ZL_MSBS_e, P3B6_WU_ZL_LSBS_e, P3B6_WU_ZH_MSBS_e, P3B6_WU_ZH_LSBS_e,
                                                      xlTh, xhTh, ylTh, yhTh, zlTh, zhTh);
}


/** thesholds im mT, to be converted to proper format. */
bool TLx493D_P3B6_setWakeUpThresholds(TLx493D_t *sensor, double temperature,
                                      double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
    return tlx493d_gen_3_setWakeUpThresholds(sensor, P3B6_WU_EN_e, P3B6_WU_EN_CP_e, P3B6_WU_PAR_e,
                                             P3B6_WU_XL_MSBS_e, P3B6_WU_XL_LSBS_e, P3B6_WU_XH_MSBS_e, P3B6_WU_XH_LSBS_e,
                                             P3B6_WU_YL_MSBS_e, P3B6_WU_YL_LSBS_e, P3B6_WU_YH_MSBS_e, P3B6_WU_YH_LSBS_e,
                                             P3B6_WU_ZL_MSBS_e, P3B6_WU_ZL_LSBS_e, P3B6_WU_ZH_MSBS_e, P3B6_WU_ZH_LSBS_e,
                                             P3B6_SHORT_EN_e, P3B6_XTR_SHORT_EN_e,
                                             temperature, xLow, xHigh, yLow, yHigh, zLow, zHigh);
}


bool TLx493D_P3B6_softwareReset(TLx493D_t *sensor) {
    tlx493d_common_setBitfield(sensor, P3B6_RST_FLG_CLR_e, 1);

    return tlx493d_gen_3_softwareReset(sensor, P3B6_SOFT_RST_e);
}


bool tlx493d_P3B6_setWakeUpParity(TLx493D_t *sensor) {
    return tlx493d_gen_3_setWakeUpParity(sensor, P3B6_WU_EN_e, P3B6_WU_PAR_e);
}


uint8_t TLx493D_P3B6_calculateFuseParity(const TLx493D_t *sensor) {
     tlx493d_errorFunctionNotSupportedForSensorType(sensor, "calculateFuseParity");
    return 0;
}


uint8_t TLx493D_P3B6_calculateBusParity(const TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "calculateBusParity");
    return 0;
}


uint8_t TLx493D_P3B6_calculateConfigurationParity(TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "calculateConfigurationParity");
    return 0;
}


bool TLx493D_P3B6_hasValidFuseParity(const TLx493D_t *sensor) {
    return tlx493d_gen_3_hasValidFuseParity(sensor, P3B6_FUSE_PAR_FLG_e);
}


bool TLx493D_P3B6_hasValidBusParity(const TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "hasValidBusParity");
    return false;
}


bool TLx493D_P3B6_hasValidConfigurationParity(const TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "hasValidConfigurationParity");
    return false;
}


bool TLx493D_P3B6_hasValidWakeUpParity(const TLx493D_t *sensor) {
    return tlx493d_gen_3_hasValidWakeUpParity(sensor, P3B6_WU_PAR_FLG_e );
}


bool TLx493D_P3B6_isInTestMode(const TLx493D_t *sensor) {
    return tlx493d_gen_3_isInTestMode(sensor, P3B6_TEST_FLG_e );
}


bool TLx493D_P3B6_hasValidIICadr(const TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "hasValidIICadr");
    return false;
}


bool TLx493D_P3B6_hasValidTBit(const TLx493D_t *sensor) {
    tlx493d_errorFunctionNotSupportedForSensorType(sensor, "hasValidTBit");
    return false;
}


void TLx493D_P3B6_setResetValues(TLx493D_t *sensor) {
    sensor->regMap[0x0A] = 0x62; /** MOD1 */
    sensor->regMap[0x0B] = 0x00; /** MOD2 */

    /** for wake-up parity calculation. */
    sensor->regMap[0x0C] = 0x7F;
    sensor->regMap[0x0D] = 0x80;
    sensor->regMap[0x0E] = 0x7F;
    sensor->regMap[0x0F] = 0x80;  
    sensor->regMap[0x10] = 0x7F;
    sensor->regMap[0x11] = 0x80;
    sensor->regMap[0x12] = 0xCC;
    sensor->regMap[0x13] = 0x2C;

    /** P3B6_CHANNEL_SEL_SAVE_e */
    sensor->regMap[0x1B] = 0x00;
}


uint8_t TLx493D_P3B6_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    return tlx493d_gen_3_selectIICAddress(sensor, addr);
}



void TLx493D_P3B6_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_gen_3_calculateRawMagneticFieldAtTemperature(sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
}


double TLx493D_P3B6_getSensitivityScaleFactor(const TLx493D_t *sensor) {
    return tlx493d_gen_3_getSensitivityScaleFactor(sensor, TLx493D_HAS_X4_e, P3B6_SHORT_EN_e, P3B6_XTR_SHORT_EN_e);
}


void TLx493D_P3B6_printRegisters(const TLx493D_t *sensor) {
    logPrintRegisters(sensor, TLX493D_P3B6_REGISTER_HEADLINE); 
}
