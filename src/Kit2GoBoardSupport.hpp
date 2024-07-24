/*********************************************************************
 * @file  Kit2GoBoardSupport.hpp
 * 
 * @brief Implementation of the class Kit2GoBoardSupport for custom sensor/board bring up.
 * This can be used to power cycle the sensor device, help with setting/resetting the SPI
 * slave select lines for multiple devices and also setting/resetting addressing lines 
 * for enabling extended addresses for certain devices.  
 *********************************************************************/

#ifndef TLX493D_KIT2GO_BOARD_SUPPORT_HPP
#define TLX493D_KIT2GO_BOARD_SUPPORT_HPP


/** Arduino includes. */
#include <Arduino.h>

//
namespace ifx {
    namespace tlx493d {
        /**
         * @brief The Kit2GoBoardSupport class used for custom board bring up, for control of SPI slave select lines 
         * and for controlling address lines for extended addressing of certain devices.
         */
        class Kit2GoBoardSupport {

            public:
            
                /**
                 * Create a new Kit2GoBoardSupport object with initialised data structures of type PinCtrl to hold parameters for powerPins, selectPins
                 * and addressPins.
                 * @brief Default constructor with no parameters.
                 */
                Kit2GoBoardSupport();

                /**
                 * @brief Destructor of the Kit2GoBoardSupport class.
                */
                ~Kit2GoBoardSupport();


                /**
                 * @brief The function `init` sets/resets the board pin modes and/or values based on the values of the data structures set in the main code.  
                 * 
                 * @param[in] enablePower Whether to power up the board using this class. In this case the board 3V3 is routed through a GPIO of the host MCU.
                 * @param[in] enableSelect Whether SPI slaves SELECT lines need to be controlled using this class. A particular slave is selected by pulling its 
                 * corresponding SELECT line low.
                 * @param[in] enableExtendedAddress (Only relevant for Generation 1, A1B6 devices) Whether to use extended addressing feature. In this case, the pin
                 *  stored in addressPins structure is activated and later isolated in a prescribed way to enable the 4 extended addresses of the said device.        
                 */
                void init(bool isEnablePower = true, bool isEnableSelect = false, bool isEnableExtendedAddress = false);
                

                /**
                 * @brief The `begin` function recursively calls the `init` function of the same class.
                 * 
                 * @param[in] enablePower Whether to power up the board using this class. In this case the board 3V3 is routed through a GPIO of the host MCU.
                 * @param[in] enableSelect Whether SPI slaves SELECT lines need to be controlled using this class. A particular slave is selected by pulling its 
                 * corresponding SELECT line low.
                 * @param[in] enableExtendedAddress (Only relevant for Generation 1, A1B6 devices) Whether to use extended addressing feature. In this case, the pin
                 *  stored in addressPins structure is activated and later isolated in a prescribed way to enable the 4 extended addresses of the said device.   
                 */
                void begin(bool enablePower = true, bool enableSelect = false, bool enableExtendedAddress = false);


                /**
                 * @brief The `deinit` function sets all the pins to their disable value.
                 */
                void deinit();


                /**
                 * @brief The `end` function recursively calls the `deinit` function of the same class.
                 */
                void end() ;


                /**
                 * @brief The `setPowerPin` function is setter function to route pin parameters from the main code into the data structures/variables of this class.
                 * 
                 * @param[in] pinNumber Arduino pin number of the GPIO to be used as 3V3 POWER pin for the sensor.
                 * @param[in] pinDriveDirection Direction of the Arduino pin to be used as the 3V3 POWER pin.
                 * @param[in] pinTristateDirection Direction of the Arduino pin when in tristate.
                 * @param[in] pinEnableValue Value of the pin in enabled state.
                 * @param[in] pinDisableValue Value of the pin in disabled state.
                 * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.  
                 * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
                 */
                void setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                 uint8_t pinEnableValue, uint8_t pinDisableValue,
                                 uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0);


                /**
                 * @brief The `unsetPowerPin` function disables all actions on the pins set in powerPins that would otherwise be performed by the `init` function.
                 */
                void unsetPowerPin();


                /**
                 * @brief The `setSelectPin` function is setter function to route pin parameters from the main code into the data structures/variables of this class.
                 * @param[in] pinNumber Arduino pin number of the GPIO to be used as SELECT pin for the sensor used as SPI slave.
                 * @param[in] pinDirection Direction of the Arduino pin to be used as the select pin for the sensor used as SPI slave.
                 * @param[in] pinTristateDirection Direction of the Arduino pin when in tristate.
                 * @param[in] pinEnableValue Value of the pin in enabled state.
                 * @param[in] pinDisableValue Value of the pin in disabled state.
                 * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.
                 * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
                 */
                void setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                  uint8_t pinEnableValue, uint8_t pinDisableValue,
                                  uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0);


