/** Project CPP includes. */ 
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Declaration of three different sensor objects, all sensors of the second generation. 
 * 
 *  ATTENTION
 *  All Kit2Go/S2Go boards have pull-up resistors attached to the IIC SCL and SDA lines.
 *  In case of sensors dut2 and dut3 these resistors actually pull-down the SCL/SDA lines while
 *  the sensors are NOT powered. Therefore the pull-up resistors of dut2 and dut3 have to be removed
 *  for this example to work. Otherwise not even dut1 can be initialized properly. Alternatively,
 *  pull-up resistors for all devices are removed and external pull-ups are added to SCL/SDA.
 *  This will have the additional benefit that the order of powering up the devices becomes irrelevant.
*/

TLx493D_P2B6 dut1(Wire, TLx493D_IIC_ADDR_A0_e);
TLx493D_W2BW dut2(Wire, TLx493D_IIC_ADDR_A0_e);
TLx493D_W2B6 dut3(Wire, TLx493D_IIC_ADDR_A0_e);


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** The second generation is critical with respect to interrupts, so you have
     *  to make sure to initialize these sensors first by powering them up one by one
     *  and disabling interrupts in the sensor's begin() method.
     *  Otherwise an interrupt may be triggered on the IIC SCL line stalling the sensor's
     *  communication interface. 
     */
    dut1.setPowerPin(8, OUTPUT, INPUT, HIGH, LOW, 0, 250000);  // XMC4700 Relax P1.10
    dut2.setPowerPin(9, OUTPUT, INPUT, HIGH, LOW, 0, 250000);  // XMC4700 Relax XMC P1.11
    dut3.setPowerPin(10, OUTPUT, INPUT, HIGH, LOW, 0, 250000); // XMC4700 Relax XMC P3.10

    /** Initialize sensor 1. */
    dut1.begin();
    dut1.setIICAddress(TLx493D_IIC_ADDR_A2_e);

    dut2.begin(true, false, false, false);
    dut2.setIICAddress(TLx493D_IIC_ADDR_A1_e);

    dut3.begin(true, false, false, false);

    Serial.print("setup done.\n");
}

/** In the loop we're reading out the temperature values as well as the magnetic values in X, Y, Z-direction 
 *  of all three sensors. After that they're all printed to the serial output.
 */
void loop() {
    double temp1 = 0.0, temp2 = 0.0, temp3 = 0.0;
    double valX1 = 0, valY1 = 0, valZ1 = 0, valX2 = 0, valY2 = 0, valZ2 = 0, valX3 = 0, valY3 = 0, valZ3 = 0;

    dut1.getTemperature(&temp1); 
    dut2.getTemperature(&temp2); 
    dut3.getTemperature(&temp3); 

    dut1.getMagneticField(&valX1, &valY1, &valZ1);
    dut2.getMagneticField(&valX2, &valY2, &valZ2);
    dut3.getMagneticField(&valX3, &valY3, &valZ3);

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
