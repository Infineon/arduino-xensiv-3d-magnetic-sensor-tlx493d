#ifndef TLX493D_W2BW_H_
#define TLX493D_W2BW_H_


/** std includes. */
#include <stdbool.h>
#include <stdint.h>

/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


/** common functions. */
bool TLx493D_W2BW_init(TLx493D_t *sensor);
bool TLx493D_W2BW_deinit(TLx493D_t *sensor);

bool TLx493D_W2BW_readRegisters(TLx493D_t *sensor);
bool TLx493D_W2BW_readRegistersAndCheck(TLx493D_t *sensor);

void TLx493D_W2BW_calculateRawTemperature(TLx493D_t *sensor, int16_t *temperature);
bool TLx493D_W2BW_getRawTemperature(TLx493D_t *sensor, int16_t *temperature);

void TLx493D_W2BW_calculateRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);
bool TLx493D_W2BW_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);

void TLx493D_W2BW_calculateRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);
bool TLx493D_W2BW_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);

void TLx493D_W2BW_calculateTemperature(TLx493D_t *sensor, double *temp);

bool TLx493D_W2BW_getTemperature(TLx493D_t *sensor, double *temp);

void TLx493D_W2BW_calculateMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);

bool TLx493D_W2BW_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);


void TLx493D_W2BW_calculateMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);
bool TLx493D_W2BW_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temp);

bool TLx493D_W2BW_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t mVals);
bool TLx493D_W2BW_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t trig);
bool TLx493D_W2BW_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t sens);

bool TLx493D_W2BW_setDefaultConfig(TLx493D_t *sensor);
bool TLx493D_W2BW_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t address);

bool TLx493D_W2BW_enable1ByteReadMode(TLx493D_t *sensor);

bool TLx493D_W2BW_enableCollisionAvoidance(TLx493D_t *sensor);
bool TLx493D_W2BW_disableCollisionAvoidance(TLx493D_t *sensor);

bool TLx493D_W2BW_enableInterrupt(TLx493D_t *sensor);
bool TLx493D_W2BW_disableInterrupt(TLx493D_t *sensor);


bool TLx493D_W2BW_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode);
bool TLx493D_W2BW_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t ur);


bool TLx493D_W2BW_hasValidData(const TLx493D_t *sensor);
bool TLx493D_W2BW_isFunctional(const TLx493D_t *sensor);

bool TLx493D_W2BW_hasWakeUp(const TLx493D_t *sensor);

bool TLx493D_W2BW_isWakeUpEnabled(const TLx493D_t *sensor);

bool TLx493D_W2BW_enableWakeUpMode(TLx493D_t *sensor);
bool TLx493D_W2BW_disableWakeUpMode(TLx493D_t *sensor);

bool TLx493D_W2BW_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh);
bool TLx493D_W2BW_setWakeUpThresholds(TLx493D_t *sensor, double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);

bool TLx493D_W2BW_softwareReset(TLx493D_t *sensor);

/** utilities. */
uint8_t TLx493D_W2BW_calculateFuseParity(const TLx493D_t *sensor);
uint8_t TLx493D_W2BW_calculateBusParity(const TLx493D_t *sensor);
uint8_t TLx493D_W2BW_calculateConfigurationParity(TLx493D_t *sensor);

bool TLx493D_W2BW_hasValidFuseParity(const TLx493D_t *sensor);
bool TLx493D_W2BW_hasValidBusParity(const TLx493D_t *sensor);
bool TLx493D_W2BW_hasValidConfigurationParity(const TLx493D_t *sensor);

bool TLx493D_W2BW_hasValidWakeUpParity(const TLx493D_t *sensor);
bool TLx493D_W2BW_isInTestMode(const TLx493D_t *sensor);

bool TLx493D_W2BW_hasValidTBit(const TLx493D_t *sensor);
bool TLx493D_W2BW_hasValidIICadr(const TLx493D_t *sensor);

void TLx493D_W2BW_setResetValues(TLx493D_t *sensor);

uint8_t TLx493D_W2BW_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

void TLx493D_W2BW_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                         double xInmT, double yInmT, double zInmT,
                                                         int16_t *x, int16_t *y, int16_t *z);

double TLx493D_W2BW_getSensitivityScaleFactor(const TLx493D_t *sensor);

void TLx493D_W2BW_printRegisters(const TLx493D_t *sensor);


#ifdef __cplusplus

}


#endif


#endif /** TLX493D_W2BW_H */