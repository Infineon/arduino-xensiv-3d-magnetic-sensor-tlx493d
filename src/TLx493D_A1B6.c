/** std includes. */
#include <math.h>
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

/** sensor specicifc includes. */
#include "TLx493D_A1B6_defines.h"
#include "TLx493D_A1B6_enums.h"
#include "TLx493D_A1B6.h"


/** register enums. */
typedef enum {
    TLx493D_A1B6_Temp_ENABLE_default,
    TLx493D_A1B6_Temp_DISABLE
} TLx493D_A1B6_Reg_Temp_NEN;


typedef enum {
    TLx493D_A1B6_ODD_PARITY,
    TLx493D_A1B6_EVEN_PARITY
} TLx493D_A1B6_Reg_PARITY;


typedef enum {
    TLx493D_A1B6_INT_ENABLE_default,
    TLx493D_A1B6_INT_DISABLE
} TLx493D_A1B6_Reg_INT;


typedef enum {
    TLx493D_A1B6_FAST_MODE_DISABLE_default,
    TLx493D_A1B6_FAST_MODE_ENABLE
} TLx493D_A1B6_Reg_FAST_MODE_NEN;


typedef enum {
    TLx493D_A1B6_LOW_POWER_MODE_DISABLE_default,
    TLx493D_A1B6_LOW_POWER_MODE_ENABLE
} TLx493D_A1B6_Reg_LOW_POWER_MODE_NEN;


typedef enum {
    TLx493D_A1B6_PARITY_TEST_DISABLE,
    TLx493D_A1B6_PARITY_TEST_ENABLE_default
} TLx493D_A1B6_Reg_PARITY_TEST_NEN;


static TLx493D_Register_t TLx493D_A1B6_regDef[] = {
    /** Read registers. */
    { /* A1B6_BX_MSB_e, */        TLx493D_READ_MODE_e,     0x00, 0xFF, 0, 8 },
    { /* A1B6_BY_MSB_e, */        TLx493D_READ_MODE_e,     0x01, 0xFF, 0, 8 },
    { /* A1B6_BZ_MSB_e, */        TLx493D_READ_MODE_e,     0x02, 0xFF, 0, 8 },
    { /* A1B6_TEMP_MSB_e, */      TLx493D_READ_MODE_e,     0x03, 0xF0, 4, 4 },
    { /* A1B6_FRM_e, */           TLx493D_READ_MODE_e,     0x03, 0x0C, 2, 2 },
    { /* A1B6_CH_e, */            TLx493D_READ_MODE_e,     0x03, 0x03, 0, 2 },
    { /* A1B6_BX_LSB_e, */        TLx493D_READ_MODE_e,     0x04, 0xF0, 4, 4 },
    { /* A1B6_BY_LSB_e, */        TLx493D_READ_MODE_e,     0x04, 0x0F, 0, 4 },
    { /* A1B6_T_e, */             TLx493D_READ_MODE_e,     0x05, 0x40, 6, 1 },
    { /* A1B6_FF_e, */            TLx493D_READ_MODE_e,     0x05, 0x20, 5, 1 },
    { /* A1B6_PD_e, */            TLx493D_READ_MODE_e,     0x05, 0x10, 4, 1 },
    { /* A1B6_BZ_LSB_e, */        TLx493D_READ_MODE_e,     0x05, 0x0F, 0, 4 },
    { /* A1B6_TEMP_LSB_e, */      TLx493D_READ_MODE_e,     0x06, 0xFF, 0, 8 },
    { /* A1B6_R_RES_1_e, */       TLx493D_READ_MODE_e,     0x07, 0x18, 3, 2 },
    { /* A1B6_R_RES_2_e, */       TLx493D_READ_MODE_e,     0x08, 0xFF, 0, 8 },
    { /* A1B6_R_RES_3_e, */       TLx493D_READ_MODE_e,     0x09, 0x1F, 0, 5 },
    /** Write Registers. */
    { /* A1B6_W_RES_0_e, */       TLx493D_WRITE_MODE_e,    0x00, 0xFF, 0, 8 },
    { /* A1B6_P_e, */             TLx493D_WRITE_MODE_e,    0x01, 0x80, 7, 1 },
    { /* A1B6_IICADR_e, */        TLx493D_WRITE_MODE_e,    0x01, 0x60, 5, 2 },
    { /* A1B6_W_RES_1_e, */       TLx493D_WRITE_MODE_e,    0x01, 0x18, 3, 2 },
    { /* A1B6_INT_e, */           TLx493D_WRITE_MODE_e,    0x01, 0x04, 2, 1 },
    { /* A1B6_FAST_e, */          TLx493D_WRITE_MODE_e,    0x01, 0x02, 1, 1 },
    { /* A1B6_LOW_POWER_e, */     TLx493D_WRITE_MODE_e,    0x01, 0x01, 0, 1 },
    { /* A1B6_W_RES_2_e, */       TLx493D_WRITE_MODE_e,    0x02, 0xFF, 0, 8 },
    { /* A1B6_Temp_NEN_e, */      TLx493D_WRITE_MODE_e,    0x03, 0x80, 7, 1 },
    { /* A1B6_LP_e, */            TLx493D_WRITE_MODE_e,    0x03, 0x40, 6, 1 },
    { /* A1B6_PT_e, */            TLx493D_WRITE_MODE_e,    0x03, 0x20, 5, 1 },
    { /* A1B6_W_RES_3_e, */       TLx493D_WRITE_MODE_e,    0x03, 0x1F, 0, 5 },
};

