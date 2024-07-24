#ifndef TLX493D_A2BW_H_
#define TLX493D_A2BW_H_


/** std includes. */
#include <stdbool.h>
#include <stdint.h>

/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


/** common functions. */
bool TLx493D_A2BW_init(TLx493D_t *sensor);
bool TLx493D_A2BW_deinit(TLx493D_t *sensor);

bool TLx493D_A2BW_readRegisters(TLx493D_t *sensor);
bool TLx493D_A2BW_readRegistersAndCheck(TLx493D_t *sensor);

void TLx493D_A2BW_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature);
bool TLx493D_A2BW_getRawTemperature(TLx493D_t *sensor, int16_t *temperature);

void TLx493D_A2BW_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);
bool TLx493D_A2BW_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);

void TLx493D_A2BW_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);
bool TLx493D_A2BW_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);

void TLx493D_A2BW_calculateTemperature(TLx493D_t *sensor, double *temp);

bool TLx493D_A2BW_getTemperature(TLx493D_t *sensor, double *temp);

void TLx493D_A2BW_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);

bool TLx493D_A2BW_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);


void TLx493D_A2BW_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);
bool TLx493D_A2BW_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);

bool TLx493D_A2BW_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t mVals);
bool TLx493D_A2BW_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t trig);
bool TLx493D_A2BW_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t sens);

bool TLx493D_A2BW_setDefaultConfig(TLx493D_t *sensor);
bool TLx493D_A2BW_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address);

bool TLx493D_A2BW_enable1ByteReadMode(TLx493D_t *sensor);

bool TLx493D_A2BW_enableCollisionAvoidance(TLx493D_t *sensor);
bool TLx493D_A2BW_disableCollisionAvoidance(TLx493D_t *sensor);

bool TLx493D_A2BW_enableInterrupt(TLx493D_t *sensor);
bool TLx493D_A2BW_disableInterrupt(TLx493D_t *sensor);


bool TLx493D_A2BW_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode);
bool TLx493D_A2BW_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t ur);


bool TLx493D_A2BW_hasValidData(const TLx493D_t *sensor);
bool TLx493D_A2BW_isFunctional(const TLx493D_t *sensor);

bool TLx493D_A2BW_hasWakeUp(const TLx493D_t *sensor);

bool TLx493D_A2BW_isWakeUpEnabled(const TLx493D_t *sensor);

bool TLx493D_A2BW_enableWakeUpMode(TLx493D_t *sensor);
bool TLx493D_A2BW_disableWakeUpMode(TLx493D_t *sensor);

bool TLx493D_A2BW_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh);
bool TLx493D_A2BW_setWakeUpThresholds(TLx493D_t *sensor, double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);

bool TLx493D_A2BW_softwareReset(TLx493D_t *sensor);

/** utilities. */
uint8_t TLx493D_A2BW_calculateFuseParity(const TLx493D_t *sensor);
uint8_t TLx493D_A2BW_calculateBusParity(const TLx493D_t *sensor);
uint8_t TLx493D_A2BW_calculateConfigurationParity(TLx493D_t *sensor);

bool TLx493D_A2BW_hasValidFuseParity(const TLx493D_t *sensor);
bool TLx493D_A2BW_hasValidBusParity(const TLx493D_t *sensor);
bool TLx493D_A2BW_hasValidConfigurationParity(const TLx493D_t *sensor);

bool TLx493D_A2BW_hasValidWakeUpParity(const TLx493D_t *sensor);
bool TLx493D_A2BW_isInTestMode(const TLx493D_t *sensor);

bool TLx493D_A2BW_hasValidTBit(const TLx493D_t *sensor);
bool TLx493D_A2BW_hasValidIICadr(const TLx493D_t *sensor);

void TLx493D_A2BW_setResetValues(TLx493D_t *sensor);

uint8_t TLx493D_A2BW_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

void TLx493D_A2BW_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z);

double TLx493D_A2BW_getSensitivityScaleFactor(const TLx493D_t *sensor);

void TLx493D_A2BW_printRegisters(const TLx493D_t *sensor);


#ifdef __cplusplus

}


#endif


#endif /** TLX493D_A2BW_H */