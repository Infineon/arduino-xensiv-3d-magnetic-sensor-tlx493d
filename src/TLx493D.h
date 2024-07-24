#ifndef TLX493D_H
#define TLX493D_H


#ifdef __cplusplus

extern "C" {

#endif


/** project c includes. */
#include "tlx493d_types.h"


/**
 * @brief The function `tlx493d_init` initializes a TLx493D sensor based on the specified sensor type.
 * It is calling the initialization function of the corresponding sensor, depending on the sensor type that
 * is passed to the function.
 * 
 * @param[in,out]   sensor      A pointer to a TLx493D_t structure, which represents the sensor being initialized.
 * @param[in]       sensorType  The sensorType parameter is of type TLx493D_SupportedSensorType_t, which is an
 * enumeration representing the supported sensor types for the TLx493D sensor.
 * 
 * @return The function `tlx493d_init` returns a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_init(TLx493D_t *sensor, TLx493D_SupportedSensorType_t sensorType);

/**
 * @brief The function `tlx493d_deinit` is used to deinitialize a TLx493D sensor.
 * It frees all allocated memory which was allocated through the initialization.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t structure, which represents the sensor being deinitialized.
 * 
 * @return The function `tlx493d_deinit` returns a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_deinit(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_readRegisters` reads registers from a TLx493D sensor.
 * It is reading out the complete register map of the sensor and is saving the current
 * values to the "internal" register map of the sensor object.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_readRegisters` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_readRegisters(TLx493D_t *sensor);


/**
 * @brief The function `tlx493d_getRawTemperature` retrieves the raw temperature from a TLx493D sensor.
 * It is reading out the temperature registers of the sensor and is returning its value as LSB.
 * 
 * @param[in,out] sensor        A pointer to a TLx493D_t structure, which represents the TLx493D sensor.
 * @param[in,out] temperature   A pointer to an int16_t variable where the raw temperature value will be stored.
 * 
 * @return The function `tlx493d_getRawTemperature` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getRawTemperature(TLx493D_t *sensor, int16_t *temperature);

/**
 * @brief The function `tlx493d_getRawMagneticField` retrieves the raw magnetic field values from a TLx493D
 * sensor.
 * It is reading the magnetic field value registers of the sensor and is returning them as LSB for the
 * X, Y, Z-direction.
 * 
 * @param[in,out] sensor    A pointer to the TLx493D_t structure that represents the sensor.
 * @param[in,out] x         A pointer to a variable where the raw magnetic field value along the x-axis will be stored.
 * @param[in,out] y         A pointer to a variable where the raw magnetic field value along the y-axis will be stored.
 * @param[in,out] z         A pointer to a variable where the raw magnetic field value along the z-axis will be stored.
 * 
 * @return The function `tlx493d_getRawMagneticField` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getRawMagneticField(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z);

/**
 * @brief The function `tlx493d_getRawMagneticFieldAndTemperature` retrieves the raw magnetic field and
 * temperature values from a TLx493D sensor.
 * It is reading out the magnetic field value registers, as well as the temperature value registers of the sensor
 * and is returning them as LSB.
 * 
 * @param[in,out] sensor        A pointer to the TLx493D_t structure that represents the sensor.
 * @param[in,out] x             A pointer to a variable where the raw magnetic field value along the x-axis will be stored.
 * @param[in,out] y             A pointer to a variable where the raw magnetic field value along the y-axis will be stored.
 * @param[in,out] z             A pointer to a variable where the raw magnetic field value along the z-axis will be stored.
 * @param[in,out] temperature   A pointer to a variable where the raw temperature value will be stored.
 * 
 * @return The function `tlx493d_getRawMagneticFieldAndTemperature` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getRawMagneticFieldAndTemperature(TLx493D_t *sensor, int16_t *x, int16_t *y, int16_t *z, int16_t *temperature);


/**
 * @brief The function `tlx493d_getTemperature` retrieves the temperature from a TLx493D sensor in °C.
 * It is reading out the temperature registers of the sensor and converts the values into °C with the formula
 * that is provided in the datasheet of the sensor.
 * 
 * @param[in,out] sensor        A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in,out] temperature   A pointer to a double variable where the temperature value will be stored in °C.
 * 
 * @return The function `tlx493d_getTemperature` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getTemperature(TLx493D_t *sensor, double *temperature);

/**
 * @brief The function `tlx493d_getMagneticField` retrieves the magnetic field values from a TLx493D sensor.
 * It is reading out the magnetic field value registers of the sensor and is converting the retrieved data into
 * values in mT for each magnetic field axis.
 * 
 * @param[in,out] sensor    A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in,out] x         A pointer to a variable where the magnetic field value in mT along the x-axis will be stored.
 * @param[in,out] y         A pointer to a variable where the magnetic field value in mT along the y-axis will be stored.
 * @param[in,out] z         A pointer to a variable where the magnetic field value in mT along the z-axis will be stored.
 * 
 * @return The function `tlx493d_getMagneticField` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getMagneticField(TLx493D_t *sensor, double *x, double *y, double *z);

/**
 * @brief The function `tlx493d_getMagneticFieldAndTemperature` retrieves the magnetic field and temperature
 * readings from a TLx493D sensor.
 * It combines the two functions `tlx493d_getTemperature` and `tlx493d_getMagneticField` in order to have one
 * function which is providing the temperature as well as the magnetic field values of the sensor.
 * 
 * @param[in,out] sensor        A pointer to the TLx493D_t structure that represents the sensor.
 * @param[in,out] x             A pointer to a variable where the magnetic field value in mT along the x-axis will be stored.
 * @param[in,out] y             A pointer to a variable where the magnetic field value in mT along the y-axis will be stored.
 * @param[in,out] z             A pointer to a variable where the magnetic field value in mT along the z-axis will be stored.
 * @param[in,out] temperature   A pointer to a double variable where the temperature value in °C will be stored.
 * 
 * @return The function `tlx493d_getMagneticFieldAndTemperature` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_getMagneticFieldAndTemperature(TLx493D_t *sensor, double *x, double *y, double *z, double *temperature);


/** functions related to the "Config" register. */
/**
 * @brief The function `tlx493d_setMeasurement` sets the measurement type for a TLx493D sensor.
 * It is writing to the corresponding bitfields in the config-register in order to set the desired
 * measuring mode of the sensor.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in]       meas    The `meas` parameter is of type `TLx493D_MeasurementType_t`, which is an enumeration
 * type representing different measurement types for the TLx493D sensor. All available options can be found in the
 * enum `TLx493D_MeasurementType_t` in the library file `tlx493d_types.h`.
 * 
 * @return The function `tlx493d_setMeasurement` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setMeasurement(TLx493D_t *sensor, TLx493D_MeasurementType_t meas);

/**
 * @brief The function `tlx493d_setTrigger` sets the trigger type for a TLx493D sensor.
 * It is writing to the corresponding bitfields in the config-register in order to set the desired
 * trigger mode of the sensor.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the sensor.
 * @param[in]       trigger The `trigger` parameter is of type `TLx493D_TriggerType_t`, which is an enumeration type
 * representing different trigger types for the TLx493D sensor. All the available options can be found in the enum
 * `TLx493D_TriggerType_t` in the library file `tlx493d_types`.
 * 
 * @return The function `tlx493d_setTrigger` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setTrigger(TLx493D_t *sensor, TLx493D_TriggerType_t trigger);

/**
 * @brief The function `tlx493d_setSensitivity` sets the sensitivity of a TLx493D sensor.
 * It is writing to the corresponding bitfields in the registers of the sensor in order to set
 * the desired measuring range.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in]       range   The `range` parameter is of type `TLx493D_SensitivityType_t, which is an enumeration type
 * that represents the sensitivity range of the sensor. All available options can be found in the enum
 * `TLx493D_SensitivityType_t` in the library file `tlx493d_types`.
 * 
 * @return The function `tlx493d_setSensitivity` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setSensitivity(TLx493D_t *sensor, TLx493D_SensitivityType_t range);


/** functions related to the "Mod1" and "Mod2" registers. */
/**
 * @brief The function `tlx493d_setDefaultConfig` sets the default configuration for a TLx493D sensor.
 * It puts the sensor into the 1-Byte-Read-Mode and turns off the interrupt. This is required to guarantee
 * the proper functionality of the sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_setDefaultConfig` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setDefaultConfig(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_setIICAddress` sets the IIC address of a TLx493D sensor.
 * It is writing to the corresponding bitfields of the sensor in order to change the I2C-Default-Address
 * of the sensor to the desired address of the user.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in]       addr    The `addr` parameter is of type `TLx493D_IICAddressType_t` , which is an enumeration type
 * representing the I2C address of the sensor. You can see all available addresses in the enum `TLx493D_IICAddressType_t`
 * in the library file `tlx493d_types.h`.
 * 
 * @return The function `tlx493d_setIICAddress` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setIICAddress(TLx493D_t *sensor, TLx493D_IICAddressType_t addr);

/**
 * @brief The function `tlx493d_enableCollisionAvoidance` enables collision avoidance for a TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_enableCollisionAvoidance` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_enableCollisionAvoidance(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_disableCollisionAvoidance` disables collision avoidance for a TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_disableCollisionAvoidance` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_disableCollisionAvoidance(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_enableInterrupt` enables interrupts for a TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_enableInterrupt` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_enableInterrupt(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_disableInterrupt` is used to disable interrupts for a TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_disableInterrupt` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_disableInterrupt(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_setPowerMode` sets the power mode of a TLx493D sensor.
 * It is writing to the corresponding bitfields of the sensor in order to set one of the three 
 * available power modes of the sensor.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in]       mode    The `mode` parameter is of type `TLx493D_PowerModeType_t`, which is an enumeration type
 * representing different power modes for the TLx493D sensor. All available options can be found in the enum 
 * `TLx493D_PowerModeType_t` in the library file `tlx493d_types.h`.
 * 
 * @return The function `tlx493d_setPowerMode` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setPowerMode(TLx493D_t *sensor, TLx493D_PowerModeType_t mode);

/**
 * @brief The function `tlx493d_setUpdateRate` sets the update rate of a TLx493D sensor.
 * It is writing to the corresponding bitfields of the sensor in order to set the desired update frequency,
 * with which the sensor will update his measured values.
 * 
 * @param[in,out]   sensor  A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in]       rate    The `rate` parameter is of type `TLx493D_UpdateRateType_t`, which is an enumeration type
 * representing different update rates for the sensor. All available options can be found in the enum `TLx493D_UpdateRateType_t`
 * in the library file ´tlx493d_types.h`.
 * 
 * @return The function `tlx493d_setUpdateRate` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setUpdateRate(TLx493D_t *sensor, TLx493D_UpdateRateType_t rate);


/** functions related to the "Diag" register. */
/**
 * @brief The function `tlx493d_hasValidData` checks if the TLx493D sensor has valid data.
 * It is checking the corresponding bitfield of the sensor which indicates if the acquired measurement
 * data is valid or not.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_hasValidData` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_hasValidData(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_isFunctional` checks if a TLx493D sensor is functional.
 * It checks the internal fuse parity bit as well as the config parity bit in order to confirm that
 * the sensor is still functional.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents a TLx493D sensor.
 * 
 * @return The function `tlx493d_isFunctional` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_isFunctional(TLx493D_t *sensor);


/** functions available only to a subset of sensors with wake-up functionality related to the "WU" register. */
/**
 * @brief The function `tlx493d_hasWakeUp` checks if a TLx493D sensor has wake-up functionality.
 * It simply checks the bitfield which indicates if the sensor has a wake-up functionality or not.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents a TLx493D sensor.
 * 
 * @return The function `tlx493d_hasWakeUp` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_hasWakeUp(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_isWakeUpEnabled` checks if wake-up mode is enabled for a TLx493D sensor.
 * It checks the bitfield of the sensor which gives you the information if the wake-up is enabled or not.
 * 
 * @param[in,out] sensor sensor is a pointer to a TLx493D_t struct, which represents a sensor.
 * 
 * @return The function `tlx493d_isWakeUpEnabled` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_isWakeUpEnabled(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_enableWakeUpMode` enables the wake-up mode for the TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_enableWakeUpMode` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_enableWakeUpMode(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_disableWakeUpMode` disables the wake-up mode of a TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_disableWakeUpMode` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_disableWakeUpMode(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_setWakeUpThresholdsAsInteger` sets the wake-up thresholds for a TLx493D sensor
 * using integer values.
 * It sets the lower and upper threshold for each of three axis. If one of these thresholds is exceeded the sensor
 * will trigger an interrupt. It will continue to trigger interrupts as long as the threshold is exceeded.
 * 
 * @param[in,out]   sensor  A pointer to the TLx493D_t structure, which represents the sensor.
 * @param[in]       xl_th   The lower threshold value for the magnetic field in x-axis.
 * @param[in]       xh_th   The upper threshold value for the magnetic field in x-axis.
 * @param[in]       yl_th   The lower threshold value for the magnetic field in y-axis.
 * @param[in]       yh_th   The upper threshold value for the magnetic field in y-axis.
 * @param[in]       zl_th   The lower threshold value for the magnetic field in z-axis.
 * @param[in]       zh_th   The upper threshold value for the magnetic field in z-axis.
 * 
 * @return The function `tlx493d_setWakeUpThresholdsAsInteger` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_setWakeUpThresholdsAsInteger(TLx493D_t *sensor, int16_t xl_th, int16_t xh_th, int16_t yl_th, int16_t yh_th,
                                          int16_t zl_th, int16_t zh_th);

/**
 * @brief The function `tlx493d_setWakeUpThresholds` sets the wake-up thresholds for the TLx493D sensor in mT.
 * It sets the lower and upper threshold for each of three axis in mT. If one of these thresholds is exceeded the sensor
 * will trigger an interrupt. It will continue to trigger interrupts as long as the threshold is exceeded.
 * 
 * @param[in,out]   sensor       A pointer to the TLx493D_t structure, which represents the sensor device.
 * @param[in]       temperature  The temperature to be used for derating the field values.
 * @param[in]       xLow         The lower threshold value for the magnetic field in x-axis.
 * @param[in]       xHigh        The upper threshold value for the magnetic field in x-axis.
 * @param[in]       yLow         The lower threshold value for the magnetic field in y-axis.
 * @param[in]       yHigh        The upper threshold value for the magnetic field in y-axis.
 * @param[in]       zLow         The lower threshold value for the magnetic field in z-axis.
 * @param[in]       zHigh        The upper threshold value for the magnetic field in z-axis.
 * 
 * @return The function `tlx493d_setWakeUpThresholds` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */                                       
bool tlx493d_setWakeUpThresholds(TLx493D_t *sensor, double temperature,
                                 double xLow, double xHigh, double yLow, double yHigh, double zLow, double zHigh);


/** utilities. */
/**
 * @brief The function `tlx493d_softwareReset` performs a software reset on the TLx493D sensor.
 * 
 * @param[in,out] sensor A pointer to the TLx493D_t structure, which represents the sensor device.
 * 
 * @return The function `tlx493d_softwareReset` is returning a boolean value.
 * @retval false Error.
 * @retval true Function execution was successful.
 */
bool tlx493d_softwareReset(TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_getTypeAsString` returns the type of the TLx493D sensor as a string.
 * 
 * @param[in,out] sensor A pointer to a TLx493D_t structure, which represents the TLx493D sensor.
 * 
 * @return The function `tlx493d_getTypeAsString` returns a pointer to a constant character string.
 */
const char *tlx493d_getTypeAsString(const TLx493D_t *sensor);

/**
 * @brief The function `tlx493d_calculateRawMagneticFieldAtTemperature` calculates the raw magnetic field at a
 * given temperature.
 * 
 * @param[in,out]   sensor      A pointer to a TLx493D_t structure, which represents the TLx493D sensor.
 * @param[in]       rawTemp     The raw temperature value obtained from the sensor.
 * @param[in]       sens        The parameter `sens` is of type `TLx493D_SensitivityType_t`, which is an enumeration type
 * representing the sensitivity level of the sensor. It is used to specify the desired sensitivity level for calculating
 * the raw magnetic field.
 * @param[in]       xInmT       The parameter `xInmT` represents the magnetic field strength in Millitesla (mT) along
 * the x-axis.
 * @param[in]       yInmT       The parameter `yInmT` represents the magnetic field strength in Millitesla (mT) along
 * the y-axis.
 * @param[in]       zInmT       The parameter `zInmT` represents the magnetic field strength in Millitesla (mT) along
 * the z-axis.
 * @param[in,out]   x           A pointer to a variable where the calculated raw magnetic field in the x-axis will be
 * stored.
 * @param[in,out]   y           A pointer to a variable where the calculated raw magnetic field in the y-axis will be
 * stored.
 * @param[in,out]   z           A pointer to a variable where the calculated raw magnetic field in the z-axis will be
 * stored.
 */
void tlx493d_calculateRawMagneticFieldAtTemperature(TLx493D_t *sensor, int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                    double xInmT, double yInmT, double zInmT,
                                                    int16_t *x, int16_t *y, int16_t *z);


/**
 * @brief The function `tlx493d_printRegisters` prints out the internal registers of the sensor object. It can be used
 * to check certain values of the sensor register map.
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t structure, which represents the TLx493D sensor.
*/
void tlx493d_printRegisters(TLx493D_t *sensor);


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_H */