static TLx493D_A1B6_PowerModeCombinations_t TLx493D_A1B6_PowerModeCombinations[] = {
    { 0, 0, 0, 1000 },		    /** POWERDOWNMODE */
	{ 1, 0, 0, 0    },			/** FASTMODE */
	{ 0, 1, 1, 10   },		    /** LOWPOWERMODE */
	{ 0, 1, 0, 100  },		    /** ULTRALOWPOWERMODE */
	{ 1, 1, 1, 10   },			/** MASTERCONTROLLEDMODE */
};


static TLx493D_CommonFunctions_t TLx493D_A1B6_commonFunctions = {
    .init                           = TLx493D_A1B6_init,
    .deinit                         = TLx493D_A1B6_deinit,

    .readRegisters                  = TLx493D_A1B6_readRegisters,
    .readRegistersAndCheck          = TLx493D_A1B6_readRegistersAndCheck,

    .calculateRawTemperature        = TLx493D_A1B6_calculateRawTemperature,
    .getRawTemperature              = TLx493D_A1B6_getRawTemperature,

    .calculateRawMagneticField      = TLx493D_A1B6_calculateRawMagneticField,
    .getRawMagneticField            = TLx493D_A1B6_getRawMagneticField,

    .calculateRawMagneticFieldAndTemperature = TLx493D_A1B6_calculateRawMagneticFieldAndTemperature,
    .getRawMagneticFieldAndTemperature       = TLx493D_A1B6_getRawMagneticFieldAndTemperature,

    .calculateTemperature           = TLx493D_A1B6_calculateTemperature,
    .getTemperature                 = TLx493D_A1B6_getTemperature,

    .calculateMagneticField         = TLx493D_A1B6_calculateMagneticField,
    .getMagneticField               = TLx493D_A1B6_getMagneticField,

    .calculateMagneticFieldAndTemperature = TLx493D_A1B6_calculateMagneticFieldAndTemperature,
    .getMagneticFieldAndTemperature = TLx493D_A1B6_getMagneticFieldAndTemperature,

    /** functions related to the "Config" register. */
    .setMeasurement                 = TLx493D_A1B6_setMeasurement,
    .setTrigger                     = TLx493D_A1B6_setTrigger,
    .setSensitivity                 = TLx493D_A1B6_setSensitivity,
    
    /** functions related to the "Mod" register. */
    .setDefaultConfig               = TLx493D_A1B6_setDefaultConfig,
    .setIICAddress                  = TLx493D_A1B6_setIICAddress,
    .enable1ByteReadMode            = TLx493D_A1B6_enable1ByteReadMode,

    .enableInterrupt                = TLx493D_A1B6_enableInterrupt,
    .disableInterrupt               = TLx493D_A1B6_disableInterrupt,

    .enableCollisionAvoidance       = TLx493D_A1B6_enableCollisionAvoidance,
    .disableCollisionAvoidance      = TLx493D_A1B6_disableCollisionAvoidance,

    .setPowerMode                   = TLx493D_A1B6_setPowerMode,
    .setUpdateRate                  = TLx493D_A1B6_setUpdateRate,

    /** functions related to the "Diag" register. */
    .hasValidData                   = TLx493D_A1B6_hasValidData,
    .isFunctional                   = TLx493D_A1B6_isFunctional,

    /** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
    .hasWakeUp                      = TLx493D_A1B6_hasWakeUp,
    .isWakeUpEnabled                = TLx493D_A1B6_isWakeUpEnabled,
    .enableWakeUpMode               = TLx493D_A1B6_enableWakeUpMode,
    .disableWakeUpMode              = TLx493D_A1B6_disableWakeUpMode,

    .setWakeUpThresholdsAsInteger   = TLx493D_A1B6_setWakeUpThresholdsAsInteger,
    .setWakeUpThresholds            = TLx493D_A1B6_setWakeUpThresholds,

    .softwareReset                  = TLx493D_A1B6_softwareReset,

    .printRegisters                 = TLx493D_A1B6_printRegisters,

    /** functions used internally and not accessible through the common interface. */
    .calculateFuseParity            = TLx493D_A1B6_calculateFuseParity,
    .calculateBusParity             = TLx493D_A1B6_calculateBusParity,
    .calculateConfigurationParity   = TLx493D_A1B6_calculateConfigurationParity,

    .hasValidFuseParity             = TLx493D_A1B6_hasValidFuseParity,
    .hasValidBusParity              = TLx493D_A1B6_hasValidBusParity,
    .hasValidConfigurationParity    = TLx493D_A1B6_hasValidConfigurationParity,
 
    .hasValidWakeUpParity           = TLx493D_A1B6_hasValidWakeUpParity,
    .isInTestMode                   = TLx493D_A1B6_isInTestMode,
    
    .hasValidTBit                   = TLx493D_A1B6_hasValidTBit,

    .setResetValues                 = TLx493D_A1B6_setResetValues,

    .selectIICAddress               = TLx493D_A1B6_selectIICAddress,

    .calculateRawMagneticFieldAtTemperature  = TLx493D_A1B6_calculateRawMagneticFieldAtTemperature,

    .getSensitivityScaleFactor      = TLx493D_A1B6_getSensitivityScaleFactor,
};


