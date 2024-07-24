/** std includes. */
#ifdef __AVR__

    #include <stddef.h>
    #include <stdlib.h>

#else

    // #include <malloc.h>
    #include <cstddef>
    #include <cstdlib>

#endif


/** project c includes. */
#include "tlx493d_types.h"

/** project cpp includes. */
#include "types.hpp"
#include "IICUsingTwoWire.hpp"
#include "Logger.h"


namespace ifx {
    namespace tlx493d {
        static bool initIIC(TLx493D_t *sensor) {
            sensor->comInterface.comLibObj.iic_obj->wire->init();
            return true;

        }


        static bool deinitIIC(TLx493D_t *sensor) {
            sensor->comInterface.comLibObj.iic_obj->wire->deinit();
            return true;
        }


        static bool transferIIC(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
            return sensor->comInterface.comLibObj.iic_obj->wire->transfer(sensor->comInterface.comLibParams.iic_params.address >> 1, txBuffer, txLen, rxBuffer, rxLen);
        }


        static void setReadAddressIIC(TLx493D_t *sensor, uint8_t address) {
            (void) sensor;
            (void) address;
            logWarn("Function 'setReadAddressIIC' not supported !");
        }


        static TLx493D_ComLibraryFunctions_t  comLibFuncs_iic = {
                                                    .init           = { .iic_init           = initIIC },
                                                    .deinit         = { .iic_deinit         = deinitIIC },
                                                    .transfer       = { .iic_transfer       = transferIIC },
                                                    .setReadAddress = { .iic_setReadAddress = setReadAddressIIC },
                                            };


        bool initCommunication(TLx493D_t *sensor, TwoWireWrapper &tw, TLx493D_IICAddressType_t iicAdr, bool executeInit) {
            sensor->comInterface.comLibObj.iic_obj                = (TLx493D_I2CObject_t *) malloc(sizeof(TLx493D_I2CObject_t));
            sensor->comInterface.comLibObj.iic_obj->wire          = &tw;
            sensor->comInterface.comLibObj.iic_obj->isToBeDeleted = false;

            sensor->comInterface.comLibFuncs                      = &comLibFuncs_iic;
            sensor->comInterface.comLibParams.iic_params.address  = sensor->functions->selectIICAddress(sensor, iicAdr);

            if( executeInit ) {
                sensor->comInterface.comLibFuncs->init.iic_init(sensor);
            }

            return true;
        }


        bool initCommunication(TLx493D_t *sensor, TwoWire &tw, TLx493D_IICAddressType_t iicAdr, bool executeInit) {
            sensor->comInterface.comLibObj.iic_obj                = (TLx493D_I2CObject_t *) malloc(sizeof(TLx493D_I2CObject_t));
            sensor->comInterface.comLibObj.iic_obj->wire          = new TwoWireWrapper(tw);
            sensor->comInterface.comLibObj.iic_obj->isToBeDeleted = true;

            sensor->comInterface.comLibFuncs                      = &comLibFuncs_iic;
            sensor->comInterface.comLibParams.iic_params.address  = sensor->functions->selectIICAddress(sensor, iicAdr);

            if( executeInit ) {
                sensor->comInterface.comLibFuncs->init.iic_init(sensor);
            }

            return true;
        }
    }
}
