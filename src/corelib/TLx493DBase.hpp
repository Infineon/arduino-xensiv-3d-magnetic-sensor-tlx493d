#ifndef TLX493D_BASE_HPP
#define TLX493D_BASE_HPP


/** std includes. */
#ifdef __AVR__

    #include <stdint.h>

#else

    #include <cstdint>

#endif


/** project c includes. */
#include "tlx493d_types.h"
#include "tlx493d.h"


namespace ifx {
    namespace tlx493d {
        /**
         * @brief The class `TLx493DBase` is the base class of the different TLx493D sensors variants.
         * It defines all available functions of the sensors and routes the member function calls to the
         * underlying c-function calls, which will be executed in the end.
         * 
         */
        class TLx493DBase {

            public:

                /**
                 * @brief The function `~TLx493DBase` is the destructor of the TLx493DBase class object.
                 * 
                 */
                ~TLx493DBase() {
                }

                /**
                 * @brief The function `readRegisters` reads registers from a TLx493D sensor.
                 * It is reading out the complete register map of the sensor and is saving the current
                 * values to the "internal" register map of the sensor object.
                 * 
                 * @return The function `readRegisters` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool readRegisters() {
                    return ::tlx493d_readRegisters(&sensor);
                }

                /**
                 * @brief The function `getRawTemperature` retrieves the raw temperature from a TLx493D sensor.
                 * It is reading out the temperature registers of the sensor and is returning its value as LSB.
                 * 
                 * @param[in,out] temperature A pointer to an int16_t variable where the raw temperature value will be stored.
                 *  
                 * @return The function `tlx493d_getRawTemperature` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool getRawTemperature(int16_t *temperature) {
                    return ::tlx493d_getRawTemperature(&sensor, temperature);
                }

                /**
                 * @brief The function `getRawMagneticField` retrieves the raw magnetic field values from a TLx493D
                 * sensor. It is reading the magnetic field value registers of the sensor and is returning them as LSB for the
                 * X, Y, Z-direction.
                 * 
                 * @param[in,out] x A pointer to a variable where the raw magnetic field value along the x-axis will be stored.
                 * @param[in,out] y A pointer to a variable where the raw magnetic field value along the y-axis will be stored.
                 * @param[in,out] z A pointer to a variable where the raw magnetic field value along the z-axis will be stored.
                 *  
                 * @return The function `getRawMagneticField` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool getRawMagneticField(int16_t *x, int16_t *y, int16_t *z) {
                    return ::tlx493d_getRawMagneticField(&sensor, x, y, z);
                }

                /**
                 * @brief The function `getRawMagneticFieldAndTemperature` retrieves the raw magnetic field and
                 * temperature values from a TLx493D sensor. It is reading out the magnetic field value registers, as well
                 * as the temperature value registers of the sensor and is returning them as LSB.
                 * 
                 * @param[in,out] x     A pointer to a variable where the raw magnetic field value along the x-axis will be stored.
                 * @param[in,out] y     A pointer to a variable where the raw magnetic field value along the y-axis will be stored.
                 * @param[in,out] z     A pointer to a variable where the raw magnetic field value along the z-axis will be stored.
                 * @param[in,out] temp  A pointer to a variable where the raw temperature value will be stored.
                 * 
                 * @return The function `getRawMagneticFieldAndTemperature` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool getRawMagneticFieldAndTemperature(int16_t *x, int16_t *y, int16_t *z, int16_t *temp) {
                    return ::tlx493d_getRawMagneticFieldAndTemperature(&sensor, x, y, z, temp);
                }

                /**
                 * @brief The function `getTemperature` retrieves the temperature from a TLx493D sensor in °C.
                 * It is reading out the temperature registers of the sensor and converts the values into °C with the formula
                 * that is provided in the datasheet of the sensor.
                 * 
                 * @param[in,out] temperature A pointer to a double variable where the temperature value will be stored in °C.
                 *  
                 * @return The function `getTemperature` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool getTemperature(double *temperature) {
                    return ::tlx493d_getTemperature(&sensor, temperature);
                }

                /**
                 * @brief The function `getMagneticField` retrieves the magnetic field values from a TLx493D sensor.
                 * It is reading out the magnetic field value registers of the sensor and is converting the retrieved data into
                 * values in mT for each magnetic field axis.
                 * 
                 * @param[in,out] x A pointer to a variable where the magnetic field value in mT along the x-axis will be stored.
                 * @param[in,out] y A pointer to a variable where the magnetic field value in mT along the y-axis will be stored.
                 * @param[in,out] z A pointer to a variable where the magnetic field value in mT along the z-axis will be stored.
                 *  
                 * @return The function `getMagneticField` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool getMagneticField(double *x, double *y, double *z) {
                    return ::tlx493d_getMagneticField(&sensor, x, y, z);
                }

                /**
                 * @brief The function `getMagneticFieldAndTemperature` retrieves the magnetic field and temperature
                 * readings from a TLx493D sensor.
                 * It combines the two functions `getMagneticFieldAndTemperature` and `tlx493d_getMagneticField` in order to have one
                 * function which is providing the temperature as well as the magnetic field values of the sensor.
                 * 
                 * @param[in,out] x     A pointer to a variable where the magnetic field value in mT along the x-axis will be stored.
                 * @param[in,out] y     A pointer to a variable where the magnetic field value in mT along the y-axis will be stored.
                 * @param[in,out] z     A pointer to a variable where the magnetic field value in mT along the z-axis will be stored.
                 * @param[in,out] temp  A pointer to a double variable where the temperature value in °C will be stored.
                 *  
                 * @return The function `getMagneticFieldAndTemperature` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool getMagneticFieldAndTemperature(double *x, double *y, double *z, double *temp) {
                    return ::tlx493d_getMagneticFieldAndTemperature(&sensor, x, y, z, temp);
                }


                // functions related to the "Config" register
                /**
                 * @brief The function `setMeasurement` sets the measurement type for a TLx493D sensor.
                 * It is writing to the corresponding bitfields in the config-register in order to set the desired
                 * measuring mode of the sensor.
                 * 
                 * @param[in] meas The `meas` parameter is of type `TLx493D_MeasurementType_t`, which is an enumeration
                 * type representing different measurement types for the TLx493D sensor. All available options can be found in the
                 * enum `TLx493D_MeasurementType_t` in the library file `tlx493d_types.h`.
                 *  
                 * @return The function `setMeasurement` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool setMeasurement(TLx493D_MeasurementType_t meas) {
                    return ::tlx493d_setMeasurement(&sensor, meas);
                }

                /**
                 * @brief The function `setTrigger` sets the trigger type for a TLx493D sensor.
                 * It is writing to the corresponding bitfields in the config-register in order to set the desired
                 * trigger mode of the sensor.
                 * 
                 * @param[in] bits The `bits` parameter is of type `TLx493D_TriggerType_t`, which is an enumeration type
                 * representing different trigger types for the TLx493D sensor. All the available options can be found in the enum
                 * `TLx493D_TriggerType_t` in the library file `tlx493d_types`.
                 *   
                 * @return The function `setTrigger` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setTrigger(TLx493D_TriggerType_t bits) {
                    return ::tlx493d_setTrigger(&sensor, bits);
                }

                /**
                 * @brief The function `setSensitivity` sets the sensitivity of a TLx493D sensor.
                 * It is writing to the corresponding bitfields in the registers of the sensor in order to set
                 * the desired measuring range.
                 * 
                 * @param[in] range The `range` parameter is of type `TLx493D_SensitivityType_t, which is an enumeration type
                 * that represents the sensitivity range of the sensor. All available options can be found in the enum
                 * `TLx493D_SensitivityType_t` in the library file `tlx493d_types`.
                 *  
                 * @return The function `setSensitivity` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setSensitivity(TLx493D_SensitivityType_t range) {
                    return ::tlx493d_setSensitivity(&sensor, range);
                }


                // functions related to the "Mod1" and "Mod2" registers
                /**
                 * @brief The function `setDefaultConfig` sets the default configuration for a TLx493D sensor.
                 * It puts the sensor into the 1-Byte-Read-Mode and turns off the interrupt. This is required to guarantee
                 * the proper functionality of the sensor.
                 * 
                 * @return The function `setDefaultConfig` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setDefaultConfig() {
                    return ::tlx493d_setDefaultConfig(&sensor);
                }

                /**
                 * @brief The function `setIICAddress` sets the IIC address of a TLx493D sensor.
                 * It is writing to the corresponding bitfields of the sensor in order to change the I2C-Default-Address
                 * of the sensor to the desired address of the user.
                 * 
                 * @param[in] addr The `addr` parameter is of type `TLx493D_IICAddressType_t` , which is an enumeration type
                 * representing the I2C address of the sensor. You can see all available addresses in the enum `TLx493D_IICAddressType_t`
                 * in the library file `tlx493d_types.h`.
                 *  
                 * @return The function `setIICAddress` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setIICAddress(TLx493D_IICAddressType_t addr) {
                    return ::tlx493d_setIICAddress(&sensor, addr);
                }

                /**
                 * @brief The function `enableCollisionAvoidance` enables collision avoidance for a TLx493D sensor.
                 * 
                 * @return The function `enableCollisionAvoidance` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool enableCollisionAvoidance() {
                    return ::tlx493d_enableCollisionAvoidance(&sensor);
                }

                /**
                 * @brief The function `disableCollisionAvoidance` disables collision avoidance for a TLx493D sensor.
                 * 
                 * @return The function `disableCollisionAvoidance` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool disableCollisionAvoidance() {
                    return ::tlx493d_disableCollisionAvoidance(&sensor);
                }

                /**
                 * @brief The function `enableInterrupt` enables interrupts for a TLx493D sensor.
                 * 
                 * @return The function `enableInterrupt` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool enableInterrupt() {
                    return ::tlx493d_enableInterrupt(&sensor);
                }

                /**
                 * @brief The function `disableInterrupt` is used to disable interrupts for a TLx493D sensor.
                 * 
                 * @return The function `disableInterrupt` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool disableInterrupt() {
                    return ::tlx493d_disableInterrupt(&sensor);
                }

                /**
                 * @brief The function `setPowerMode` sets the power mode of a TLx493D sensor.
                 * It is writing to the corresponding bitfields of the sensor in order to set one of the three 
                 * available power modes of the sensor.
                 * 
                 * @param[in] mode The `mode` parameter is of type `TLx493D_PowerModeType_t`, which is an enumeration type
                 * representing different power modes for the TLx493D sensor. All available options can be found in the enum 
                 * `TLx493D_PowerModeType_t` in the library file `tlx493d_types.h`.
                 * 
                 * @return The function `setPowerMode` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setPowerMode(TLx493D_PowerModeType_t mode) {
                    return ::tlx493d_setPowerMode(&sensor, mode);
                }

                /**
                 * @brief The function `setUpdateRate` sets the update rate of a TLx493D sensor.
                 * It is writing to the corresponding bitfields of the sensor in order to set the desired update frequency,
                 * with which the sensor will update his measured values.
                 * 
                 * @param[in] bit The `bit` parameter is of type `TLx493D_UpdateRateType_t`, which is an enumeration type
                 * representing different update rates for the sensor. All available options can be found in the enum `TLx493D_UpdateRateType_t`
                 * in the library file ´tlx493d_types.h`.
                 *  
                 * @return The function `setUpdateRate` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool setUpdateRate(TLx493D_UpdateRateType_t bit) {
                    return ::tlx493d_setUpdateRate(&sensor, bit);
                }


                // functions related to the "Diag" register
                /**
                 * @brief The function `hasValidData` checks if the TLx493D sensor has valid data.
                 * It is checking the corresponding bitfield of the sensor which indicates if the acquired measurement
                 * data is valid or not.
                 * 
                 * @return The function `hasValidData` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool hasValidData() {
                    return ::tlx493d_hasValidData(&sensor);
                }
                
                /**
                 * @brief The function `isFunctional` checks if a TLx493D sensor is functional.
                 * It checks the internal fuse parity bit as well as the config parity bit in order to confirm that
                 * the sensor is still functional.  
                 * 
                 * @return The function `isFunctional` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.  
                 */
                bool isFunctional() {
                    return ::tlx493d_isFunctional(&sensor);
                }


