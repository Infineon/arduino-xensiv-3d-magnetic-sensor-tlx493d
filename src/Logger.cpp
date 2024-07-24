/** std includes. */
#ifdef __AVR__

    #include <stdarg.h>
    #include <stdio.h>
    #include <string.h>

#else

    #include <cstdarg>
    #include <cstdio>
    #include <cstring>

#endif


/** Arduino includes. */
#include <Arduino.h>

/** project c includes. */
#include "tlx493d_types.h"
#include "Logger.h"


const uint16_t LOGGER_BUFFER_SIZE = 512U;


static void logMessage(const char *prefix, const char *format, va_list vaList) {
    char buffer[LOGGER_BUFFER_SIZE];

    size_t prefixSize = strlen(prefix);
    (void) memcpy(buffer, prefix, prefixSize);
    int ret = vsprintf(buffer + prefixSize, format, vaList);

    if( (ret + prefixSize) > LOGGER_BUFFER_SIZE ) {
        Serial.print("FATAL : Buffer overflow (> ");
        Serial.print(LOGGER_BUFFER_SIZE);
        Serial.println(" characters) because message too long !\n");
    }

    Serial.print(buffer);
}


extern "C" {
    void logPrintRegisters(const TLx493D_t *sensor, const char *headLine = NULL) {
        Serial.println();


#if defined(ARDUINO_ARM_XMC) || (defined(__AVR__) && (defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_AVR_MEGA2560)))

        if( headLine != NULL ) {
            Serial.println(headLine);
        }

#endif

        for(uint8_t i = 0; i < sensor->regMapSize; ++i) {
            logPrint("    0x%02X", sensor->regMap[i]);
        }

        Serial.println();
    }


    void logPrintDouble(double d) {
        Serial.print(d);
    }


    void logPrint(const char *format, ...) {
        va_list ap;
        va_start(ap, format);
        logMessage("", format, ap);
        va_end(ap);
    }


    void logPrintln(const char *prefix, const char *format, ...) {
        Serial.println();
        va_list ap;
        va_start(ap, format);
        logMessage(prefix, format, ap);
        va_end(ap);
        Serial.println();
    }


    void logFlush() {
        Serial.flush();
    }
}