/** note: make sure that the init function is called at reset to make sure the write default values are in sync. */
bool TLx493D_A1B6_init(TLx493D_t *sensor) {
    return tlx493d_common_init(sensor, GEN_1_REG_MAP_SIZE, TLx493D_A1B6_regDef, &TLx493D_A1B6_commonFunctions, TLx493D_A1B6_e, TLx493D_I2C_e);
}

bool TLx493D_A1B6_deinit(TLx493D_t *sensor) {
    return tlx493d_common_deinit(sensor);
}


bool TLx493D_A1B6_readRegisters(TLx493D_t *sensor) {
    return tlx493d_transfer(sensor, NULL, 0, sensor->regMap, GEN_1_READ_REGISTERS_MAX_COUNT);
}


bool TLx493D_A1B6_readRegistersAndCheck(TLx493D_t *sensor) {
    return TLx493D_A1B6_readRegisters(sensor);
}


void TLx493D_A1B6_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    tlx493d_common_calculateRawTemperature(sensor, A1B6_TEMP_MSB_e, A1B6_TEMP_LSB_e, temperature);
}


bool TLx493D_A1B6_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    return tlx493d_common_getRawTemperature(sensor, temperature);
}


void TLx493D_A1B6_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_common_calculateRawMagneticField(sensor, A1B6_BX_MSB_e, A1B6_BX_LSB_e, A1B6_BY_MSB_e, A1B6_BY_LSB_e, A1B6_BZ_MSB_e, A1B6_BZ_LSB_e, x, y, z);
}


bool TLx493D_A1B6_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    return tlx493d_common_getRawMagneticField(sensor, x, y, z);
}


