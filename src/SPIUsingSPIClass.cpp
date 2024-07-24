/** std includes. */
#ifdef __AVR__

    #include <stddef.h>
    #include <stdlib.h>

#else

    #include <cstddef>
    #include <cstdlib>

#endif


/** project c includes. */
#include "tlx493d_types.h"


/** project cpp includes. */
#include "types.hpp"
#include "SPIUsingSPIClass.hpp"


namespace ifx {
    namespace tlx493d {
        static uint8_t   spiReadAddress = 0x00;

        static uint32_t  clockFreq = 200000;
        static uint8_t   bitOrder  = MSBFIRST;
        static uint8_t   dataMode  = SPI_MODE2;


        static bool initSPI(TLx493D_t *sensor) {

/** TODO: Fix XMCLib SPISettings incompatibilities ! P3I8 will not work for any other platform other than XMCLib ! */
#ifdef ARDUINO_ARM_XMC      

            sensor->comInterface.comLibObj.spi_obj->spi->init(SPISettings(clockFreq, bitOrder, dataMode));

#endif

            return true;
        }


        static bool deinitSPI(TLx493D_t *sensor) {
            sensor->comInterface.comLibObj.spi_obj->spi->deinit();
            return true;
        }


        static bool transferSPI(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
            if( sensor->boardSupportInterface.boardSupportObj.k2go_obj != NULL ) {
                sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go->enableSelect(true);
            }

            bool b = sensor->comInterface.comLibObj.spi_obj->spi->transfer(txBuffer, txLen, rxBuffer, rxLen, spiReadAddress);

            if( sensor->boardSupportInterface.boardSupportObj.k2go_obj != NULL ) {
                sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go->enableSelect(false);
            }

            return b;
        }


        static void setReadAddressSPI(TLx493D_t *sensor, uint8_t address) {
            (void) sensor;
            
            spiReadAddress = address;
        }


        static TLx493D_ComLibraryFunctions_t  comLibFuncs_spi = {
                                                    .init           = { .spi_init           = initSPI },
                                                    .deinit         = { .spi_deinit         = deinitSPI },
                                                    .transfer       = { .spi_transfer       = transferSPI },
                                                    .setReadAddress = { .spi_setReadAddress = setReadAddressSPI },
                                            };


        bool initCommunication(TLx493D_t *sensor, SPIClassWrapper &spi, bool executeInit,
                               uint32_t pClockFreq, uint8_t pBitOrder, uint8_t pDataMode) {
            sensor->comInterface.comLibObj.spi_obj                = (TLx493D_SPIObject_t *) malloc(sizeof(TLx493D_SPIObject_t));
            sensor->comInterface.comLibObj.spi_obj->spi           = &spi;
            sensor->comInterface.comLibObj.spi_obj->isToBeDeleted = false;

            sensor->comInterface.comLibFuncs                      = &comLibFuncs_spi;

            if( executeInit ) {
                clockFreq = pClockFreq;
                bitOrder  = pBitOrder;
                dataMode  = pDataMode;

                sensor->comInterface.comLibFuncs->init.spi_init(sensor);
            }

            return true;
        }


        bool initCommunication(TLx493D_t *sensor, SPIClass &spi, bool executeInit, uint32_t pClockFreq, uint8_t pBitOrder, uint8_t pDataMode) {
            sensor->comInterface.comLibObj.spi_obj                = (TLx493D_SPIObject_t *) malloc(sizeof(TLx493D_SPIObject_t));
            sensor->comInterface.comLibObj.spi_obj->spi           = new SPIClassWrapper(spi);
            sensor->comInterface.comLibObj.spi_obj->isToBeDeleted = true;

            sensor->comInterface.comLibFuncs                      = &comLibFuncs_spi;

            if( executeInit ) {
                clockFreq = pClockFreq;
                bitOrder  = pBitOrder;
                dataMode  = pDataMode;

                sensor->comInterface.comLibFuncs->init.spi_init(sensor);
            }

            return true;
        }
    }
}