                /**
                 * @brief The `unsetSelectPin` function disables all actions on the pins set in selectPins that would otherwise be performed by the `init` function.
                 */    
                void unsetSelectPin();


                /**
                 * @brief The `setAddressPin` function is setter function to route pin parameters from the main code into the data structures/variables of this class.
                 * 
                 * @param[in] pinNumber Arduino pin number of the GPIO to be used as the ADDR pin for the sensor used as SPI slave.
                 * @param[in] pinDirection Direction of the Arduino pin to be used as the ADDR pin for the sensor used as SPI slave.
                 * @param[in] pinTristateDirection Direction of the Arduino pin when in tristate.
                 * @param[in] pinEnableValue Value of the pin in enabled state.
                 * @param[in] pinDisableValue Value of the pin in disabled state.
                 * @param[in] delayAfterEnable delay in ms after the pin is enabled. Needed to meet settling time constraints.
                 * @param[in] delayAfterDisable delay in ms after the pin is disabled. Needed to meet settling time constraints.
                 */
                void setAddressPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                   uint8_t pinEnableValue, uint8_t pinDisableValue,
                                   uint32_t delayAfterEnable = 0, uint32_t delayAfterDisable = 0);

                /**
                 * @brief The `unsetAddressPin` function disables all actions on the pins set in selectPins that would otherwise be performed by the `init` function.
                 */ 
                void unsetAddressPin();


                /**
                 * @brief The `enablePower` function sets/resets the pins in powerPins based on argument.
                 * 
                 * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
                 */
                void enablePower(bool enable) ;

                /**
                 * @brief The `enableSelect` function sets/resets the pins in selectPins based on argument.
                 * 
                 * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
                  */
                void enableSelect(bool enable);

                /**
                 * @brief The `enableAddress` function sets/resets the pins in selectPins based on argument.
                 * 
                 * @param enable Sets pin to pinEnableValue if true, else to pinDisableValue.
                 */    
                void enableAddress(bool enable);


                /**
                 * @brief The `reset` function resets the power pin by going through a disable / enable cycle.
                 */    
                void reset();


            private:

                /**
                * A structure to represent pins with all necessary parameters. 
                */
                typedef struct pinCtrl {
                    /*@{*/
                    bool     isSet;             /**< the state of the pin, to be activated or not at `init`. */
                    uint8_t  pinNumber;         /**< the Arduino pin number of the pin. */

                    uint8_t  driveDirection;    /**< the direction for the Arduino pin when actively driving. */
                    uint8_t  tristateDirection; /**< the direction for the Arduino pin when in tristate. */
                    
                    uint8_t  enableValue;       /**< the value of the pin to be enabled or set by the `init` function. */
                    uint8_t  disableValue;      /**< the value of the pin when the pin is disabled. */

                    uint32_t delayAfterEnable;  /**< the delay in us after the pin is enabled. */
                    uint32_t delayAfterDisable; /**< the delay in us after the pin is disabled. */
                    /*@}*/
                } pinCtrl;


                /**
                 * @brief The `enablePin` function sets/resets the pin on the basis of parameters in the structure `pinCtrl`.
                 * 
                 * @param[in] p Structure of type `pinCtrl`.
                 * @param[in] enable Sets pin to pinEnableValue if true, else to pinDisableValue.
                 */ 
                void enablePin(const pinCtrl &p, bool enable);


                /**
                 * @brief The `initPin` function sets the direction and value of the pin on the basis of parameters in the structure `pinCtrl`.
                 * 
                 * @param[in] p Structure of type `pinCtrl`.
                 */ 
                void initPin(const pinCtrl &p);


                /**
                 * @brief The `setPinDirectionToDrive` function sets the direction of the pin to drive mode.
                 * 
                 * @param[in] p Structure of type `pinCtrl`.
                */
                void setPinDirectionToDrive(pinCtrl &p);


                /**
                 * @brief The `setPinDirectionToTristate` function sets the direction of the pin to tristate mode.
                 * 
                 * @param[in] p Structure of type `pinCtrl`.
                */
                void setPinDirectionToTristate(pinCtrl &p);


                /**
                * Structure variables to hold parameters of powerPins, selectPins and addressPins.
                */ 
                pinCtrl powerPins[1];
                pinCtrl selectPins[1];
                pinCtrl addressPins[1];
        };
    }
}


#endif // TLX493D_KIT2GO_BOARD_SUPPORT_HPP
