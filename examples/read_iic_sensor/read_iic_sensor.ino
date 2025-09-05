/** Project CPP includes. */
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


#if BOARD_TYPE == "XMC1100_S2GO"
    const uint8_t POWER_PIN = 15; // XMC1100 : LED2
#elif BOARD_TYPE == "XMC4700_RELAX_KIT"
    const uint8_t POWER_PIN = 8; // XMC : P1.10
#endif


/* Definition of the power pin and sensor objects for Kit2Go XMC1100 boards. */
// const uint8_t POWER_PIN = 15; // XMC1100 : LED2

// TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_A2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_P2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

SENSOR_TYPE dut(Wire, TLx493D_IIC_ADDR_A0_e);


/** Definition of the power pin and sensor objects for S2Go with XMC4700 Relax Lite board. */
// const uint8_t POWER_PIN = 8; // XMC : P1.10

// TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_A2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);


/** P3XX evaluation board */
// const uint8_t POWER_PIN = 8;
// TLx493D_P3B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);


/** Definition of the power pin and sensor objects for Arduino Uno boards */
/** Care must be taken to level shift down to 3.3V as the sensor boards expect only 3.3V ! */
/** Therefore disabled here. */
// const uint8_t POWER_PIN = 7;

// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);


/** Definition of a counter variable. */
uint8_t count = 0;


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** Definition of the power pin to power up the sensor. */
    /** Set delay after power-on to 50 for A1B6 Kit2Go sensor. */
    /** All other Kit2Go boards */
    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);

    // /** P3XX evaluation board */
    // dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, LOW, HIGH, 1000, 250000);

    dut.begin();

    // This will be the token used as start token in this setup (see project.yml)
    Serial.print("setup done.\n");
}


/** In the loop we continuously reading the temperature value as well as the
 *  magnetic values in X, Y, Z-direction of the sensor and printing them to
 *  the serial monitor
 */
void loop() {
    double t, x, y, z;

    // Messages of these 3 types are detected and reported: 
    // Serial.println("WARNING: Dummy warning 1.\n");
    // Serial.println("ERROR: Dummy error 1.\n");
    // Serial.println("FATAL: Dummy fatal 1.\n");

    dut.setSensitivity(TLx493D_FULL_RANGE_e);
    bool result = dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
    // Serial.print(true == dut.getMagneticFieldAndTemperature(&x, &y, &z, &t) ? "getMagneticFieldAndTemperature ok\n" : "getMagneticFieldAndTemperature error\n");

    if( !result ) {
        Serial.println("FATAL: An error occurred, could not get magnetic field values !\n");
    }

    dut.printRegisters();

    Serial.print("\nTemperature is: ");
    Serial.print(t);
    Serial.println("°C");

    Serial.print("Value X is: ");
    Serial.print(x);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(y);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(z);
    Serial.println(" mT");

    dut.setSensitivity(TLx493D_SHORT_RANGE_e);

    result = dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
    
    if( !result ) {
        Serial.println("FATAL: An error occurred, could not get magnetic field values !\n");
    }

    dut.printRegisters();

    Serial.print("\nTemperature is: ");
    Serial.print(t);
    Serial.println("°C");

    Serial.print("Value X is: ");
    Serial.print(x);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(y);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(z);
    Serial.println(" mT");
    Serial.print("\n\n\n\n");

    delay(1000);

    Serial.print("count = ");
    Serial.println(count);

    if( ++count == 4 ) {
        Serial.println("\nBefore reset -------------------------------------------------------------------------------------------------------");

        /** Reset does not work for W2BW : either drive strength too low or delay to stabilize critical. */
        dut.reset(true, dut.getSensorType() != TLx493D_A1B6_e);

        Serial.println("\nAfter reset -------------------------------------------------------------------------------------------------------");
        count = 0;
    }

    // This will be the token used as start token in this setup (see project.yml).
    // Serial.println("loop done.\n");
}
