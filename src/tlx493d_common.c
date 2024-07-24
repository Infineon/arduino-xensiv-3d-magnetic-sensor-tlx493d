/** std includes. */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** project c includes. */
#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"
#include "tlx493d.h"
#include "CommunicationInterface.h"
#include "Logger.h"


/***
*/
bool tlx493d_common_init(TLx493D_t *sensor, uint8_t regMapSize, TLx493D_Register_t *regDef, TLx493D_CommonFunctions_t *commonFuncs,
                         TLx493D_SupportedSensorType_t sensorType, TLx493D_SupportedComLibraryInterfaceType_t comIFType) {
    sensor->regMap     = (uint8_t*) malloc(sizeof(uint8_t) * regMapSize);

    if( sensor->regMap == NULL ) {
        logError("Malloc regMap failed !");
        logFlush();
        return false;
    }
    else {
        sensor->regDef     = regDef;
        sensor->functions  = commonFuncs;
        sensor->regMapSize = regMapSize;
        sensor->sensorType = sensorType;
        sensor->comIFType  = comIFType;

        sensor->comInterface.comLibFuncs                       = NULL;
        sensor->comInterface.comLibObj.iic_obj                 = NULL;

        sensor->boardSupportInterface.boardSupportObj.k2go_obj = NULL;

        (void) memset(sensor->regMap, 0, sensor->regMapSize);
        sensor->functions->setResetValues(sensor);
    }

    return true;
}


/***
 * 
*/
bool tlx493d_common_deinit(TLx493D_t *sensor) {
    if( sensor->regMap != NULL ) {
        free(sensor->regMap);
        sensor->regMap = NULL;
    }

    sensor->comInterface.comLibFuncs                       = NULL;
    sensor->comInterface.comLibObj.iic_obj                 = NULL;

    sensor->boardSupportInterface.boardSupportObj.k2go_obj = NULL;
    
    return true;
}


static bool tlx493d_hasNotOnly0xFFInRegmap(const TLx493D_t *sensor) {
    /** Skip address 0 ! Seems to be ok even if other entries are not. */
    for(uint8_t i = 1; i < sensor->regMapSize; ++i) {
        if( sensor->regMap[i] != 0xFFU ) {
            return true;
        }
    }

    return false;
}

/***
 * Generations 2 and 3, not 1.
*/
bool tlx493d_common_readRegisters(TLx493D_t *sensor) {
    bool isOk  = tlx493d_transfer(sensor, NULL, 0, sensor->regMap, sensor->regMapSize);
    isOk      &= tlx493d_hasNotOnly0xFFInRegmap(sensor);

/*
    if( ! isOk ) {
        logInfo("tlx493d_common_readRegisters   isOk = %d", isOk);

        logInfo("hasValidData = %d", sensor->functions->hasValidData(sensor));
        logInfo("hasValidBusParity = %d", sensor->functions->hasValidBusParity(sensor));
        logInfo("hasValidTBit = %d", sensor->functions->hasValidTBit(sensor));

        logInfo("isInTestMode = %d", sensor->functions->isInTestMode(sensor));

        logInfo("isFunctional = %d", sensor->functions->isFunctional(sensor));
        logInfo("hasValidFuseParity = %d", sensor->functions->hasValidFuseParity(sensor));
        logInfo("hasValidConfigurationParity = %d", sensor->functions->hasValidConfigurationParity(sensor));

        tlx493d_printRegisters(sensor);
    }
*/

    return isOk;
}


