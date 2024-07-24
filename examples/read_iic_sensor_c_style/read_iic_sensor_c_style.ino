/** Project CPP includes. */
#include "TLx493D_inc.hpp"


/** Definition of the power pin. */
const uint8_t POWER_PIN = 15; // XMC1100 : LED2


/** Declaration of the sensor. */
TLx493D_t dut;

uint8_t count = 0;
TLx493D_SupportedSensorType_t sensorType = TLx493D_W2B6_e;


void setup() {
    Serial.begin(115200);
    delay(3000);

    Serial.println(true ==  tlx493d_init(&dut, sensorType) ? "" : "tlx493d_init error");

    /** Setting the defined power up pin as output and set to VDD / high value. */
    pinMode(POWER_PIN, OUTPUT);

    digitalWrite(POWER_PIN, LOW);
    delayMicroseconds(250000UL);

    digitalWrite(POWER_PIN, HIGH);
    delayMicroseconds(0);

    /** Initialization of the sensor and the communication interface.
     *  After that the default configuration of the sensor is set. This means
     *  1-Byte read mode and interrupt disabled.
     */
    Serial.println(true ==  ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e, true) ? "" : "initCommunication error");
    Serial.println(true ==  tlx493d_setDefaultConfig(&dut) ? "" : "tlx493d_setDefaultConfig error");

    Serial.println("setup done.");
}

/** In the loop we continuously reading the temperature value as well as the
 *  magnetic values in X, Y, Z-direction of the sensor and printing them to
 *  the serial monitor.
 */
void loop() {
    double t, x, y, z;

    tlx493d_getMagneticFieldAndTemperature(&dut, &x, &y, &z, &t);
    tlx493d_printRegisters(&dut);

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

    delay(1000);

    Serial.print("count : ");
    Serial.println(count);

    if( ++count == 5 ) {
        Serial.println("\nBefore reset -------------------------------------------------------------------------------------------------------");

        // If reset fails for A1B6 and W2BW : check drive strength of power pin !
        ifx::tlx493d::deinitCommunication(&dut, sensorType != TLx493D_A1B6_e);
        dut.functions->deinit(&dut);

        digitalWrite(POWER_PIN, LOW);
        delayMicroseconds(250000UL);

        tlx493d_init(&dut, sensorType);

        digitalWrite(POWER_PIN, HIGH);
        delayMicroseconds(0);

        ifx::tlx493d::initCommunication(&dut, Wire, TLx493D_IIC_ADDR_A0_e, true);
        tlx493d_setDefaultConfig(&dut);

        Serial.println("\nAfter reset -------------------------------------------------------------------------------------------------------");
        count = 0;
    }
}
