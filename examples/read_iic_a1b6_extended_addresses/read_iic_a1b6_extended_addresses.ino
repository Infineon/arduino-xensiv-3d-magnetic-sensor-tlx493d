/** Project CPP includes. */ 
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Use XMC4700 Relax Kit for this test and connect to power and I2C SDA, respectively. */
// const uint8_t POWER_PIN       = 8; // XMC4700 : P1.10
// const uint8_t SDA_ADDRESS_PIN = 7; // XMC4700 : P1.9

/** Use XMC1100 Boot Kit for this test and connect to power and I2C SDA, respectively. */
const uint8_t POWER_PIN       = 5; // XMC1100
const uint8_t SDA_ADDRESS_PIN = 4; // XMC1100


/** Device at address 0x3E. */
TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A4_e);


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** Explicit power pin needed to power up board after the addressPin is pulled down.
     *  The value of 140 us has been determined for the XMC1100 board by measuring the
     *  delay between the rising edge of the power signal and the rising edge of the 
     *  pulled-down SDA pin. The data sheet specifies a delay of 200us between the 2 edges.
     *  These 200us are the combined delay of the delay after enable for the power pin (here 140us)
     *  plus the program execution delay. Once the address pin SDA has been enabled it is
     *  set as INPUT thereby detaching it from the SDA output signal.  
     */
    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 140, 250000);

    /** Set pin used to drive SDA/ADDR pin before power up.
      * This pin is then isolated from the I2C bus by switching it high-Z before I2C init. */
    dut.setAddressPin(SDA_ADDRESS_PIN, OUTPUT, INPUT, LOW, HIGH, 0, 0);
    
    /** Set the sensor constructor to activate extended address switching pin. */
    dut.begin(true, false, true, true);
    dut.printRegisters();

    /* Options to set the other remaining addresses when SDA low at power-up. */
    // dut.setIICAddress(TLx493D_IIC_ADDR_A5_e); // 0x36
    // dut.setIICAddress(TLx493D_IIC_ADDR_A6_e); // 0x1E
    dut.setIICAddress(TLx493D_IIC_ADDR_A7_e); // 0x16
  
    Serial.print("setup done.\n");
}


/** In the loop we're reading out the temperature value as well as the magnetic values in X, Y, Z-direction 
 *  of the sensors. After that they're all printed to the serial output.
 */
void loop() {
    double temp = 0.0;
    double valX = 0, valY = 0, valZ = 0;

    Serial.print(true == dut.getTemperature(&temp) ? "getTemperature ok\n" : "getTemperature error\n");

    Serial.print("Temperature is: ");
    Serial.print(temp);
    Serial.println("°C");

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
}
