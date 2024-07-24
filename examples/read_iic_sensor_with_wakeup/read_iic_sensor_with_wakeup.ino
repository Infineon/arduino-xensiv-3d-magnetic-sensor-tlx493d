/** Project CPP includes. */
#include "TLx493D_inc.hpp"


using namespace ifx::tlx493d;


/** Definition of the upper and lower thresholds in X, Y, Z-direction.
 *  These thresholds define under which conditions the sensor wakes up and triggers his interrupt.
 */
const int16_t THRESHOLD = 200;

const int16_t LOWER_THRESHOLD_X = -THRESHOLD;
const int16_t LOWER_THRESHOLD_Y = -THRESHOLD;
const int16_t LOWER_THRESHOLD_Z = -THRESHOLD;

const int16_t UPPER_THRESHOLD_X = THRESHOLD;
const int16_t UPPER_THRESHOLD_Y = THRESHOLD;
const int16_t UPPER_THRESHOLD_Z = THRESHOLD;


/** Definition of the interrupt pin, which will detected the triggered interrupt.
 *  Please be aware that you have to change the pin according to your setup.
 *  Here a XCM1100-XMC2GO is used as microcontroller.
 */
// const uint8_t INTERRUPT_PIN = 9;


/** XMC4700-Relax-Kit */
const uint8_t INTERRUPT_PIN = 2;


/** Declaration of the sensor object. */
TLx493D_W2BW dut(Wire, TLx493D_IIC_ADDR_A0_e);

/** Definition of an interrupt flag. */
bool intTriggered = false;


void setup() {
    Serial.begin(115200);
    delay(3000);

    /** Definition of the interrupt pin and attaching of a callback-function to it. 
     *  In the attachInterrupt function we can also define when the service routine should
     *  be triggered. In our case on a falling edge.  
     */
    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), wakeUp_ISR, FALLING);

    dut.begin();

    /** Here we're setting the thresholds for all three directions of the sensor.
     *  After this we enable the wake up mode as well as the interrupt mode.
     *  Both is necessary in order to enable the wake up feature of the sensor.
     * 
     *  The datasheet also recommends to disable the interrupt after it is triggered.
     *  The reason for that is that the sensor continues to trigger the interrupt
     *  as long as one of the thresholds is exceeded.
     */
    dut.setWakeUpThresholdsAsInteger(LOWER_THRESHOLD_X, UPPER_THRESHOLD_X, LOWER_THRESHOLD_Y, UPPER_THRESHOLD_Y, LOWER_THRESHOLD_Z, UPPER_THRESHOLD_Z);
    dut.enableWakeUpMode();
    dut.enableInterrupt();
    
    /** Here we are checking if the wake up is set correctly.
     *  This can be done due to an internal flag in the register, which is
     *  representing the status of the wake up.
     */
    Serial.print("isWakeUpEnabled : ");
    Serial.println(dut.isWakeUpEnabled() ? "enabled" : "not enabled");
    Serial.print("setup done.\n");
}

/** The code in the loop is constantly checking if the interrupt flag is set.
 *  If this condition is fulfilled, we're reading the temperature as well as the
 *  magnetic values in X, Y, Z-direction and printing them to the console.
 *  Afterwards we're reseting the flag and wait for two seconds.
 */
void loop() {
    if( intTriggered ) {
        double temp1 = 0.0;
        double valX1 = 0, valY1 = 0, valZ1 = 0;

        dut.printRegisters();

        dut.getTemperature(&temp1); 
        dut.getMagneticField(&valX1, &valY1, &valZ1);
    
        Serial.println("========================================");
        Serial.print("Temperature of Sensor 1:\t");Serial.print(temp1);Serial.println(" °C");
        Serial.print("Magnetic X-Value of Sensor 1:\t");Serial.print(valX1);Serial.println(" mT");
        Serial.print("Magnetic Y-Value of Sensor 1:\t");Serial.print(valY1);Serial.println(" mT");
        Serial.print("Magnetic Z-Value of Sensor 1:\t");Serial.print(valZ1);Serial.println(" mT");

        delay(2000);

        intTriggered = false;
    }
}

/** The interrupt service routine is simply setting a boolean flag as soon the sensor interrupt is triggered */
void wakeUp_ISR() {
    intTriggered = true;
}