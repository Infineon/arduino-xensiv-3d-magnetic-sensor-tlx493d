#ifndef TLX493D_P3I8_H
#define TLX493D_P3I8_H


/** std includes. */
#include <stdbool.h>
#include <stdint.h>

/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


/** common functions. */
bool TLx493D_P3I8_init(TLx493D_t *sensor);
bool TLx493D_P3I8_deinit(TLx493D_t *sensor);

bool TLx493D_P3I8_readRegisters(TLx493D_t *sensor);
bool TLx493D_P3I8_readRegistersAndCheck(TLx493D_t *sensor);

void TLx493D_P3I8_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature);
bool TLx493D_P3I8_getRawTemperature(TLx493D_t *sensor, int16_t *temperature);

void TLx493D_P3I8_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);
bool TLx493D_P3I8_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);

void TLx493D_P3I8_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);
bool TLx493D_P3I8_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);

void TLx493D_P3I8_calculateTemperature(TLx493D_t *sensor, double *temp);
bool TLx493D_P3I8_getTemperature(TLx493D_t *sensor, double *temp);

void TLx493D_P3I8_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);
bool TLx493D_P3I8_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);

void TLx493D_P3I8_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);
bool TLx493D_P3I8_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);

bool TLx493D_P3I8_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t val);
bool TLx493D_P3I8_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t val);
bool TLx493D_P3I8_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t val);

bool TLx493D_P3I8_setDefaultConfig(TLx493D_t *sensor);
bool TLx493D_P3I8_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address);
bool TLx493D_P3I8_enable1ByteReadMode(TLx493D_t *sensor);

bool TLx493D_P3I8_enableCollisionAvoidance(TLx493D_t *sensor);
bool TLx493D_P3I8_disableCollisionAvoidance(TLx493D_t *sensor);

bool TLx493D_P3I8_enableInterrupt(TLx493D_t *sensor);
bool TLx493D_P3I8_disableInterrupt(TLx493D_t *sensor);

bool TLx493D_P3I8_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode);
bool TLx493D_P3I8_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t val);

bool TLx493D_P3I8_hasValidData(const TLx493D_t *sensor);
bool TLx493D_P3I8_isFunctional(const TLx493D_t *sensor);

bool TLx493D_P3I8_hasWakeUp(const TLx493D_t *sensor);
bool TLx493D_P3I8_isWakeUpEnabled(const TLx493D_t *sensor);
bool TLx493D_P3I8_enableWakeUpMode(TLx493D_t *sensor);
bool TLx493D_P3I8_disableWakeUpMode(TLx493D_t *sensor);
bool TLx493D_P3I8_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh);
bool TLx493D_P3I8_setWakeUpThresholds(TLx493D_t *sensor, double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);

bool TLx493D_P3I8_softwareReset(TLx493D_t *sensor);


/** utilities. */
bool tlx493d_P3I8_setWakeUpParity(TLx493D_t *sensor);

uint8_t TLx493D_P3I8_calculateFuseParity(const TLx493D_t *sensor);
uint8_t TLx493D_P3I8_calculateBusParity(const TLx493D_t *sensor);
uint8_t TLx493D_P3I8_calculateConfigurationParity(TLx493D_t *sensor);

bool TLx493D_P3I8_hasValidFuseParity(const TLx493D_t *sensor);
bool TLx493D_P3I8_hasValidBusParity(const TLx493D_t *sensor);
bool TLx493D_P3I8_hasValidConfigurationParity(const TLx493D_t *sensor);

bool TLx493D_P3I8_hasValidWakeUpParity(const TLx493D_t *sensor);
bool TLx493D_P3I8_isInTestMode(const TLx493D_t *sensor);

bool TLx493D_P3I8_hasValidTBit(const TLx493D_t *sensor);
bool TLx493D_P3I8_hasValidIICadr(const TLx493D_t *sensor);

void TLx493D_P3I8_setResetValues(TLx493D_t *sensor);

uint8_t TLx493D_P3I8_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

void TLx493D_P3I8_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z);

double TLx493D_P3I8_getSensitivityScaleFactor(const TLx493D_t *sensor);

void TLx493D_P3I8_printRegisters(const TLx493D_t *sensor);


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_P3I8_H */
