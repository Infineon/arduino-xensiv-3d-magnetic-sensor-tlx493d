/** std includes. */
#ifdef __AVR__

    #include <stdbool.h>

#else

    #include <cstdbool>

#endif


/** project cpp includes. */
#include "CommunicationInterface.h"

/** project c includes. */
#include "tlx493d_types.h"


extern "C" bool tlx493d_transfer(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
    return sensor->comIFType == TLx493D_I2C_e ? sensor->comInterface.comLibFuncs->transfer.iic_transfer(sensor, txBuffer, txLen, rxBuffer, rxLen)
                                              : (sensor->comIFType == TLx493D_SPI_e ? sensor->comInterface.comLibFuncs->transfer.spi_transfer(sensor, txBuffer, txLen, rxBuffer, rxLen)
                                                                                    : false);
}


extern "C" void tlx493d_setReadAddress(TLx493D_t *sensor, uint8_t address) {
    if( sensor->comIFType == TLx493D_I2C_e ) {
        sensor->comInterface.comLibFuncs->setReadAddress.iic_setReadAddress(sensor, address);
    }
    else if( sensor->comIFType == TLx493D_SPI_e ) {
        sensor->comInterface.comLibFuncs->setReadAddress.spi_setReadAddress(sensor, address);
    }
}


namespace ifx {
    namespace tlx493d {
        void deinitCommunication(TLx493D_t *sensor, bool executeDeinit) {
            if( sensor->comIFType == TLx493D_I2C_e ) {
                if( sensor->comInterface.comLibFuncs != NULL ) {
                    if( executeDeinit ) {
                        sensor->comInterface.comLibFuncs->deinit.iic_deinit(sensor);
                    }
                }

                if( sensor->comInterface.comLibObj.iic_obj != NULL ) {
                    if( sensor->comInterface.comLibObj.iic_obj->isToBeDeleted ) {
                        delete sensor->comInterface.comLibObj.iic_obj->wire;
                    }

                    free(sensor->comInterface.comLibObj.iic_obj);
                    sensor->comInterface.comLibObj.iic_obj = NULL;
                }
            }
            else if( sensor->comIFType == TLx493D_SPI_e ) {
                if( sensor->comInterface.comLibFuncs != NULL ) {
                    if( executeDeinit ) {
                        sensor->comInterface.comLibFuncs->deinit.spi_deinit(sensor);
                    }
                }

                if( sensor->comInterface.comLibObj.iic_obj != NULL ) {

                    if( sensor->comInterface.comLibObj.iic_obj->isToBeDeleted ) {
                        delete sensor->comInterface.comLibObj.spi_obj->spi;
                    }

                    free(sensor->comInterface.comLibObj.spi_obj);
                    sensor->comInterface.comLibObj.spi_obj = NULL;
                }
            }

            sensor->comInterface.comLibFuncs = NULL;
        }
    }
}