void TLx493D_A1B6_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    TLx493D_A1B6_calculateRawMagneticField(sensor, x, y, z);
    TLx493D_A1B6_calculateRawTemperature(sensor, temperature);
}


bool TLx493D_A1B6_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
    return tlx493d_common_getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


void TLx493D_A1B6_calculateTemperature(TLx493D_t *sensor, double *temp) {
    int16_t value = 0;
    tlx493d_common_concatBytes(sensor, A1B6_TEMP_MSB_e, A1B6_TEMP_LSB_e, &value);
    
    *temp = (((double) value - GEN_1_TEMP_OFFSET) * GEN_1_TEMP_MULT) + GEN_1_REF_TEMP;
}

bool TLx493D_A1B6_getTemperature(TLx493D_t *sensor, double *temp) {
    return tlx493d_common_getTemperature(sensor, temp);
}

void TLx493D_A1B6_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    int16_t valueX = 0, valueY = 0, valueZ = 0;

    tlx493d_common_concatBytes(sensor, A1B6_BX_MSB_e, A1B6_BX_LSB_e, &valueX);
    tlx493d_common_concatBytes(sensor, A1B6_BY_MSB_e, A1B6_BY_LSB_e, &valueY);
    tlx493d_common_concatBytes(sensor, A1B6_BZ_MSB_e, A1B6_BZ_LSB_e, &valueZ);

    *x = ((double) valueX) * GEN_1_MAG_FIELD_MULT;
    *y = ((double) valueY) * GEN_1_MAG_FIELD_MULT;
    *z = ((double) valueZ) * GEN_1_MAG_FIELD_MULT;
}

bool TLx493D_A1B6_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z) {
    return tlx493d_common_getMagneticField(sensor, x, y, z);
}

void TLx493D_A1B6_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    TLx493D_A1B6_calculateMagneticField(sensor, x, y, z);
    TLx493D_A1B6_calculateTemperature(sensor, temp);
}

bool TLx493D_A1B6_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp) {
    return tlx493d_common_getMagneticFieldAndTemperature(sensor, x, y, z, temp);
}

bool TLx493D_A1B6_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val) {
    uint8_t temp_nen = 0;

    switch(val) {
        case TLx493D_BxByBzTemp_e : temp_nen = TLx493D_A1B6_Temp_ENABLE_default;
                                    break;

        case TLx493D_BxByBz_e : temp_nen = TLx493D_A1B6_Temp_DISABLE;         
                                break;
        
        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, val, "TLx493D_MeasurementType_t");
                  return false;
    }

    TLx493D_A1B6_setBitfield(sensor, A1B6_Temp_NEN_e, temp_nen);
    TLx493D_A1B6_calculateConfigurationParity(sensor);

    return TLx493D_A1B6_transferWriteRegisters(sensor);
}

 /** This option depends on PR and MODE. */
bool TLx493D_A1B6_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t val) {
    (void) val;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setTrigger");
    return false;
}


bool TLx493D_A1B6_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val) {
    (void) val;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setSensitivity");
    return false;
}


bool TLx493D_A1B6_setDefaultConfig(TLx493D_t *sensor) {  
    bool ret = true;
    /** read READ register values. */
    ret = TLx493D_A1B6_readRegisters(sensor);
    
    /** set WRITE register values to 0x00. */
    memset(sensor->regMap + GEN_1_WRITE_REGISTERS_OFFSET, 0, GEN_1_WRITE_REGISTERS_MAX_COUNT);

    /** set WRITE reserved register values from READ reserved register values. */
    TLx493D_A1B6_setReservedRegisterValues(sensor);

    /** enable parity test and write to registers. */
    ret &= TLx493D_A1B6_enableParityTest(sensor);

    /** set to MASTERCONTROLLEDMODE to start measurement. */
    TLx493D_A1B6_setPowerMode(sensor, TLx493D_MASTER_CONTROLLED_MODE_e);

    /** calculate parity. */
    TLx493D_A1B6_calculateConfigurationParity(sensor);

    /** write out register map to registers. */
    ret &= TLx493D_A1B6_transferWriteRegisters(sensor);

    /** update register map. */
    ret &= TLx493D_A1B6_readRegisters(sensor);

    return ret;  
}

