/** std includes. */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** project c includes. */
#include "tlx493d.h"
#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"

/** sensor specific includes. */
#include "TLx493D_A1B6.h"
#include "TLx493D_A2B6.h"
#include "TLx493D_A2BW.h"
#include "TLx493D_P2B6.h"
#include "TLx493D_W2B6.h"
#include "TLx493D_W2BW.h"
#include "TLx493D_P3B6.h"
#include "TLx493D_P3I8.h"


/** functions common to all sensors. */
bool tlx493d_init(TLx493D_t *sensor, TLx493D_SupportedSensorType_t sensorType) {
   switch(sensorType) {

      case TLx493D_A1B6_e : return TLx493D_A1B6_init(sensor);
                            break;                              


      case TLx493D_A2B6_e : return TLx493D_A2B6_init(sensor);
                            break;


      case TLx493D_A2BW_e : return TLx493D_A2BW_init(sensor);
                            break;


      case TLx493D_P2B6_e : return TLx493D_P2B6_init(sensor);
                            break;


      case TLx493D_W2B6_e : return TLx493D_W2B6_init(sensor);
                            break;


      case TLx493D_W2BW_e : return TLx493D_W2BW_init(sensor);
                            break;


      case TLx493D_P3B6_e : return TLx493D_P3B6_init(sensor);
                            break;


      case TLx493D_P3I8_e : return TLx493D_P3I8_init(sensor);
                            break;


      default : return false;
   }
}


bool tlx493d_deinit(TLx493D_t *sensor) {
   return sensor->functions->deinit(sensor);
}


bool tlx493d_readRegisters(TLx493D_t *sensor) {
   return sensor->functions->readRegisters(sensor);
}


bool tlx493d_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
   return sensor->functions->getRawTemperature(sensor, temperature);
}


bool tlx493d_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
   return sensor->functions->getRawMagneticField(sensor, x, y, z);
}


bool tlx493d_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature) {
   return sensor->functions->getRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


bool tlx493d_getTemperature(TLx493D_t *sensor, double *temperature) {
   return sensor->functions->getTemperature(sensor, temperature);
}


bool tlx493d_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z ) {
   return sensor->functions->getMagneticField(sensor, x, y, z);
}


bool tlx493d_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature) {
   return sensor->functions->getMagneticFieldAndTemperature(sensor, x, y, z, temperature);
}


bool tlx493d_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t meas) {
   return sensor->functions->setMeasurement(sensor, meas);
}


bool tlx493d_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t trigger) {
   return sensor->functions->setTrigger(sensor, trigger);
}


bool tlx493d_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t range) {
   return sensor->functions->setSensitivity(sensor, range);
}


bool tlx493d_setDefaultConfig(TLx493D_t *sensor) {
   return sensor->functions->setDefaultConfig(sensor);
}


bool tlx493d_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t addr) {
   return sensor->functions->setIICAddress(sensor, addr);
}


bool tlx493d_enableCollisionAvoidance(TLx493D_t *sensor) {
   return sensor->functions->enableCollisionAvoidance(sensor);
}


bool tlx493d_disableCollisionAvoidance(TLx493D_t *sensor) {
   return sensor->functions->disableCollisionAvoidance(sensor);
}


bool tlx493d_enableInterrupt(TLx493D_t *sensor) {
   return sensor->functions->enableInterrupt(sensor);
}


bool tlx493d_disableInterrupt(TLx493D_t *sensor) {
   return sensor->functions->disableInterrupt(sensor);
}


bool tlx493d_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode) {
   return sensor->functions->setPowerMode(sensor, mode);
}


bool tlx493d_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t rate) {
   return sensor->functions->setUpdateRate(sensor, rate);
}


bool tlx493d_hasValidData(TLx493D_t *sensor) {
   return sensor->functions->hasValidData(sensor);
}


bool tlx493d_isFunctional(TLx493D_t *sensor) {
   return sensor->functions->isFunctional(sensor);
}


bool tlx493d_hasWakeUp(TLx493D_t *sensor) {
   return sensor->functions->hasWakeUp(sensor);
}


bool tlx493d_isWakeUpEnabled(TLx493D_t *sensor) {
   return sensor->functions->isWakeUpEnabled(sensor);
}


bool tlx493d_enableWakeUpMode(TLx493D_t *sensor) {
   return sensor->functions->enableWakeUpMode(sensor);
}


bool tlx493d_disableWakeUpMode(TLx493D_t *sensor) {
   return sensor->functions->disableWakeUpMode(sensor);
}


bool tlx493d_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xl_th, int16_t xh_th, int16_t yl_th, int16_t yh_th, 
                                        int16_t zl_th, int16_t zh_th) {
   return sensor->functions->setWakeUpThresholdsAsInteger(sensor, xl_th, xh_th, yl_th, yh_th, zl_th, zh_th);
}

bool tlx493d_setWakeUpThresholds(TLx493D_t *sensor, double temperature,
                                 double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh) {
   return sensor->functions->setWakeUpThresholds(sensor, temperature, xLow, xHigh, yLow, yHigh, zLow, zHigh);
}


bool tlx493d_softwareReset(TLx493D_t *sensor) {
   return sensor->functions->softwareReset(sensor);
}


const char *tlx493d_getTypeAsString(const TLx493D_t *sensor) {
   return tlx493d_common_getTypeAsString(sensor);
}


void tlx493d_calculateRawMagneticFieldAtTemperature(TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                    double xInmT, double yInmT, double zInmT,
                                                    int16_t *x, int16_t *y, int16_t *z) {
   sensor->functions->calculateRawMagneticFieldAtTemperature(sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
}


void tlx493d_printRegisters(TLx493D_t *sensor) {
   sensor->functions->printRegisters(sensor);
}
