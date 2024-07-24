#ifndef TLX493D_SPI_USING_SPICLASS_HPP
#define TLX493D_SPI_USING_SPICLASS_HPP


/** std includes. */
#ifdef __AVR__

    #include <stdbool.h>

#else

    #include <cstdbool>

#endif


/** Arduino includes. */
#include <Arduino.h>

/** project c includes. */
#include "tlx493d_types.h"

/** project cpp includes. */
#include "SPIClassWrapper.hpp"


namespace ifx {
    namespace tlx493d {
        /**
         * @brief The function `initCommunication` is used to initialize the communication interface of the sensor. In this case the SPI interface.
         * The communication interfaces is determined automatically depending on the chosen sensor.
         * 
         * @param[in,out] sensor A pointer to a TLx493D_t struct, which represents the TLx493D sensor.
         * @param[in,out] spi A pointer the used SPIClass instance.
         * @param[in] executeInit Boolean flag which determines whether the initialization is executed or not. The default value is \b false.
         * @param[in] clockFreq Desired clock frequency of the SPI-bus. The default value is \b 200000.
         * @param[in,out] bitOrder Determines the desired bit order of the communication. MSB or LSB first. Default value is \b MSBFIRST.
         * @param[in,out] dataMode Determines the desired data mode for the SPI communication. The default values is \b SPI_MODE2.
         * 
         * @return A boolean value which indicates if the initialization was successful or not.
         * @retval false Error.
         * @retval true Success.
         */
        bool initCommunication(TLx493D_t *sensor, SPIClassWrapper &spi, bool executeInit = false,
                               uint32_t clockFreq = 200000, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE2);
        bool initCommunication(TLx493D_t *sensor, SPIClass &spi, bool executeInit = false,
                               uint32_t clockFreq = 200000, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE2);
    }
}


#endif // TLX493D_SPI_USING_SPICLASS_HPP
