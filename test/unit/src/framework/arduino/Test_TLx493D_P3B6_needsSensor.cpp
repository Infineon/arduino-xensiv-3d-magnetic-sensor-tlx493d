// test includes
#include "Test_includes.hpp"


// const static uint8_t POWER_PIN = 15; // XMC1100 : LED2
const static uint8_t POWER_PIN = 8; // P1.10

static ifx::tlx493d::Kit2GoBoardSupport bsc;


extern "C" {
    // project includes
    #include "Test_TLx493D_P3B6_needsSensor.h"
    #include "Test_tlx493d_commonFunctions_needsSensor.h"


    // Method invoked by Unity before a test suite is run 
    void TLx493D_P3B6_needsSensor_suiteSetup() {
        // deinit in TEAR_DOWN will cut communication link, so if deinit is called communication must be reinitialized !
        (void) TLx493D_P3B6_init(&dut);

        bsc.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
        ifx::tlx493d::initBoardSupport(&dut, bsc);
        bsc.init();

        // ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e, true);
        ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A1_e, true);

        dut.functions->setDefaultConfig(&dut);
    }
    
    
    // Method invoked by Unity after a test suite is run 
    void TLx493D_P3B6_needsSensor_suiteTearDown() {
        ifx::tlx493d::deinitCommunication(&dut, true);
        bsc.deinit();

        // If deinitializing here make sure to reinit in 'TEST_SETUP' or communication will be lost !
        dut.functions->deinit(&dut);
    }
}
