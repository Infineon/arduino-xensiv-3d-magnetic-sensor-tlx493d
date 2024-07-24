/** Arduino includes. */
#include <Arduino.h>

/** project cpp includes. */
#include "Kit2GoBoardSupport.hpp"


namespace ifx {
    namespace tlx493d {
        Kit2GoBoardSupport::Kit2GoBoardSupport() : powerPins{false, 0, 0, 0, 0, 0, 0, 0},
                                                   selectPins{false, 0, 0, 0, 0, 0, 0, 0},
                                                   addressPins{false, 0, 0, 0, 0, 0, 0, 0} {
        }


        Kit2GoBoardSupport::~Kit2GoBoardSupport() {
        }

        
        void Kit2GoBoardSupport::init(bool isEnablePower, bool isEnableSelect, bool isEnableExtendedAddress) {
            if( isEnableSelect ) {
                for(const auto &p : selectPins) {
                    initPin(p);
                }

                enableSelect(false);
            }

            if( isEnableExtendedAddress ) {
                for(const auto &p : addressPins){
                    initPin(p);
                }

                enableAddress(true);
            }

            if( isEnablePower ) {
                for(const auto &p : powerPins) {
                    initPin(p);
                }

                reset();
            }

            if( isEnableExtendedAddress ) {
                enableAddress(false);

                for(auto &p : addressPins){
                    setPinDirectionToTristate(p);
                }
            }
        }


        void Kit2GoBoardSupport::begin(bool enablePower, bool enableSelect, bool enableExtendedAddress) {
            init(enablePower, enableSelect, enableExtendedAddress);
        }


        void Kit2GoBoardSupport::deinit() {
            enablePower(false);
            enableSelect(false);
        }


        void Kit2GoBoardSupport::end() {
            deinit();
        }


        void Kit2GoBoardSupport::setPowerPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                             uint8_t pinEnableValue, uint8_t pinDisableValue,
                                             uint32_t delayAfterEnable, uint32_t delayAfterDisable) {
            powerPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
        }


        void Kit2GoBoardSupport::unsetPowerPin() {
            powerPins[0].isSet = false;
        }


        void Kit2GoBoardSupport::setSelectPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                              uint8_t pinEnableValue, uint8_t pinDisableValue,
                                              uint32_t delayAfterEnable, uint32_t delayAfterDisable) {
            selectPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
        }


        void Kit2GoBoardSupport::unsetSelectPin() {
            selectPins[0].isSet = false;
        }


        void Kit2GoBoardSupport::setAddressPin(uint8_t pinNumber, uint8_t pinDriveDirection, uint8_t pinTristateDirection,
                                               uint8_t pinEnableValue, uint8_t pinDisableValue,
                                               uint32_t delayAfterEnable, uint32_t delayAfterDisable) {
            addressPins[0] = { true, pinNumber, pinDriveDirection, pinTristateDirection, pinEnableValue, pinDisableValue, delayAfterEnable, delayAfterDisable };
        }


        void Kit2GoBoardSupport::unsetAddressPin() {
            addressPins[0].isSet = false;
        }


        void Kit2GoBoardSupport::enablePower(bool enable) {
            for(const auto &p : powerPins) {
                enablePin(p, enable);
            }
        }


        void Kit2GoBoardSupport::enableSelect(bool enable) {
            for(const auto &p : selectPins) {
                enablePin(p, enable);
            }
        }


        void Kit2GoBoardSupport::enableAddress(bool enable) {
            for(const auto &p : addressPins) {
                enablePin(p, enable);
            }
        }


        void Kit2GoBoardSupport::reset() {
            enablePower(false);
            enablePower(true);
        }


        void Kit2GoBoardSupport::enablePin(const pinCtrl &p, bool enable) {
            if( p.isSet ) {
                digitalWrite(p.pinNumber, enable ? p.enableValue : p.disableValue);
                delayMicroseconds(enable ? p.delayAfterEnable : p.delayAfterDisable);
            }
        }


        void Kit2GoBoardSupport::initPin(const pinCtrl &p) {
            if( p.isSet ) {
                pinMode(p.pinNumber, p.driveDirection);
            }
        }


        void Kit2GoBoardSupport::setPinDirectionToDrive(pinCtrl &p) {
            if( p.isSet ) {
                pinMode(p.pinNumber, p.driveDirection);
            }
        }


        void Kit2GoBoardSupport::setPinDirectionToTristate(pinCtrl &p) {
            if( p.isSet ) {
                pinMode(p.pinNumber, p.tristateDirection);
            }
        }
    }
}
