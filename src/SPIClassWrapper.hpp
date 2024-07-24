#ifndef TLX493D_SPICLASS_WRAPPER_HPP
#define TLX493D_SPICLASS_WRAPPER_HPP


/** Arduino includes. */
#include <Arduino.h>
#include <SPI.h>


namespace ifx {
    namespace tlx493d {
        /**
         * @brief The class `SPIClassWrapper` is used to make the generic `SPIClass` compatible with Arduino.
         * It wraps the required functions into the Arduino API calls.
         */
        class SPIClassWrapper {

            public:

                /** Sets the bus type to SPI. */
                using BusType = SPIClass;
                // typedef SPIClass BusType;

                static constexpr uint8_t TLX493D_SPI_READ_BIT_ON      = 0x80;
                // static constexpr uint8_t TLX493D_SPI_READ_BIT_OFF     = 0x00;

                // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT     = 0x60;
                // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT_ON  = 0x60;
                // static constexpr uint8_t TLX493D_SPI_AUTO_INC_BIT_OFF = 0x00;


                /**
                 * @brief Constructor of the `SPIClassWrapper`class with a `SPIClass` parameter. Can
                 * be used to pass a desired SPI instance to the wrapper.
                 */
                explicit SPIClassWrapper(SPIClass &bus) : spi(&bus) {
                }


                /**
                 * @brief Destructor of the `SPIClassWrapper`.
                 */
                ~SPIClassWrapper() {
                }


                /**
                 * @brief The SPIClass::init initializes the SPI interface. 
                 * 
                 */
                void init(const SPISettings &settings) {
                    spi->beginTransaction(settings);
                }


                /**
                 * @brief The function `deinit` de-initializes the SPI interface. 
                 */
                void deinit() {
                    spi->end();
                }


                /**
                 * @brief The function `transfer` is used to transfer data.
                 * 
                 * @param[in] txBuffer Transmit buffer.
                 * @param[in] txLen Length of the data that should be transmitted.
                 * @param[in] rxBuffer Receive buffer.
                 * @param[in] rxLen Length of the data that should be received.
                 * @param[in] readAddress Desired address where the device should read from.
                 * 
                 * @return Function returns a boolean value to indicate if the transfer was successful or not.
                 * @retval false Error.
                 * @retval true Success.
                 */
                bool transfer(uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen, uint8_t readAddress) {
                    if( (txLen > 0) && (txBuffer != NULL) ) {
                        uint8_t bytesWritten = 0;

                        for(; bytesWritten < txLen; ++bytesWritten) {
                            spi->transfer(txBuffer[bytesWritten]);
                        }

                        if( bytesWritten != txLen ) {
                            return false;
                        }
                    }

                    if( (rxLen > 0)  && (rxBuffer != NULL) ) {
                        uint16_t bytesRead = 0;
                        spi->transfer(TLX493D_SPI_READ_BIT_ON | readAddress);

                        for(; bytesRead < rxLen; ++bytesRead) {
                            rxBuffer[bytesRead] = spi->transfer(TLX493D_SPI_READ_BIT_ON | readAddress);
                        }

                        if( bytesRead != rxLen ) {
                            return false;
                        }
                    }

                    return true;
                }


                /**
                 * @brief The function `getBus` is used to retrieve a pointer to the wrapper's bus-object.
                 * 
                 * @return A pointer to the current SPI bus-object of the wrapper.
                 */
                SPIClass &getBus() {
                    return *spi;
                }


            private:

                /** SPIClass object. */
                SPIClass *spi;
        };
    }
}

#endif // TLX493D_SPICLASS_WRAPPER_HPP