                // functions available only to a subset of sensors with wake-up functionality
                /**
                 * @brief The function `hasWakeUp` checks if a TLx493D sensor has wake-up functionality.
                 * It simply checks the bitfield which indicates if the sensor has a wake-up functionality or not. 
                 * 
                 * @return The function `hasWakeUp` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.  
                 */
                bool hasWakeUp() {
                    return ::tlx493d_hasWakeUp(&sensor);
                }

                /**
                 * @brief The function `isWakeUpEnabled` checks if wake-up mode is enabled for a TLx493D sensor.
                 * It checks the bitfield of the sensor which gives you the information if the wake-up is enabled or not.
                 * 
                 * @return The function `isWakeUpEnabled` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool isWakeUpEnabled() {
                    return ::tlx493d_isWakeUpEnabled(&sensor);
                }

                /**
                 * @brief The function `enableWakeUpMode` enables the wake-up mode for the TLx493D sensor.
                 * 
                 * @return The function `enableWakeUpMode` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool enableWakeUpMode() {
                    return ::tlx493d_enableWakeUpMode(&sensor);
                }

                /**
                 * @brief The function `disableWakeUpMode` disables the wake-up mode of a TLx493D sensor.
                 * 
                 * @return The function `disableWakeUpMode` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful.
                 */
                bool disableWakeUpMode() {
                    return ::tlx493d_disableWakeUpMode(&sensor);
                }

