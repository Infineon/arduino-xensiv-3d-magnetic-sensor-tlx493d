#ifndef TLX493D_TYPES_H
#define TLX493D_TYPES_H


/** std includes. */
#include <stdbool.h>
#include <stdint.h>

/** project c includes. */
#include "tlx493d_enums.h"


#ifdef __cplusplus

typedef struct TLx493D_t  TLx493D_t;

/** project cpp includes. */
#include "baseTypes.hpp"

extern "C" {

#else

/** project c includes. */
#include "pal.h"

#endif


/**
 * @brief The structure `TLx493D_Register_t` is used to store name, access mode, address, mask and offset of registers.
 */
typedef struct TLx493D_Register_t {
    /** uint8_t                           name; */
    TLx493D_RegisterAccessModeType_t  accessMode;
    uint8_t                           address;
    uint8_t                           mask;
    uint8_t                           offset;
    uint8_t                           numBits;
} TLx493D_Register_t;


/** Definition of function pointers for the communication and the transfer of data. */
typedef bool (*TLx493D_OneParamsFuncPtr)(TLx493D_t *sensor);
typedef void (*TLx493D_SetReadAddressFuncPtr)(TLx493D_t *sensor, uint8_t address);
typedef bool (*TLx493D_TransferFuncPtr)(TLx493D_t *sensor, uint8_t *tx_buffer, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len);


/**
 * @brief The structure `TLx493D_SPIParameters_t` stores the parameter of the SPI interface.
 */
typedef struct TLx493D_SPIParameters_t {
    uint8_t dummy;
} TLx493D_SPIParameters_t;


/**
 * @brief The structure `TLx493D_I2CParameters_t` stores the parameter of the I2C interface.
 */
typedef struct TLx493D_I2CParameters_t {
    uint8_t address;
} TLx493D_I2CParameters_t;


/**
 * @brief The structure `TLx493D_ComLibraryFunctions_t` stores the function pointers which are
 * needed for the initialization and the transfer of data, for each communication interface.
 */
typedef struct TLx493D_ComLibraryFunctions_t {
    union {
        TLx493D_OneParamsFuncPtr  spi_init;
        TLx493D_OneParamsFuncPtr  iic_init;
    } init;

    union {
        TLx493D_OneParamsFuncPtr  spi_deinit;
        TLx493D_OneParamsFuncPtr  iic_deinit;
    } deinit;

    union {
        TLx493D_TransferFuncPtr  spi_transfer;
        TLx493D_TransferFuncPtr  iic_transfer;
    } transfer;

    union {
        TLx493D_SetReadAddressFuncPtr  spi_setReadAddress;
        TLx493D_SetReadAddressFuncPtr  iic_setReadAddress;
    } setReadAddress;
} TLx493D_ComLibraryFunctions_t;


/**
 * @brief The structure `TLx493D_ComLibraryParameters_t` is used to store the necessary parameters
 * for both interface (I2C, SPI).
 */
typedef union TLx493D_ComLibraryParameters_t {
    TLx493D_SPIParameters_t  spi_params;
    TLx493D_I2CParameters_t  iic_params;
} TLx493D_ComLibraryParameters_t;


/**
 * @brief The structure `TLx493D_ComLibraryObject_t` is used to store both communication interface objects.
 */
typedef union TLx493D_ComLibraryObject_t {
    TLx493D_SPIObject_t  *spi_obj;
    TLx493D_I2CObject_t  *iic_obj;
} TLx493D_ComLibraryObject_t;


/**
 * @brief The structure `TLx493D_CommunicationInterface_t` contains all the important parameters to properly use the
 * communication interface. It uses the previously defined structures `TLx493D_ComLibraryFunctions_t`, `TLx493D_ComLibraryParameters_t`
 * and `TLx493D_ComLibraryObject_t`.
 */
typedef struct TLx493D_CommunicationInterface_t {
    TLx493D_ComLibraryFunctions_t   *comLibFuncs;
    TLx493D_ComLibraryParameters_t   comLibParams;
    TLx493D_ComLibraryObject_t       comLibObj;
} TLx493D_CommunicationInterface_t;


/**
 * @brief The union `TLx493D_BoardSupportObject_t` defines the board support object, which is used for
 * Kits2Go.
 */
typedef union TLx493D_BoardSupportObject_t {
    TLx493D_Kit2GoBoardSupportObject_t  *k2go_obj;
} TLx493D_BoardSupportObject_t;


typedef struct TLx493D_BoardSupportInterface_t {
    /** TLx493D_BoardSupportFunctions_t   *boardSupportFuncs; */
    /** TLx493D_BoardSupportParameters_t   boardSupportParams; */
    TLx493D_BoardSupportObject_t       boardSupportObj;
} TLx493D_BoardSupportInterface_t;


/** Following are the functions which are common to all the sensors. */
typedef bool (*TLx493D_InitFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_DeinitFuncPtr)(TLx493D_t *);

typedef bool (*TLx493D_ReadRegistersFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_ReadRegistersAndCheckFuncPtr)(TLx493D_t *);

typedef void (*TLx493D_CalculateRawTemperatureFuncPtr)(TLx493D_t *, int16_t *);
typedef bool (*TLx493D_GetRawTemperatureFuncPtr)(TLx493D_t *, int16_t *);

typedef void (*TLx493D_CalculateRawMagneticFieldFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *);
typedef bool (*TLx493D_GetRawMagneticFieldFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *);

typedef void (*TLx493D_CalculateRawMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *, int16_t *);
typedef bool (*TLx493D_GetRawMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, int16_t *, int16_t *, int16_t *, int16_t *);

typedef void (*TLx493D_CalculateTemperatureFuncPtr)(TLx493D_t *, double *);
typedef bool (*TLx493D_GetTemperatureFuncPtr)(TLx493D_t *, double *);

typedef void (*TLx493D_CalculateMagneticFieldFuncPtr)(TLx493D_t *, double *, double *, double *);
typedef bool (*TLx493D_GetMagneticFieldFuncPtr)(TLx493D_t *, double *, double *, double *);

typedef void (*TLx493D_CalculateMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, double *, double *, double *, double *);
typedef bool (*TLx493D_GetMagneticFieldAndTemperatureFuncPtr)(TLx493D_t *, double *, double *, double *, double *);


/** Following are the functions related to the "Config" register. */
typedef bool (*TLx493D_SetMeasurementFuncPtr)(TLx493D_t *, TLx493D_MeasurementType_t);
typedef bool (*TLx493D_SetTriggerFuncPtr)(TLx493D_t *, TLx493D_TriggerType_t);
typedef bool (*TLx493D_SetSetSensitivityFuncPtr)(TLx493D_t *, TLx493D_SensitivityType_t);


/** Following are the functions related to the "Mod1" and "Mod2" registers. */
typedef bool (*TLx493D_SetDefaultConfigFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_SetIICAddressFuncPtr)(TLx493D_t *, TLx493D_IICAddressType_t);
typedef bool (*TLx493D_Enable1ByteReadModeFuncPtr)(TLx493D_t *);

typedef bool (*TLx493D_EnableInterruptFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_DisableInterruptFuncPtr)(TLx493D_t *);

typedef bool (*TLx493D_EnableCollisionAvoidanceFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_DisableCollisionAvoidanceFuncPtr)(TLx493D_t *);

typedef bool (*TLx493D_SetPowerModeFuncPtr)(TLx493D_t *, TLx493D_PowerModeType_t);
typedef bool (*TLx493D_SetUpdateRateFuncPtr)(TLx493D_t *, TLx493D_UpdateRateType_t);

/** Following are the functions related to the "Diag" register. */
typedef bool (*TLx493D_HasValidDataFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_IsFunctionalFuncPtr)(const TLx493D_t *);


/** Following are the functions related to the "WU" register. These are only available to a subset of sensors with wake-up functionality */
typedef bool (*TLx493D_HasWakeUpFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_IsWakeUpEnabledFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_EnableWakeUpModeFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_DisableWakeUpModeFuncPtr)(TLx493D_t *);
typedef bool (*TLx493D_SetWakeUpThresholdsAsIntegerFuncPtr)(TLx493D_t *, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
typedef bool (*TLx493D_SetWakeUpThresholdsFuncPtr)(TLx493D_t *, double, double, double, double, double, double, double);

typedef bool (*TLx493D_SoftwareResetFuncPtr)(TLx493D_t *);


/** Following are the functions used internally and not accessible through the common interface. */
typedef uint8_t (*TLx493D_CalculateFuseParityFuncPtr)(const TLx493D_t *);
typedef uint8_t (*TLx493D_CalculateBusParityFuncPtr)(const TLx493D_t *);
typedef uint8_t (*TLx493D_CalculateConfigParityFuncPtr)(TLx493D_t *);

typedef bool (*TLx493D_HasValidFuseParityFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_HasValidBusParityFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_HasValidConfigParityFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_HasValidWakeUpParityFuncPtr)(const TLx493D_t *);

typedef bool (*TLx493D_HasValidTBitFuncPtr)(const TLx493D_t *);
typedef bool (*TLx493D_isInTestModeFuncPtr)(const TLx493D_t *);

typedef void (*TLx493D_SetResetValuesFuncPtr)(TLx493D_t *);

typedef void (*TLx493D_CalculateRawMagneticFieldAtTemperatureFuncPtr)(const TLx493D_t *, int16_t, TLx493D_SensitivityType_t,
                                                                      double, double, double,
                                                                      int16_t *, int16_t *, int16_t *);

typedef double (*TLx493D_GetSensitivityScaleFactorFuncPtr)(const TLx493D_t *);

typedef uint8_t (*TLx493D_SelectIICAddressFuncPtr)(const TLx493D_t *, TLx493D_IICAddressType_t);

typedef void (*TLx493D_PrintRegistersFuncPtr)(const TLx493D_t *);


/** Functions used to refer to sensor specific functions by a common name. These functions are not part of the common user C/C++ interface. */
typedef struct TLx493D_CommonFunctions_t {
    TLx493D_InitFuncPtr                         init;
    TLx493D_DeinitFuncPtr                       deinit;

    TLx493D_ReadRegistersFuncPtr                readRegisters;
    TLx493D_ReadRegistersAndCheckFuncPtr        readRegistersAndCheck;

    TLx493D_CalculateRawTemperatureFuncPtr      calculateRawTemperature;
    TLx493D_GetRawTemperatureFuncPtr            getRawTemperature;

    TLx493D_CalculateRawMagneticFieldFuncPtr    calculateRawMagneticField;
    TLx493D_GetRawMagneticFieldFuncPtr          getRawMagneticField;

    TLx493D_CalculateRawMagneticFieldAndTemperatureFuncPtr  calculateRawMagneticFieldAndTemperature;
    TLx493D_GetRawMagneticFieldAndTemperatureFuncPtr        getRawMagneticFieldAndTemperature;

    TLx493D_CalculateTemperatureFuncPtr         calculateTemperature;
    TLx493D_GetTemperatureFuncPtr               getTemperature;

    TLx493D_CalculateMagneticFieldFuncPtr       calculateMagneticField;
    TLx493D_GetMagneticFieldFuncPtr             getMagneticField;
    
    TLx493D_CalculateMagneticFieldAndTemperatureFuncPtr  calculateMagneticFieldAndTemperature;
    TLx493D_GetMagneticFieldAndTemperatureFuncPtr        getMagneticFieldAndTemperature;

    /** Functions related to the "Config" register. */
    TLx493D_SetMeasurementFuncPtr             setMeasurement;
    TLx493D_SetTriggerFuncPtr                   setTrigger;
    TLx493D_SetSetSensitivityFuncPtr            setSensitivity;

    
    /** Functions related to the "Mod1" and "Mod2" registers. */
    TLx493D_SetDefaultConfigFuncPtr             setDefaultConfig;
    TLx493D_SetIICAddressFuncPtr                setIICAddress;
    TLx493D_Enable1ByteReadModeFuncPtr          enable1ByteReadMode;

    TLx493D_EnableInterruptFuncPtr              enableInterrupt;
    TLx493D_DisableInterruptFuncPtr             disableInterrupt;

    TLx493D_EnableCollisionAvoidanceFuncPtr     enableCollisionAvoidance;
    TLx493D_DisableCollisionAvoidanceFuncPtr    disableCollisionAvoidance;

    TLx493D_SetPowerModeFuncPtr                 setPowerMode;
    TLx493D_SetUpdateRateFuncPtr                setUpdateRate;

    /** Functions related to the "Diag" register. */
    TLx493D_HasValidDataFuncPtr                 hasValidData;
    TLx493D_IsFunctionalFuncPtr                 isFunctional;


    /** Functions available only to a subset of sensors with wake-up functionality. The functions are related to the WU register. */
    TLx493D_HasWakeUpFuncPtr                    hasWakeUp;
    TLx493D_IsWakeUpEnabledFuncPtr              isWakeUpEnabled;
    TLx493D_EnableWakeUpModeFuncPtr             enableWakeUpMode;
    TLx493D_DisableWakeUpModeFuncPtr            disableWakeUpMode;

    TLx493D_SetWakeUpThresholdsAsIntegerFuncPtr setWakeUpThresholdsAsInteger;                
    TLx493D_SetWakeUpThresholdsFuncPtr          setWakeUpThresholds;                

    TLx493D_SoftwareResetFuncPtr                softwareReset;
    

    /** Functions used internally and not accessible through the common interface. */
    TLx493D_CalculateFuseParityFuncPtr          calculateFuseParity;
    TLx493D_CalculateBusParityFuncPtr           calculateBusParity;
    TLx493D_CalculateConfigParityFuncPtr        calculateConfigurationParity;
    
    TLx493D_HasValidFuseParityFuncPtr           hasValidFuseParity;
    TLx493D_HasValidBusParityFuncPtr            hasValidBusParity;
    TLx493D_HasValidConfigParityFuncPtr         hasValidConfigurationParity;
   
    TLx493D_HasValidWakeUpParityFuncPtr         hasValidWakeUpParity;
    TLx493D_isInTestModeFuncPtr                 isInTestMode;

    TLx493D_HasValidTBitFuncPtr                 hasValidTBit;
 
    TLx493D_SetResetValuesFuncPtr               setResetValues;

    TLx493D_SelectIICAddressFuncPtr             selectIICAddress;

    TLx493D_CalculateRawMagneticFieldAtTemperatureFuncPtr  calculateRawMagneticFieldAtTemperature;

    TLx493D_GetSensitivityScaleFactorFuncPtr    getSensitivityScaleFactor;

    TLx493D_PrintRegistersFuncPtr               printRegisters;
} TLx493D_CommonFunctions_t;


/**
 * @brief The structure `TLx493D_t` stores all relevant information for a particular sensor.
 */
typedef struct TLx493D_t {
    uint8_t                         *regMap;
    TLx493D_Register_t              *regDef;
    TLx493D_CommonFunctions_t       *functions;

    TLx493D_CommunicationInterface_t  comInterface;

    TLx493D_BoardSupportInterface_t   boardSupportInterface;

    uint8_t                                     regMapSize;
    TLx493D_SupportedSensorType_t               sensorType;
    TLx493D_SupportedComLibraryInterfaceType_t  comIFType;
} TLx493D_t;


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_TYPES_H */