/** Addresses for generation 1. */
/** (A0-A3 - for SDA/ADDR high at power-up). */
/** (A4-A7 - for SDA/ADDR low at power-up). */
bool TLx493D_A1B6_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    uint8_t bitfieldValue = 0;
    uint8_t deviceAddress = 0;

    switch (addr) {
        case TLx493D_IIC_ADDR_A0_e:
            bitfieldValue = 0b00;
            deviceAddress = 0xBC;
            break;

        case TLx493D_IIC_ADDR_A1_e:
            bitfieldValue = 0b01;
            deviceAddress = 0xB4;
            break;

        case TLx493D_IIC_ADDR_A2_e:
            bitfieldValue = 0b10;
            deviceAddress = 0x9C;
            break;

        case TLx493D_IIC_ADDR_A3_e:
            bitfieldValue = 0b11;
            deviceAddress = 0x94;
            break;

        case TLx493D_IIC_ADDR_A4_e:
            bitfieldValue = 0b00;
            deviceAddress = 0x3E;
            break;

        case TLx493D_IIC_ADDR_A5_e:
            bitfieldValue = 0b01;
            deviceAddress = 0x36;
            break;

        case TLx493D_IIC_ADDR_A6_e:
            bitfieldValue = 0b10;
            deviceAddress = 0x1E;
            break;

        case TLx493D_IIC_ADDR_A7_e:
            bitfieldValue = 0b11;
            deviceAddress = 0x16;
            break;        

        default:
            return false;
    }

    TLx493D_A1B6_setBitfield(sensor, A1B6_IICADR_e, bitfieldValue);
    TLx493D_A1B6_calculateConfigurationParity(sensor);
    bool ret = TLx493D_A1B6_transferWriteRegisters(sensor);

    tlx493d_common_setIICAddress(sensor, deviceAddress);

    return ret;
}


bool TLx493D_A1B6_enable1ByteReadMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "enable1ByteReadMode");
    return false;
}


bool TLx493D_A1B6_enableCollisionAvoidance(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "enableCollisionAvoidance");
    return false;
}


bool TLx493D_A1B6_disableCollisionAvoidance(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "disableCollisionAvoidance");
    return false;
}

bool TLx493D_A1B6_enableInterrupt(TLx493D_t *sensor) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_INT_e, TLx493D_A1B6_INT_ENABLE_default);
    TLx493D_A1B6_calculateConfigurationParity(sensor);

    return TLx493D_A1B6_transferWriteRegisters(sensor);
}


bool TLx493D_A1B6_disableInterrupt(TLx493D_t *sensor) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_INT_e, TLx493D_A1B6_INT_DISABLE);
    TLx493D_A1B6_calculateConfigurationParity(sensor);

    return TLx493D_A1B6_transferWriteRegisters(sensor);
}


bool TLx493D_A1B6_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_FAST_e, TLx493D_A1B6_PowerModeCombinations[mode].FAST);
    TLx493D_A1B6_setBitfield(sensor, A1B6_LOW_POWER_e, TLx493D_A1B6_PowerModeCombinations[mode].LOW_POWER);
    TLx493D_A1B6_setBitfield(sensor, A1B6_LP_e, TLx493D_A1B6_PowerModeCombinations[mode].LP);
    TLx493D_A1B6_calculateConfigurationParity(sensor);

    return TLx493D_A1B6_transferWriteRegisters(sensor);
}


bool TLx493D_A1B6_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val) {
    (void) val;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setUpdateRate");
    return false;
}


bool TLx493D_A1B6_hasValidData(const TLx493D_t *sensor){
    return TLx493D_A1B6_hasValidTBit(sensor) && TLx493D_A1B6_hasValidPDBit(sensor);
}


bool TLx493D_A1B6_isFunctional(const TLx493D_t *sensor){
    return TLx493D_A1B6_hasValidFuseParity(sensor);
}


bool TLx493D_A1B6_hasWakeUp(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasWakeUp");
    return false;
}


bool TLx493D_A1B6_isWakeUpEnabled(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isWakeUpEnabled");
    return false;
}