/***
 * Generations 2 and 3, not 1.
*/
bool tlx493d_common_readRegistersAndCheck(TLx493D_t *sensor) {
    uint8_t buf[sensor->regMapSize];

    (void) memcpy(buf, sensor->regMap, sensor->regMapSize);

    do {
        bool isOk  = tlx493d_transfer(sensor, NULL, 0, sensor->regMap, sensor->regMapSize);
        isOk      &= tlx493d_hasNotOnly0xFFInRegmap(sensor);

        /*
        logInfo("isOk = %d", isOk);

        logInfo("hasValidData = %d", sensor->functions->hasValidData(sensor));
        logInfo("hasValidBusParity = %d", sensor->functions->hasValidBusParity(sensor));
        logInfo("hasValidTBit = %d", sensor->functions->hasValidTBit(sensor));

        logInfo("isInTestMode = %d", sensor->functions->isInTestMode(sensor));

        logInfo("isFunctional = %d", sensor->functions->isFunctional(sensor));
        logInfo("hasValidFuseParity = %d", sensor->functions->hasValidFuseParity(sensor));
        logInfo("hasValidConfigurationParity = %d", sensor->functions->hasValidConfigurationParity(sensor));

        sensor->functions->printRegisters(sensor);
        */

        // if( ! (isOk && sensor->functions->hasValidData(sensor) && sensor->functions->isFunctional(sensor)) ) {
        if( ! (isOk && sensor->functions->hasValidData(sensor) && sensor->functions->hasValidFuseParity(sensor)) ) {
/*
            logInfo("tlx493d_common_readRegistersAndCheck    --------   isOk = %d", isOk);

            logInfo("hasValidData = %d", sensor->functions->hasValidData(sensor));
            logInfo("hasValidBusParity = %d", sensor->functions->hasValidBusParity(sensor));
            logInfo("hasValidTBit = %d", sensor->functions->hasValidTBit(sensor));

            logInfo("isInTestMode = %d", sensor->functions->isInTestMode(sensor));

            logInfo("isFunctional = %d", sensor->functions->isFunctional(sensor));
            logInfo("hasValidFuseParity = %d", sensor->functions->hasValidFuseParity(sensor));
            logInfo("hasValidConfigurationParity = %d", sensor->functions->hasValidConfigurationParity(sensor));

            tlx493d_printRegisters(sensor);
*/

            (void) memcpy(sensor->regMap, buf, sensor->regMapSize);

/*
            tlx493d_printRegisters(sensor);
*/
        }
        else {
            break;
        }
    } while( true );
    /** } while( ! (isOk && sensor->functions->hasValidData(sensor)) ); */
    /** } while( ! (isOk && sensor->functions->hasValidData(sensor) && sensor->functions->isFunctional(sensor)) ); */

    return true;
}


void tlx493d_common_calculateRawTemperature(TLx493D_t *sensor, uint8_t tempMSBBF, uint8_t tempLSBBF, int16_t *temperature) {
    tlx493d_common_concatBytes(sensor, tempMSBBF, tempLSBBF, temperature);
}


bool tlx493d_common_getRawTemperature(TLx493D_t *sensor, int16_t *temperature) {
    bool b = false;

    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateRawTemperature(sensor, temperature);
        /** return true; */
        b = true;
    }

    /** return false; */
    return b;
}


void tlx493d_common_calculateRawMagneticField(TLx493D_t *sensor, uint8_t bxMSBBF, uint8_t bxLSBBF,
                                              uint8_t byMSBBF, uint8_t byLSBBF, uint8_t bzMSBBF, uint8_t bzLSBBF,
                                              int16_t *x, int16_t *y, int16_t *z) {
    tlx493d_common_concatBytes(sensor, bxMSBBF, bxLSBBF, x);
    tlx493d_common_concatBytes(sensor, byMSBBF, byLSBBF, y);
    tlx493d_common_concatBytes(sensor, bzMSBBF, bzLSBBF, z);
}


bool tlx493d_common_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z) {
    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateRawMagneticField(sensor, x, y, z);
        return true;
    }

    return false;
}


bool tlx493d_common_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z,
                                                     int16_t *temperature) {
    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateRawMagneticFieldAndTemperature(sensor, x, y, z, temperature);
        return true;
    }

    return false;
}


/***
 * 
*/
bool tlx493d_common_getTemperature(TLx493D_t *sensor, double *temperature) {
    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateTemperature(sensor, temperature);
        return true;
    }

    return false;
}


/***
 * 
*/
bool tlx493d_common_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z ) {
    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateMagneticField(sensor, x, y, z);
        return true;
    }

    return false;
}


/***
 * 
*/
bool tlx493d_common_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature) {
    if( sensor->functions->readRegistersAndCheck(sensor) ) {
        sensor->functions->calculateMagneticFieldAndTemperature(sensor, x, y, z, temperature);
        return true;
    }

    return false;
}


uint8_t tlx493d_common_returnBitfield(const TLx493D_t *sensor, uint8_t bitField) {
    const TLx493D_Register_t *bf = &sensor->regDef[bitField];

    if((bf->accessMode == TLx493D_READ_MODE_e) || (bf->accessMode == TLx493D_READ_WRITE_MODE_e)) {
        return (sensor->regMap[bf->address] & bf->mask) >> bf->offset;
    }
    
    tlx493d_errorBitfieldNotReadableForSensorType(sensor, bitField);
    return 0U;
}


void tlx493d_common_getBitfield(const TLx493D_t *sensor, uint8_t bitField, uint8_t *bitFieldValue) {
    *bitFieldValue = tlx493d_common_returnBitfield(sensor, bitField);
}