                /**
                 * @brief The function `setWakeUpThresholdsAsInteger` sets the wake-up thresholds for a TLx493D sensor
                 * using integer values.
                 * It sets the lower and upper threshold for each of three axis. If one of these thresholds is exceeded the sensor
                 * will trigger an interrupt. It will continue to trigger interrupts as long as the threshold is exceeded.
                 * 
                 * @param[in] xl_th The lower threshold value for the magnetic field in x-axis.
                 * @param[in] xh_th The upper threshold value for the magnetic field in x-axis.
                 * @param[in] yl_th The lower threshold value for the magnetic field in y-axis.
                 * @param[in] yh_th The upper threshold value for the magnetic field in y-axis.
                 * @param[in] zl_th The lower threshold value for the magnetic field in z-axis.
                 * @param[in] zh_th The upper threshold value for the magnetic field in z-axis.
                 * 
                 * @return The function `setWakeUpThresholdsAsInteger` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool setWakeUpThresholdsAsInteger(int16_t xl_th, int16_t xh_th, int16_t yl_th, int16_t yh_th, int16_t zl_th, int16_t zh_th) {
                    return ::tlx493d_setWakeUpThresholdsAsInteger(&sensor, xl_th, xh_th, yl_th, yh_th, zl_th, zh_th);
                }


                /**
                 * @brief The function `setWakeUpThresholds` sets the wake-up thresholds for the TLx493D sensor in mT.
                 * It sets the lower and upper threshold for each of three axis in mT. If one of these thresholds is exceeded the sensor
                 * will trigger an interrupt. It will continue to trigger interrupts as long as the threshold is exceeded.
                 * 
                 * @param[in] temperature The temperature to be used for derating the field values.
                 * @param[in] xl_th       The lower threshold value for the magnetic field in x-axis.
                 * @param[in] xh_th       The upper threshold value for the magnetic field in x-axis.
                 * @param[in] yl_th       The lower threshold value for the magnetic field in y-axis.
                 * @param[in] yh_th       The upper threshold value for the magnetic field in y-axis.
                 * @param[in] zl_th       The lower threshold value for the magnetic field in z-axis.
                 * @param[in] zh_th       The upper threshold value for the magnetic field in z-axis.
                 * 
                 * @return The function `setWakeUpThresholds` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool setWakeUpThresholds(double temperature, double xl_th, double xh_th, double yl_th, double yh_th, double zl_th, double zh_th) {
                    return ::tlx493d_setWakeUpThresholds(&sensor, temperature, xl_th, xh_th, yl_th, yh_th, zl_th, zh_th);
                }

                /**
                 * @brief The function `softwareReset` performs a software reset on the TLx493D sensor.
                 * 
                 * @return The function `softwareReset` is returning a boolean value.
                 * @retval false Error.
                 * @retval true Function execution was successful. 
                 */
                bool softwareReset() {
                    return ::tlx493d_softwareReset(&sensor);
                }


