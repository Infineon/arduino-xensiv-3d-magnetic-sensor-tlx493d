#ifndef TLX493D_GEN_3_COMMON_H
#define TLX493D_GEN_3_COMMON_H


/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


bool tlx493d_gen_3_readRegisters(TLx493D_t *sensor, uint8_t channelSaveBF);
bool tlx493d_gen_3_readRegistersAndCheck(TLx493D_t *sensor, uint8_t channelSaveBF);

void tlx493d_gen_3_calculateRawTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, int16_t *temperature);
void tlx493d_gen_3_calculateRawMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                             uint8_t bzMSBBF, uint8_t bzLSBBF, int16_t *x, int16_t *y, int16_t *z);

void tlx493d_gen_3_calculateTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, double *temperature);
void tlx493d_gen_3_calculateMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                          uint8_t bzMSBBF, uint8_t bzLSBBF, uint8_t tempMSBBF, uint8_t tempLSBBF,
                                          double *x, double *y, double *z);

bool tlx493d_gen_3_setMeasurement(TLx493D_t *sensor, uint8_t channelBF, uint8_t channelSaveBF, TLx493D_MeasurementType_t val);
bool tlx493d_gen_3_setTrigger(TLx493D_t *sensor, uint8_t trigBF, TLx493D_TriggerType_t val);
bool tlx493d_gen_3_setSensitivity(TLx493D_t *sensor, uint8_t shortBF, uint8_t xtrShortBF, TLx493D_SensitivityType_t val);

bool tlx493d_gen_3_setDefaultConfig(TLx493D_t *sensor, uint8_t caBF, uint8_t intBF);
bool tlx493d_gen_3_setIICAddress(const TLx493D_t *sensor, uint8_t iicadrBF, TLx493D_IICAddressType_t addr);
bool tlx493d_gen_3_set1ByteReadMode(TLx493D_t *sensor, uint8_t prBF, uint8_t pr);

bool tlx493d_gen_3_setCollisionAvoidance(TLx493D_t *sensor, uint8_t caBF, uint8_t ca);
bool tlx493d_gen_3_setInterrupt(TLx493D_t *sensor, uint8_t intBF, uint8_t irq);

bool tlx493d_gen_3_setPowerMode(TLx493D_t *sensor, uint8_t modeBF, TLx493D_PowerModeType_t val);
bool tlx493d_gen_3_setUpdateRate(TLx493D_t *sensor, uint8_t fUpdateBF, TLx493D_UpdateRateType_t val);

bool tlx493d_gen_3_hasValidData(const TLx493D_t *sensor, uint8_t measBF);
bool tlx493d_gen_3_isFunctional(const TLx493D_t *sensor);

bool tlx493d_gen_3_isWakeUpEnabled(const TLx493D_t *sensor, uint8_t wuBF);
bool tlx493d_gen_3_enableWakeUpMode(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF);
bool tlx493d_gen_3_disableWakeUpMode(TLx493D_t *sensor, uint8_t intBF, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF);

bool tlx493d_gen_3_writeWakeupParityRelatedRegisters(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF);
bool tlx493d_gen_3_setThreshold(TLx493D_t *sensor, uint8_t msbsBF, uint8_t lsbsBF, int16_t threshold10Bits);
bool tlx493d_gen_3_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF,
                                                uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                                uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                                uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                                int16_t xlTh, int16_t xhTh, int16_t ylTh, int16_t yhTh, int16_t zlTh, int16_t zhTh);

bool tlx493d_gen_3_setWakeUpThresholds(TLx493D_t *sensor, uint8_t wuBF, uint8_t wucpBF, uint8_t wupBF,
                                       uint8_t xlMSBBF, uint8_t xlLSBBF, uint8_t xhMSBBF, uint8_t xhLSBBF,
                                       uint8_t ylMSBBF, uint8_t ylLSBBF, uint8_t yhMSBBF, uint8_t yhLSBBF,
                                       uint8_t zlMSBBF, uint8_t zlLSBBF, uint8_t zhMSBBF, uint8_t zhLSBBF,
                                       uint8_t x2BF, uint8_t x4BF,
                                       double temperature, double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);

bool tlx493d_gen_3_softwareReset(TLx493D_t *sensor, uint8_t resetBF);


/** utilities. */
bool tlx493d_gen_3_setWakeUpParity(TLx493D_t *sensor, uint8_t wuBF, uint8_t wupBF);
uint8_t tlx493d_gen_3_calculateWakeUpParity(const TLx493D_t *sensor, uint8_t wuBF);

bool tlx493d_gen_3_hasValidFuseParity(const TLx493D_t *sensor, uint8_t fpfBF);
bool tlx493d_gen_3_hasValidWakeUpParity(const TLx493D_t *sensor, uint8_t wupBF);
bool tlx493d_gen_3_isInTestMode(const TLx493D_t *sensor, uint8_t testBF);


/** bool tlx493d_gen_3_hasValidIICadr(TLx493D_t *sensor, uint8_t idBF, uint8_t iicAdrBF); */

uint8_t tlx493d_gen_3_selectIICAddress(const TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

double tlx493d_gen_3_getSensitivityScaleFactor(const TLx493D_t *sensor, TLx493D_AvailableSensitivityType_t availSens, uint8_t x2BF, uint8_t x4BF);

void tlx493d_gen_3_calculateRawMagneticFieldAtTemperature(const TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                          double xInmT, double yInmT, double zInmT,
                                                          int16_t *x, int16_t *y, int16_t *z);

void tlx493d_gen_3_convertTemperatureToRaw(const TLx493D_t *sensor, double temperature, int16_t *rawTemperature);

TLx493D_SensitivityType_t tlx493d_gen_3_getSensitivityType(const TLx493D_t *sensor, uint8_t x2BF, uint8_t x4BF);


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_GEN_3_COMMON_H */
