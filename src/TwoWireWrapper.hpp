#ifndef TLX493D_TWOWIRE_WRAPPER_HPP
#define TLX493D_TWOWIRE_WRAPPER_HPP


/** Arduino includes. */
#include <Arduino.h>
#include <Wire.h>


namespace ifx {
    namespace tlx493d {
        /**
         * @brief The class `TwoWireWrapper` is used to make the generic `TwoWire` available for Arduino.
         */
        class TwoWireWrapper {

            public:

                using BusType = TwoWire;


                /**
                 * @brief Constructor of the `TwoWireWrapper` class with a TwoWire function parameter. The passed
                 * TwoWire object is set to the icc attribute.
                 * 
                 * @param[in] bus Pointer to a TwoWire object which is set to icc class attribute. 
                 */
                explicit TwoWireWrapper(TwoWire &bus) : iic(&bus) {
                }


                /**
                 * @brief Destructor of the `TwoWireWrapper` class. 
                 */
                ~TwoWireWrapper() {
                }


                /**
                 * @brief The function `init` initializes the icc-object of the class. 
                 */
                void init() {
                    iic->begin();
                }


                /**
                 * @brief The function `deinit` de-initializes the icc-object of the class. 
                 */
                void deinit() {
                    iic->end();
                }


                /**
                 * @brief The function `transfer` is used to transfer the data through the I2C interface
                 * of the sensor.
                 * 
                 * @param[in] iicAddress I2C address of the sensor with which the communication should be established.
                 * @param[in] txBuffer Transmit buffer for the data that should be sent via I2C.
                 * @param[in] txLen Length of the data that should be sent.
                 * @param[in] rxBuffer Receive buffer for the data that is received during the I2C communication.
                 * @param[in] rxLen Length of the data that should be received.
                 * 
                 * @return The functions returns a boolean to indicate if the the transfer was successful.
                 * @retval false Error.
                 * @retval true Success.
                 */
                bool transfer(uint8_t iicAddress, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
                    if( (txLen > 0) && (txBuffer != NULL) ) {
                        iic->beginTransmission(iicAddress);

                        uint8_t bytesWritten = iic->write(txBuffer, txLen);
                        iic->endTransmission(true);

                        if( bytesWritten != txLen ) {
                            return false;
                        }
                    }

                    if( (rxLen > 0)  && (rxBuffer != NULL) ) {
                        uint8_t bytesRead = iic->requestFrom(iicAddress, rxLen);

                        for(uint16_t i = 0; (i < rxLen) && (iic->available() > 0); ++i) {
                            rxBuffer[i] = iic->read();
                        }

                        if( bytesRead != rxLen ) {
                            return false;
                        }
                    }

                    return true;
                }


                /**
                 * @brief The function `getBus` returns the iic-bus object.
                 * 
                 * @return Returns the iic-bus object of the class.
                 */
                TwoWire &getBus() {
                    return *iic;
                }


            private:

                TwoWire *iic;
        };
    }
}


#endif // TLX493D_TWOWIRE_WRAPPER_HPP