                // utilities
                /**
                 * @brief The function `getTypeAsString` returns the type of the TLx493D sensor as a string.
                 * 
                 * @return The function `tlx493d_getTypeAsString` returns a pointer to a constant character string.
                 */
                const char *getTypeAsString() {
                    return ::tlx493d_getTypeAsString(&sensor);
                }

                /**
                 * @brief The function `calculateRawMagneticFieldAtTemperature` calculates the raw magnetic field at a
                 * given temperature.
                 * 
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
                void calculateRawMagneticFieldAtTemperature(int16_t rawTemp, TLx493D_SensitivityType_t sens,
                                                            double xInmT, double yInmT, double zInmT,
                                                            int16_t *x, int16_t *y, int16_t *z) {
                    ::tlx493d_calculateRawMagneticFieldAtTemperature(&sensor, rawTemp, sens, xInmT, yInmT, zInmT, x, y, z);
                }


                /**
                 * @brief The function `printRegisters` prints out the internal registers of the sensor object. It can be used
                 * to check certain values of the sensor register map.
                 */
                void printRegisters() {
                    ::tlx493d_printRegisters(&sensor);
                }


                // Attribute getters for TLx493D object
                /**
                 * @brief The function `getSensor` retrieves the sensor object of the class.
                 * 
                 * @return A pointer to the sensor structure `TLx493D_t`.
                 */
                TLx493D_t *getSensor() {
                    return &sensor;
                }

