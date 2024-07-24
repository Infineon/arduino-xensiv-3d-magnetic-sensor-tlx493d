/** Project CPP includes. */ 
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Declaration of three sensor objects with the same default address (A0).
 * 
 *  ATTENTION
 *  All Kit2Go/S2Go boards have pull-up resistors attached to the IIC SCL and SDA lines.
 *  In case of sensors dut2 and dut3 these resistors actually pull-down the SCL/SDA lines while
 *  the sensors are NOT powered. Therefore the pull-up resistors of dut2 and dut3 have to be removed
 *  for this example to work. Otherwise not even dut1 can be initialized properly. Alternatively,
 *  pull-up resistors for all devices are removed and external pull-ups are added to SCL/SDA.
 */
TLx493D_W2B6 dut1(Wire, TLx493D_IIC_ADDR_A0_e);
TLx493D_W2B6 dut2(Wire, TLx493D_IIC_ADDR_A0_e);
TLx493D_W2B6 dut3(Wire, TLx493D_IIC_ADDR_A0_e);


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** In this example we're using the XMC4700-Relax-Kit. 
     *  Here we're using three GPIOs to power up the sensors, one
     *  after the other. This is done by defining the pins with the
     *  Board Support Class and its functions. The power up pins are
     *  enabled during the begin() call to the sensor object as done below. 
    */
    dut1.setPowerPin(8, OUTPUT, INPUT, HIGH, LOW, 0, 250000);  // XMC4700 Relax P1.10
    dut2.setPowerPin(9, OUTPUT, INPUT, HIGH, LOW, 0, 250000);  // XMC4700 Relax XMC P1.11
    dut3.setPowerPin(10, OUTPUT, INPUT, HIGH, LOW, 0, 250000); // XMC4700 Relax XMC P3.10

    /** Here we're enabling one sensor after another. This procedure 
     *  is necessary in order to avoid an interrupt to occur on the SCL line before
     *  interrupts are disabled in the sensor's begin() method. Additionally, the IIC address
     *  is changed from the default A0 to a distinct one for each sensor.
     */
    dut1.begin(true, false, false, true);
    dut1.setIICAddress(TLx493D_IIC_ADDR_A2_e);
    dut1.printRegisters();

    dut2.begin();
    dut2.setIICAddress(TLx493D_IIC_ADDR_A1_e);
    dut2.printRegisters();

    dut3.begin();
    dut3.printRegisters();

    Serial.println("setup done.\n");
}

/** In the loop we're reading out the temperature value as well as the magnetic values in X, Y, Z-direction 
 *  of all three sensors. After that they're all printed to the serial output.
 */
void loop() {
    double temp1 = 0.0, temp2 = 0.0, temp3 = 0.0;
    double valX1 = 0, valY1 = 0, valZ1 = 0, valX2 = 0, valY2 = 0, valZ2 = 0, valX3 = 0, valY3 = 0, valZ3 = 0;

    dut1.getMagneticFieldAndTemperature(&valX1, &valY1, &valZ1, &temp1);
    dut1.printRegisters();
    dut2.getMagneticFieldAndTemperature(&valX2, &valY2, &valZ2, &temp2);
    dut2.printRegisters();
    dut3.getMagneticFieldAndTemperature(&valX3, &valY3, &valZ3, &temp3);
    dut3.printRegisters();

    Serial.println("========================================");
    Serial.print("Temperature of Sensor 1:\t");Serial.print(temp1);Serial.println(" °C");
    Serial.print("Magnetic X-Value of Sensor 1:\t");Serial.print(valX1);Serial.println(" mT");
    Serial.print("Magnetic Y-Value of Sensor 1:\t");Serial.print(valY1);Serial.println(" mT");
    Serial.print("Magnetic Z-Value of Sensor 1:\t");Serial.print(valZ1);Serial.println(" mT");
    Serial.println("----------------------------------------");
    Serial.print("Temperature of Sensor 2:\t");Serial.print(temp2);Serial.println(" °C");
    Serial.print("Magnetic X-Value of Sensor 2:\t");Serial.print(valX2);Serial.println(" mT");
    Serial.print("Magnetic Y-Value of Sensor 2:\t");Serial.print(valY2);Serial.println(" mT");
    Serial.print("Magnetic Z-Value of Sensor 2:\t");Serial.print(valZ2);Serial.println(" mT");
    Serial.println("----------------------------------------");
    Serial.print("Temperature of Sensor 3:\t");Serial.print(temp3);Serial.println(" °C");
    Serial.print("Magnetic X-Value of Sensor 3:\t");Serial.print(valX3);Serial.println(" mT");
    Serial.print("Magnetic Y-Value of Sensor 3:\t");Serial.print(valY3);Serial.println(" mT");
    Serial.print("Magnetic Z-Value of Sensor 3:\t");Serial.print(valZ3);Serial.println(" mT");
    Serial.println("========================================\n\n");

    delay(2000);
}