bool TLx493D_A1B6_enableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "enableWakeUpMode");
    return false;
}

bool TLx493D_A1B6_disableWakeUpMode(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "disableWakeUpMode");
    return false;
}


bool TLx493D_A1B6_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh) {
    (void) xlTh;
    (void) xhTh;
    (void) ylTh;
    (void) yhTh;
    (void) zlTh;
    (void) zhTh;

    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "setWakeUpThresholdsAsInteger");
    return false;
}

bool TLx493D_A1B6_setWakeUpThresholds(TLx493D_t *sensor, double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
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

bool TLx493D_A1B6_softwareReset(TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "softwareReset");
    return false;
}


uint8_t TLx493D_A1B6_calculateFuseParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "calculateFuseParity");
    return false;
}


uint8_t TLx493D_A1B6_calculateBusParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "calculateBusParity");
    return false;
}


/** parity is calculated for all the WRITE register, including the parity bit. */
uint8_t TLx493D_A1B6_calculateConfigurationParity(TLx493D_t *sensor) {
    uint8_t result = 0x00;

    /**set parity as EVEN first. */
    TLx493D_A1B6_setBitfield(sensor, A1B6_P_e, TLx493D_A1B6_EVEN_PARITY); 

    /** calculate bitwise XOR for all WRITE registers. */
    for (uint8_t addr = 0x00; addr<GEN_1_WRITE_REGISTERS_MAX_COUNT; addr++) {
        result ^= sensor->regMap[addr+GEN_1_WRITE_REGISTERS_OFFSET];
    }

    /** then set calculated parity. */
    TLx493D_A1B6_setBitfield(sensor, A1B6_P_e, tlx493d_common_calculateParity(result));

    return 1;
}


bool TLx493D_A1B6_hasValidFuseParity(const TLx493D_t *sensor){
    TLx493D_Register_t *bf = &sensor->regDef[A1B6_FF_e];
    return ((sensor->regMap[bf->address] & bf->mask) != 0);
}


bool TLx493D_A1B6_hasValidBusParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidBusParity");
    return false;
}


bool TLx493D_A1B6_hasValidConfigurationParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidConfigurationParity");
    return false;
}


bool TLx493D_A1B6_hasValidWakeUpParity(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidWakeUpParity");
    return false;
}


bool TLx493D_A1B6_isInTestMode(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "isInTestMode");
    return false;
}


bool TLx493D_A1B6_hasValidIICadr(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "hasValidIICadr");
    return false;
}


bool TLx493D_A1B6_hasValidTBit(const TLx493D_t *sensor) {
    TLx493D_Register_t *bf = &sensor->regDef[A1B6_T_e];
    return ((sensor->regMap[bf->address] & bf->mask) == 0);
}


void TLx493D_A1B6_setResetValues(TLx493D_t *sensor) {
    TLx493D_A1B6_setReservedRegisterValues(sensor);
}


void TLx493D_A1B6_setReservedRegisterValues(TLx493D_t *sensor) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_W_RES_1_e, TLx493D_A1B6_returnBitfield(sensor, A1B6_R_RES_1_e));
    TLx493D_A1B6_setBitfield(sensor, A1B6_W_RES_2_e, TLx493D_A1B6_returnBitfield(sensor, A1B6_R_RES_2_e));
    TLx493D_A1B6_setBitfield(sensor, A1B6_W_RES_3_e, TLx493D_A1B6_returnBitfield(sensor, A1B6_R_RES_3_e));
}

/** Addresses for generation 1. */
/** (A0-A3 - for SDA/ADDR high at power-up). */
/** (A4-A7 - for SDA/ADDR low at power-up). */