                /**
                 * @brief The function `getSensorType` retrieves the specific sensor type from the sensor object.
                 * 
                 * @return A `TLx493D_SupportedSensorType_t` enum which contains the specific sensor type.
                 */
                TLx493D_SupportedSensorType_t getSensorType() {
                    return sensor.sensorType;
                }

                /**
                 * @brief The function `getComLibIFType` is returning the communication interface of the sensor.
                 * It is reading out the corresponding structure member of the sensor object.
                 * 
                 * @return A `TLx493D_SupportedComLibraryInterfaceType_t` enum which contains the communication
                 * interface type.
                 * @retval TLx493D_I2C_e If the sensor communication interface is set to I2C.
                 * @retval TLx493D_SPI_e If the sensor communication interface is set to SPI.
                 */
                TLx493D_SupportedComLibraryInterfaceType_t getComLibIFType() {
                    return sensor.comIFType;
                }

                /**
                 * @brief The function `getRegisterMap` gets the internal register map of the sensor object.
                 * 
                 * @return A pointer to the register map array with its saved values.
                 */
                uint8_t *getRegisterMap() {
                    return sensor.regMap;
                }

                /**
                 * @brief The function `getRegisterMapSize` returns the register map size of the internal register
                 * map of the sensor object.
                 * 
                 * @return Size of the internal register map. 
                 */
                uint8_t getRegisterMapSize() {
                    return sensor.regMapSize;
                }

                /**
                 * @brief The function `getI2CAddress` is returning the I2C address of the sensor.
                 * It is reading out the I2C address stored within the sensor object.
                 * 
                 * @return I2C address of the sensor.
                 */
                uint8_t getI2CAddress() {
                    return sensor.comInterface.comLibParams.iic_params.address;
                }


            protected:

                /**
                 * @brief The function `TLx493DBase` is the constructor of the class.
                 * 
                 */
                TLx493DBase() {
                }

                TLx493D_t  sensor; /**< Declaration of the sensor object structure. */
        };


        /**
         * @brief The class `TLx493D` is a template class, which inherits its functionality from the `TLx493DBase` class. 
         * 
         * @tparam BoardSupportClass A helper class, which takes care of needed power pins as well user defined pins.
         * @tparam BusWrapper A wrapper class for the bus system.
         * @tparam sensorType Specific sensor type of the used sensor.
         */
        template<typename BoardSupportClass, typename BusWrapper, TLx493D_SupportedSensorType_t sensorType>
            class TLx493D : public TLx493DBase {

            private:

                using BusType = typename BusWrapper::BusType;


                TLx493D();
                explicit TLx493D(BusType &c);
        };
    }
}

#endif // TLX493D_BASE_HPP
