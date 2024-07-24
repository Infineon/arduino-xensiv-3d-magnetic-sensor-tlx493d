#ifndef TLX493D_ARDUINO_TYPES_H
#define TLX493D_ARDUINO_TYPES_H


/** project cpp includes. */
#include "baseTypes.hpp"
#include "TLx493D.hpp"


namespace ifx {
    namespace tlx493d {
        using TLx493D_A1B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A1B6_e>;
        using TLx493D_A2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A2B6_e>;
        using TLx493D_A2BW = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_A2BW_e>;
        using TLx493D_P2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P2B6_e>;
        using TLx493D_W2B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2B6_e>;
        using TLx493D_W2BW = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_W2BW_e>;
        using TLx493D_P3B6 = TLx493D<Kit2GoBoardSupport, TwoWireWrapper, TLx493D_P3B6_e>;

        using TLx493D_P3I8 = TLx493D<Kit2GoBoardSupport, SPIClassWrapper, TLx493D_P3I8_e>;
    }
}

#endif // TLX493D_ARDUINO_TYPES_H
