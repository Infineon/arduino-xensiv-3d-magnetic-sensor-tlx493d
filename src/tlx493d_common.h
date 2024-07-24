#ifndef TLX493D_COMMON_H
#define TLX493D_COMMON_H


/** project c includes. */
#include "tlx493d_types.h"


#ifdef __cplusplus

extern "C" {

#endif


bool tlx493d_common_init(TLx493D_t *sensor, uint8_t regMapSize, TLx493D_Register_t *regDef, TLx493D_CommonFunctions_t *commonFuncs, TLx493D_SupportedSensorType_t sensorType, TLx493D_SupportedComLibraryInterfaceType_t comIFType);
bool tlx493d_common_deinit(TLx493D_t *sensor);


void    tlx493d_common_getBitfield(const TLx493D_t *sensor, uint8_t bitField, uint8_t *bitFieldValue);
uint8_t tlx493d_common_returnBitfield(const TLx493D_t *sensor, uint8_t bitField);
void    tlx493d_common_setBitfield(TLx493D_t *sensor, uint8_t bitField, uint8_t newBitFieldValue);

bool tlx493d_common_writeRegister(TLx493D_t* sensor, uint8_t bitField);
bool tlx493d_common_readRegisters(TLx493D_t *sensor);
bool tlx493d_common_readRegistersAndCheck(TLx493D_t *sensor);

void tlx493d_common_calculateRawTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, int16_t *temperature);
bool tlx493d_common_getRawTemperature(TLx493D_t *sensor, int16_t *temperature);

void tlx493d_common_calculateRawMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF, uint8_t byMSBBF, uint8_t byLSBBF,
                                              uint8_t bzMSBBF, uint8_t bzLSBBF, int16_t *x, int16_t *y, int16_t *z);
bool tlx493d_common_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);
bool tlx493d_common_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);


bool tlx493d_common_getTemperature(TLx493D_t *sensor, double *temperature);
bool tlx493d_common_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);
bool tlx493d_common_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature);


/** utilities. */
uint8_t tlx493d_common_calculateParity(uint8_t dataIn);
uint8_t tlx493d_common_getOddParity(uint8_t parity);
uint8_t tlx493d_common_getEvenParity(uint8_t parity);

void tlx493d_common_concatBytes(TLx493D_t *sensor, uint8_t msbBitfield, uint8_t lsbBitfield, int16_t *result);

const char *tlx493d_common_getTypeAsString(const TLx493D_t *sensor);

void tlx493d_common_setIICAddress(TLx493D_t *sensor, uint8_t addr);


void tlx493d_warnFeatureNotAvailableForSensorType(const TLx493D_t *sensor, const char *featureName);
void tlx493d_errorBitfieldNotReadableForSensorType(const TLx493D_t *sensor, uint8_t bf);
void tlx493d_errorBitfieldNotWritableForSensorType(const TLx493D_t *sensor, uint8_t bf);
void tlx493d_errorFunctionNotSupportedForSensorType(const TLx493D_t *sensor, const char *func);
void tlx493d_errorSelectionNotSupportedForSensorType(const TLx493D_t *sensor, uint8_t sel, const char *selType);


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_COMMON_H */