uint8_t TLx493D_A1B6_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
    switch(addr) {
        case TLx493D_IIC_ADDR_A0_e : return GEN_1_STD_IIC_ADDR_WRITE_A0;

        case TLx493D_IIC_ADDR_A1_e : return GEN_1_STD_IIC_ADDR_WRITE_A1;

        case TLx493D_IIC_ADDR_A2_e : return GEN_1_STD_IIC_ADDR_WRITE_A2;

        case TLx493D_IIC_ADDR_A3_e : return GEN_1_STD_IIC_ADDR_WRITE_A3;

        case TLx493D_IIC_ADDR_A4_e : return GEN_1_STD_IIC_ADDR_WRITE_A4;

        case TLx493D_IIC_ADDR_A5_e : return GEN_1_STD_IIC_ADDR_WRITE_A5;

        case TLx493D_IIC_ADDR_A6_e : return GEN_1_STD_IIC_ADDR_WRITE_A6;

        case TLx493D_IIC_ADDR_A7_e : return GEN_1_STD_IIC_ADDR_WRITE_A7;

        default : tlx493d_errorSelectionNotSupportedForSensorType(sensor, addr, "TLx493D_IICAddressType_t");
                  return 0;
    }
}

void TLx493D_A1B6_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT, int16_t *x, int16_t *y, int16_t *z) {
    (void) sensor;
    (void) rawTemp;
    (void) sens;

    *x = (int16_t) lround(xInmT / GEN_1_MAG_FIELD_MULT);
    *y = (int16_t) lround(yInmT / GEN_1_MAG_FIELD_MULT);
    *z = (int16_t) lround(zInmT / GEN_1_MAG_FIELD_MULT);
}


double TLx493D_A1B6_getSensitivityScaleFactor(const TLx493D_t *sensor) {
    tlx493d_warnFeatureNotAvailableForSensorType(sensor, "getSensitivityScaleFactor");
    return 0.0;
}


bool TLx493D_A1B6_enableParityTest(TLx493D_t *sensor) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_PT_e, TLx493D_A1B6_PARITY_TEST_ENABLE_default);
    TLx493D_A1B6_calculateConfigurationParity(sensor);
    return TLx493D_A1B6_transferWriteRegisters(sensor);
}

bool TLx493D_A1B6_disableParityTest(TLx493D_t *sensor) {
    TLx493D_A1B6_setBitfield(sensor, A1B6_PT_e, TLx493D_A1B6_PARITY_TEST_DISABLE);
    TLx493D_A1B6_calculateConfigurationParity(sensor);
    return TLx493D_A1B6_transferWriteRegisters(sensor);
}

uint8_t TLx493D_A1B6_returnBitfield(TLx493D_t *sensor, uint8_t bitField) {
    const TLx493D_Register_t *bf = &sensor->regDef[bitField];
    uint8_t bitFieldValue;

    if(bf->accessMode == TLx493D_READ_MODE_e) {
        bitFieldValue = (sensor->regMap[bf->address] & bf->mask) >> bf->offset;
    }
    else {
        tlx493d_errorBitfieldNotReadableForSensorType(sensor, bitField);
        return 0;
    }

    return bitFieldValue;
}

void TLx493D_A1B6_setBitfield(TLx493D_t *sensor, uint8_t bitField, uint8_t newBitFieldValue) {
    const TLx493D_Register_t *bf = &sensor->regDef[bitField];
    
    if(bf->accessMode == TLx493D_WRITE_MODE_e) {
        sensor->regMap[bf->address + GEN_1_WRITE_REGISTERS_OFFSET] = (sensor->regMap[bf->address + GEN_1_WRITE_REGISTERS_OFFSET] & ~bf->mask) | (newBitFieldValue << bf->offset);
    }
    else {
        tlx493d_errorBitfieldNotWritableForSensorType(sensor, bitField);

    }
}

bool TLx493D_A1B6_transferWriteRegisters(TLx493D_t *sensor) {
    return tlx493d_transfer(sensor, sensor->regMap + GEN_1_WRITE_REGISTERS_OFFSET, GEN_1_WRITE_REGISTERS_MAX_COUNT, NULL, 0);
}

bool TLx493D_A1B6_hasValidPDBit(const TLx493D_t *sensor) {
    const TLx493D_Register_t *bf = &sensor->regDef[A1B6_PD_e];
    return ((sensor->regMap[bf->address] & bf->mask) != 0);
}


void TLx493D_A1B6_printRegisters(const TLx493D_t *sensor) {
    logPrintRegisters(sensor, TLX493D_A1B6_REGISTER_HEADLINE); 
}
