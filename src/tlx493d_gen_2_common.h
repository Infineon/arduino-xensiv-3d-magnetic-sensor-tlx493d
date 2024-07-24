#ifndef TLX493D_GEN_2_COMMON_H
#define TLX493D_GEN_2_COMMON_H

/** std includes. */
#include <stdbool.h>


/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


void tlx493d_gen_2_calculateRawTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, int16_t *temperature);
void tlx493d_gen_2_calculateRawMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                          uint8_t bzMSBBF, uint8_t bzLSBBF, int16_t *x, int16_t *y, int16_t *z);

void tlx493d_gen_2_calculateTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, double *temperature);
void tlx493d_gen_2_calculateMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                          uint8_t bzMSBBF, uint8_t bzLSBBF, double *x, double *y, double *z);

bool tlx493d_gen_2_setOneConfigBitfield(TLx493D_t *sensor, uint8_t bfBF, uint8_t cpBF, uint8_t bfVal);
bool tlx493d_gen_2_setTwoConfigBitfields(TLx493D_t *sensor, uint8_t firstBF, uint8_t secondBF, uint8_t cpBF, uint8_t firstVal, uint8_t secondVal);

bool tlx493d_gen_2_setMeasurement(TLx493D_t *sensor, uint8_t dtBF, uint8_t amBF, uint8_t cpBF, TLx493D_MeasurementType_t val);
bool tlx493d_gen_2_setTrigger(TLx493D_t *sensor, uint8_t trigBF, uint8_t cpBF, TLx493D_TriggerType_t val);
bool tlx493d_gen_2_setSensitivity(TLx493D_t *sensor, TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF, uint8_t cpBF, TLx493D_SensitivityType_t val);
/** bool tlx493d_gen_2_setMagneticTemperatureCompensation(TLx493D_t *sensor, uint8_t tl_magBF, uint8_t cpBF, uint8_t mtc); */


bool tlx493d_gen_2_setDefaultConfig(TLx493D_t *sensor, uint8_t cpBF, uint8_t caBF, uint8_t intBF);
bool tlx493d_gen_2_setIICAddress(TLx493D_t *sensor, uint8_t iicadrBF, uint8_t fpBF, TLx493D_IICAddressType_t addr);
bool tlx493d_gen_2_set1ByteReadMode(TLx493D_t *sensor, uint8_t prBF, uint8_t fpBF, uint8_t prdBF, uint8_t pr);

bool tlx493d_gen_2_setCollisionAvoidance(TLx493D_t *sensor, uint8_t caBF, uint8_t fpBF, uint8_t ca);
bool tlx493d_gen_2_setInterrupt(TLx493D_t *sensor, uint8_t intBF, uint8_t fpBF, uint8_t irq);

bool tlx493d_gen_2_setPowerMode(TLx493D_t *sensor, uint8_t modeBF, uint8_t fpBF, TLx493D_PowerModeType_t val);
bool tlx493d_gen_2_setUpdateRateFastSlow(TLx493D_t *sensor, uint8_t fpBF, uint8_t prdBF, TLx493D_UpdateRateType_t val);
bool tlx493d_gen_2_setUpdateRate(TLx493D_t *sensor, uint8_t fpBF, uint8_t prdBF, TLx493D_UpdateRateType_t val);

bool tlx493d_gen_2_hasValidData(const TLx493D_t *sensor, uint8_t modeBF, uint8_t pd3BF, uint8_t pd0BF);
bool tlx493d_gen_2_isFunctional(const TLx493D_t *sensor);


bool tlx493d_gen_2_writeConfigurationRegisters(TLx493D_t *sensor);
/** bool tlx493d_gen_2_hasWakeUp(TLx493D_t *sensor, uint8_t typeBF); */
bool tlx493d_gen_2_isWakeUpEnabled(const TLx493D_t *sensor, uint8_t waBF);
bool tlx493d_gen_2_enableWakeUpMode(TLx493D_t *sensor, uint8_t tstBF, uint8_t wuBF, uint8_t cpbBF);
bool tlx493d_gen_2_disableWakeUpMode(TLx493D_t *sensor, uint8_t wuBF, uint8_t cpbBF);

bool tlx493d_gen_2_setThreshold(TLx493D_t *sensor, uint8_t msbsBF, uint8_t lsbsBF, int16_t threshold12Bits);

bool tlx493d_gen_2_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, uint8_t cpBF,
                                                uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                                uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                                uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                                int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh);

bool tlx493d_gen_2_setWakeUpThresholds(TLx493D_t *sensor, uint8_t cpBF,
                                       uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                       uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                       uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                       TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF,
                                       double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);


/** utilities. */
bool tlx493d_gen_2_softwareReset(TLx493D_t *sensor);


uint8_t tlx493d_gen_2_calculateFuseParity(const TLx493D_t *sensor, uint8_t fpBF, uint8_t prdBF);
uint8_t tlx493d_gen_2_calculateBusParity(const TLx493D_t *sensor, uint8_t to);
uint8_t tlx493d_gen_2_calculateConfigurationParity(const TLx493D_t *sensor, uint8_t cpBF);
uint8_t tlx493d_gen_2_calculateConfigurationParityWakeUp(const TLx493D_t *sensor, uint8_t cpBF); /**, uint8_t from, uint8_t to); */

bool tlx493d_gen_2_hasValidFuseParity(const TLx493D_t *sensor, uint8_t ffBF);
bool tlx493d_gen_2_hasValidBusParity(const TLx493D_t *sensor, uint8_t pBF);
bool tlx493d_gen_2_hasValidConfigurationParity(const TLx493D_t *sensor, uint8_t cpBF);

bool tlx493d_gen_2_hasValidIICadr(const TLx493D_t *sensor, uint8_t idBF, uint8_t iicAdrBF);
bool tlx493d_gen_2_hasValidTBit(const TLx493D_t *sensor, uint8_t tBF) ;


/** bool tlx493d_gen_2_hasValidTemperatureData(TLx493D_t *sensor); */
/** bool tlx493d_gen_2_hasValidMagneticFieldData(TLx493D_t *sensor); */
/** bool tlx493d_gen_2_hasValidPD3Bit(TLx493D_t *sensor, uint8_t pd3BF); */
/** bool tlx493d_gen_2_hasValidPD0Bit(TLx493D_t *sensor, uint8_t pd0BF); */


/** uint8_t tlx493d_gen_2_getID(TLx493D_t *sensor, uint8_t idBF); */
/** uint8_t tlx493d_gen_2_getFrameCounter(TLx493D_t *sensor, uint8_t frmBF) ; */
/** uint8_t tlx493d_gen_2_getType(TLx493D_t *sensor, uint8_t typeBF); */
/** uint8_t tlx493d_gen_2_getHWV(TLx493D_t *sensor, uint8_t hwvBF); */


uint8_t tlx493d_gen_2_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

double tlx493d_gen_2_getSensitivityScaleFactor(const TLx493D_t *sensor, TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF);

void tlx493d_gen_2_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                          double xInmT, double yInmT, double zInmT,
                                                          int16_t *x, int16_t *y, int16_t *z);

void tlx493d_gen_2_convertTemperatureToRaw(const TLx493D_t *sensor, double temperature, int16_t *rawTemperature);

TLx493D_SensitivityType_t tlx493d_gen_2_getSensitivityType(const TLx493D_t *sensor, TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF);


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_GEN_2_COMMON_H */