void tlx493d_common_setBitfield(TLx493D_t *sensor, uint8_t bitField, uint8_t newBitFieldValue) {
    const TLx493D_Register_t *bf = &sensor->regDef[bitField];

    if((bf->accessMode == TLx493D_WRITE_MODE_e) || (bf->accessMode == TLx493D_READ_WRITE_MODE_e)) {
       sensor->regMap[bf->address] = (uint8_t) ((sensor->regMap[bf->address] & ((uint8_t) ~bf->mask)) | ((newBitFieldValue << bf->offset) & bf->mask));
    }
    else {
        tlx493d_errorBitfieldNotWritableForSensorType(sensor, bitField);
    }
}


bool tlx493d_common_writeRegister(TLx493D_t* sensor, uint8_t bitField) {
    const TLx493D_Register_t *bf = &sensor->regDef[bitField];

    if((bf->accessMode == TLx493D_WRITE_MODE_e) || (bf->accessMode == TLx493D_READ_WRITE_MODE_e)) {
        uint8_t transBuffer[2] = { bf->address, sensor->regMap[bf->address] };

        return tlx493d_transfer(sensor, transBuffer, sizeof(transBuffer), NULL, 0);
    }

    return false;
}


uint8_t tlx493d_common_calculateParity(uint8_t dataIn) {
    uint8_t data = dataIn;
	data ^= data >> 4;
	data ^= data >> 2;
	data ^= data >> 1;
	return data & 1U;
}


uint8_t tlx493d_common_getOddParity(uint8_t parity) {
    return (parity ^ 1U) & 1U;
}


uint8_t tlx493d_common_getEvenParity(uint8_t parity) {
    return parity & 1U;
}


/**
 * More generic version wrt size and offsets of MSB and LSB. Register values are in two's complement form.
 * Assumptions :
 *    - registers are 8 bits wide
*/
void tlx493d_common_concatBytes(TLx493D_t *sensor, uint8_t msbBitfield, uint8_t lsbBitfield, int16_t *result) {
    const TLx493D_Register_t *msb = &sensor->regDef[msbBitfield];
    const TLx493D_Register_t *lsb = &sensor->regDef[lsbBitfield];

    *result   = ((sensor->regMap[msb->address] & msb->mask) << (16U - msb->numBits - msb->offset)); /** Set minus flag if highest bit is set */
    *result >>= (16U - msb->numBits - lsb->numBits); /** shift back and make space for LSB */
    *result  |= ((int16_t) ((sensor->regMap[lsb->address] & lsb->mask) >> lsb->offset)); /** OR with LSB */
}


const char *tlx493d_common_getTypeAsString(const TLx493D_t *sensor) {
    switch(sensor->sensorType) {
        case TLx493D_A1B6_e : return "TLx493D_A1B6";
                              break;

        case TLx493D_A2B6_e : return "TLx493D_A2B6";
                              break;

        case TLx493D_A2BW_e : return "TLx493D_A2BW";
                              break;

        case TLx493D_P2B6_e : return "TLx493D_P2B6";
                              break;

        case TLx493D_W2B6_e : return "TLx493D_W2B6";
                              break;

        case TLx493D_W2BW_e : return "TLx493D_W2BW";
                              break;

        case TLx493D_P3B6_e : return "TLx493D_P3B6";
                              break;

        case TLx493D_P3I8_e : return "TLx493D_P3I8";
                              break;

        default : return "ERROR : Unknown sensorType !";
                  break;
    }
}


void tlx493d_common_setIICAddress(TLx493D_t *sensor, uint8_t addr) {
    sensor->comInterface.comLibParams.iic_params.address = addr;
}


void tlx493d_warnFeatureNotAvailableForSensorType(const TLx493D_t *sensor, const char *featureName) {
    logWarn("Feature '%s' not available for sensor type '%s' !", featureName, tlx493d_common_getTypeAsString(sensor));
}


void tlx493d_errorBitfieldNotReadableForSensorType(const TLx493D_t *sensor, uint8_t bf) {
    logError("Bitfield '%d' not readable for sensor type '%s' !", bf, tlx493d_common_getTypeAsString(sensor));
}


void tlx493d_errorBitfieldNotWritableForSensorType(const TLx493D_t *sensor, uint8_t bf) {
    logError("Bitfield '%d' not writable for sensor type '%s' !", bf, tlx493d_common_getTypeAsString(sensor));
}


void tlx493d_errorFunctionNotSupportedForSensorType(const TLx493D_t *sensor, const char *func) {
    logError("Function '%s' not supported for sensor type '%s' !", func, tlx493d_common_getTypeAsString(sensor));
}


void tlx493d_errorSelectionNotSupportedForSensorType(const TLx493D_t *sensor, uint8_t sel, const char *selType) {
    logError("Selection '%d' for type '%s' not supported for sensor type '%s' !", sel, selType, tlx493d_common_getTypeAsString(sensor));
}

