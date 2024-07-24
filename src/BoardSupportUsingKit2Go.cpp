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
#include "BoardSupportUsingKit2Go.hpp"


namespace ifx {
    namespace tlx493d {
        bool initBoardSupport(TLx493D_t *sensor, Kit2GoBoardSupport &bsc) {
            sensor->boardSupportInterface.boardSupportObj.k2go_obj       = (TLx493D_Kit2GoBoardSupportObject_t *) malloc(sizeof(TLx493D_Kit2GoBoardSupportObject_t));
            sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go = &bsc;
            return true;
        }
    }
}