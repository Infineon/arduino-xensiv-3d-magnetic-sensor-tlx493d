#ifndef TLX493D_ARDUINO_BASETYPES_H
#define TLX493D_ARDUINO_BASETYPES_H


/** project cpp includes. */
#include "Kit2GoBoardSupport.hpp"
#include "SPIClassWrapper.hpp"
#include "TwoWireWrapper.hpp"


extern "C" {

    /**
     * @brief Structure to hold the I2C-object, needed for communication.
     */
    using TLx493D_I2CObject_t = struct TLx493D_I2CObject {
        ifx::tlx493d::TwoWireWrapper *wire;
        bool                          isToBeDeleted;
    };


    /**
     * @brief Structure to hold the SPI-object, needed for communication.
     */
    using TLx493D_SPIObject_t = struct TLx493D_SPIObject {
        ifx::tlx493d::SPIClassWrapper *spi;
        bool                           isToBeDeleted;
    };


    /**
     * @brief Structure to hold the Kit2GoBoardSupport-Object.
    */
    using TLx493D_Kit2GoBoardSupportObject_t = struct TLx493D_Kit2GoBoardSupportObject {
        ifx::tlx493d::Kit2GoBoardSupport  *k2go;
    };

}


#endif // TLX493D_ARDUINO_BASETYPES_H
