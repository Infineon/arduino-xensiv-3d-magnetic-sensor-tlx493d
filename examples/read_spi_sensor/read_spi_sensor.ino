/** Project CPP includes. */
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Definition of the power and chip select pin. */
/** P3XX evaluation board */
const uint8_t POWER_PIN       = 4; // XMC1100_XMC2GO
const uint8_t CHIP_SELECT_PIN = 3;

/** Declaration of the sensor object. */
TLx493D_P3I8 dut(SPI);

/** Definition of a counter. */
uint8_t count = 0;


void setup() {
    Serial.begin(115200);

    while (!Serial) ;

    delay(3000);

    /** Setting the chip select pin for the SPI board using the functions of the Board Support Class.
     * Power supply has to be switched on through transistor, therefore inverse logic.
     */
    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, LOW, HIGH, 1000, 250000);
    dut.setSelectPin(CHIP_SELECT_PIN, OUTPUT, INPUT, LOW, HIGH, 0, 0, 0, 0);
    dut.begin(true, true);

    Serial.print("setup done.\n");
}

/** In the loop we're reading out the temperature value (in °C) as well as the magnetic fields values in X, Y, Z-direction (in mT).
 *  We're also reading out the raw temperature value (in LSB).
 */
void loop() {
    double temp = 0.0;
    double valX = 0, valY = 0, valZ = 0;
    int16_t tempRaw = 0;

    dut.printRegisters();
    Serial.print("\n");

    /** Note that you don't have to toggle any chip select signal, this is done in the background within the transfer function. */
    Serial.print(true == dut.getTemperature(&temp) ? "getTemperature ok\n" : "getTemperature error\n");

    Serial.print("Temperature is: ");
    Serial.print(temp);
    Serial.println(" °C");

    dut.getRawTemperature(&tempRaw);

    Serial.print("Raw temperature is: ");
    Serial.print(tempRaw);
    Serial.println(" LSB");

    Serial.print(true == dut.getMagneticFieldAndTemperature(&valX, &valY, &valZ, &temp) ? "getMagneticFieldAndTemperature ok\n" : "getMagneticFieldAndTemperature error\n");

    Serial.print("Value X is: ");
    Serial.print(valX);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(valY);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(valZ);
    Serial.println(" mT");

    dut.printRegisters();
    Serial.print("\n");

    delay(1000);

    Serial.print("count : ");
    Serial.println(count);

    if( ++count == 10 ) {
        Serial.println("Before reset -------------------------------------------------------------------------------------------------------");

        /* Use reset to do a full power down reset or softwareReset to reset using register settings. **/
        dut.reset();
        // dut.softwareReset();

        Serial.println("After reset -------------------------------------------------------------------------------------------------------");
        count = 0;
    }
}
