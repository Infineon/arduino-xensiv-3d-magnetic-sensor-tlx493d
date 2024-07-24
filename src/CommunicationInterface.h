#ifndef TLX493D_COMMUNICATION_INTERFACE_H
#define TLX493D_COMMUNICATION_INTERFACE_H


/** std includes. */
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus

extern "C" {

#endif


/** `Tlx493D_t` is a struct which contains all important elements for the 3D-Magnetic senors, like the internal register map, register definitions, 
 * common function definitions, etc. and is essential to define the sensor objects. */
typedef struct TLx493D_t  TLx493D_t;


/**
 * @brief The function `tlx493d_transfer` is a generic function to transfer data. It is implemented for each communication interface offered by the
 * different senors (SPI, I2C, etc.).
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in, out] txBuffer Buffer for the data that should be transferred.
 * @param[in] txLen Length of the transfer buffer.
 * @param[in, out] rxBuffer Buffer for the data that should be received.
 * @param[in] rxLen Length of the receive buffer.
 * 
 * @return The function `tlx493d_transfer` is returning a boolean value.
 * @retval false Error.
 * @retval true Transfer of the data was successful.
*/
bool tlx493d_transfer(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen);


/**
 * @brief The function `tlx493d_setReadAddress` sets the address for the communication interface. This address will be used to communicate with the
 * used sensor device.
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in] address Desired read address for the communication interface.
*/
void tlx493d_setReadAddress(TLx493D_t *sensor, uint8_t address);


#ifdef __cplusplus

}

#endif


#ifdef __cplusplus

namespace ifx {
    namespace tlx493d {

#endif


/**
 * @brief The function `deinitCommunication` is used to de-initialize the communication interface of the used sensor.
 * 
 * @param[in, out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
 * @param[in] executeDeinit Boolean value to determine if the communication interface should be de-initialzed or not. 
*/
void deinitCommunication(TLx493D_t *sensor, bool executeDeinit);


#ifdef __cplusplus

    }
}

#endif


#endif /** TLX493D_COMMUNICATION_INTERFACE_H */
