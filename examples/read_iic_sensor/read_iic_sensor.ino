/** Project CPP includes. */
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/* Definition of the power pin and sensor objects for Kit2Go XMC1100 boards. */
const uint8_t POWER_PIN = 15; // XMC1100 : LED2

// TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_A2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
TLx493D_P2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);


/** Definition of the power pin and sensor objects for S2Go with XMC4700 Relax Lite board. */
// const uint8_t POWER_PIN = 8; // XMC : P1.10

// TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_A2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_W2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);

// TLx493D_P3B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
// TLx493D_P3B6 dut(Wire, TLx493D_IIC_ADDR_A1_e);


/** Definition of the power pin and sensor objects for Arduino Uno boards */
/** Care must be taken to level shift down to 3.3V as the sensor boards expect only 3.3V ! */
/** Therefore disabled for here. */
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
    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
    dut.begin();

    Serial.print("setup done.\n");
}


/** In the loop we continuously reading the temperature value as well as the
 *  magnetic values in X, Y, Z-direction of the sensor and printing them to
 *  the serial monitor
 */
void loop() {
    double t, x, y, z;

    dut.setSensitivity(TLx493D_FULL_RANGE_e);
    dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
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
    dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
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

    Serial.print("count : ");
    Serial.println(count);

    if( ++count == 4 ) {
        Serial.println("\nBefore reset -------------------------------------------------------------------------------------------------------");

        /** Reset does not work for W2BW : either drive strength too low or delay to stabilize critical. */
        dut.reset(true);

        Serial.println("\nAfter reset -------------------------------------------------------------------------------------------------------");
        count = 0;
    }
}
