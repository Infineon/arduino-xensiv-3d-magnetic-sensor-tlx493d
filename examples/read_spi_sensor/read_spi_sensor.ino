/** Project CPP includes. */
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Definition of the power and chip select pin. */
const uint8_t CHIP_SELECT_PIN = 3;

/** Declaration of the sensor object. */
TLx493D_P3I8 dut(SPI);

/** Definition of a counter. */
uint8_t count = 0;


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** Setting the chip select pin for the SPI board using the functions of the Board Support Class.
     * Power supply is constantly on and cannot be changed for the current experimental board.
     */
    dut.setSelectPin(CHIP_SELECT_PIN, OUTPUT, INPUT, LOW, HIGH, 50, 50);
    dut.begin();

    Serial.print("setup done.\n");
}

/** In the loop we're reading out the temperature value (in °C) as well as the magnetic fields values in X, Y, Z-direction (in mT).
 *  We're also reading out the raw temperature value (in LSB).
 */
void loop() {
    double temp = 0.0;
    double valX = 0, valY = 0, valZ = 0;
    int16_t tempRaw = 0;

    /** Note that you don't have to toggle any chip select signal, this is done in the background within the transfer function. */
    Serial.print(true == dut.getTemperature(&temp) ? "getTemperature ok\n" : "getTemperature error\n");

    Serial.print("Temperature is: ");
    Serial.print(temp);
    Serial.println(" °C");

    dut.getRawTemperature(&tempRaw);

    Serial.print("Raw temperature is: ");
    Serial.print(tempRaw);
    Serial.println(" LSB");

    Serial.print(true == dut.getMagneticField(&valX, &valY, &valZ) ? "getMagneticField ok\n" : "getMagneticField error\n");

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

        /* The current experimental board does not support power down as the chip VDD is hard wired ! Therefore either use the software reset
         * directly or use dut.reset() to execute a software reset. **/
        dut.reset();
        // dut.softwareReset();

        Serial.println("After reset -------------------------------------------------------------------------------------------------------");
        count = 0;
    }
}
