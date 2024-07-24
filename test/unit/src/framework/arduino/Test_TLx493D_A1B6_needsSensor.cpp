#include "Test_includes.hpp"


const static uint8_t POWER_PIN = 15; // XMC1100 : LED2
// const uint8_t POWER_PIN   = 8; // P1.10
const uint8_t ADDRESS_PIN = 7;

static ifx::tlx493d::Kit2GoBoardSupport bsc;


extern "C" {
    // project includes
    #include "Test_TLx493D_A1B6_needsSensor.h"
    #include "Test_tlx493d_commonFunctions_needsSensor.h"


    // Method invoked by Unity before a test suite is run 
    void TLx493D_A1B6_needsSensor_suiteSetup() {
        (void) TLx493D_A1B6_init(&dut);

        bsc.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 50, 250000);
        ifx::tlx493d::initBoardSupport(&dut, bsc);
        bsc.init();

        ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e, true);
        dut.functions->setDefaultConfig(&dut);
    }
    
    
    // Method invoked by Unity after a test suite is run 
    void TLx493D_A1B6_needsSensor_suiteTearDown() {
        ifx::tlx493d::deinitCommunication(&dut, false);
        bsc.deinit();
        dut.functions->deinit(&dut);
    }


    // Method invoked by Unity before a test suite is run 
    void TLx493D_A1B6_atReset_suiteSetup() {
        (void) TLx493D_A1B6_init(&dut);

        bsc.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 50, 250000);
        ifx::tlx493d::initBoardSupport(&dut, bsc);
        bsc.init();

        ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e, true);
    }
    
    
    // Method invoked by Unity after a test suite is run 
    void TLx493D_A1B6_atReset_suiteTearDown() {
        ifx::tlx493d::deinitCommunication(&dut, false);
        bsc.deinit();
        dut.functions->deinit(&dut);
    }


    // Method invoked by Unity before a test suite is run 
    void TLx493D_A1B6_extendedAddresses_suiteSetup() {
        (void) TLx493D_A1B6_init(&dut);

        logPrint("\nbsc object used to power on board; check if POWER PIN connected!\ncheck if ADDR pin is connected!\n");
        // power up the board using bsc
        bsc.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 50, 250000);
        bsc.setAddressPin(ADDRESS_PIN, OUTPUT, INPUT, HIGH, LOW, 1000, 1000);
        ifx::tlx493d::initBoardSupport(&dut, bsc);
        bsc.init(true, false, true);

        ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A4_e, true);
        dut.functions->setDefaultConfig(&dut);
    }


    // Method invoked by Unity after a test suite is run 
    void TLx493D_A1B6_extendedAddresses_suiteTearDown() {
        ifx::tlx493d::deinitCommunication(&dut, false);
        bsc.deinit();
        dut.functions->deinit(&dut);
    }
}