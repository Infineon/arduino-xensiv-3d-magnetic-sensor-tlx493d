#ifndef TLX493D_ENUMS_H
#define TLX493D_ENUMS_H


#ifdef __cplusplus

extern "C" {

#endif


/**
 * @brief The enumeration `TLx493D_SupportedSensorType_t` defines all the supported sensor types of the library.
 */
typedef enum {
               TLx493D_A1B6_e = 0,
               TLx493D_A2B6_e,
               TLx493D_A2BW_e,
               TLx493D_P2B6_e,
               TLx493D_W2B6_e,
               TLx493D_W2BW_e,
               TLx493D_P3B6_e,
               TLx493D_P3I8_e,
} TLx493D_SupportedSensorType_t;


/**
 * @brief The enumeration `TLx493D_SupportedComLibraryInterfaceType_t` defines the supported communication interfaces of
 * of the different sensors.
 */
typedef enum {
               TLx493D_I2C_e = 0,
               TLx493D_SPI_e,
} TLx493D_SupportedComLibraryInterfaceType_t;


/**
 * @brief The enumeration `TLx493D_RegisterAccessModeType_t` defines the access modes of the different registers inside the sensors.
 */
typedef enum { TLx493D_READ_MODE_e = 0, 
               TLx493D_WRITE_MODE_e,
               TLx493D_READ_WRITE_MODE_e,
} TLx493D_RegisterAccessModeType_t;


/**
 * @brief The enumeration `TLx493D_IICAddressType_t` defines the possible I2C addresses of the different sensors. They're used to
 * establish a connection to the sensor.
 */
typedef enum {
    TLx493D_IIC_ADDR_A0_e = 0,
    TLx493D_IIC_ADDR_A1_e,
    TLx493D_IIC_ADDR_A2_e,
    TLx493D_IIC_ADDR_A3_e,
    TLx493D_IIC_ADDR_A4_e,
    TLx493D_IIC_ADDR_A5_e,
    TLx493D_IIC_ADDR_A6_e,
    TLx493D_IIC_ADDR_A7_e,
} TLx493D_IICAddressType_t;


/**
 * @brief The enumeration `TLx493D_MeasurementType_t` defines the different measurement modes of the sensors. You have to make sure
 * that you are using a mode which is available for your used sensor family (1st Gen, 2nd Gen, etc.).
 */
typedef enum {
    /** 1st and 2nd generation. */
    TLx493D_BxByBz_e = 0,
    
    /**  1st and 3rd generation. */
    TLx493D_BxByBzTemp_e,

    /** 3rd generation. */
    TLx493D_VHall_Bias_e,
    TLx493D_Spintest_e,
    TLx493D_SAT_test_e,
    TLx493D_BxTemp_e,
    TLx493D_BxBy_e,
    TLx493D_BzTemp_e,
} TLx493D_MeasurementType_t;


/**
 * @brief The enumeration `TLx493D_TriggerType_t` defines the different trigger modes for the sensors. You have to make sure that
 * you are using a mode which is available for your used sensor family (1st Gen, 2nd Gen, etc.).
 */
typedef enum {
               /** 1st and 2nd generation. */
               TLx493D_NO_ADC_ON_READ_e = 0,
               TLx493D_ADC_ON_READ_BEFORE_FIRST_MSB_e,
               TLx493D_ADC_ON_READ_AFTER_REG_05_e,

               /** 3rd generation only. */
               TLx493D_NO_TRIGGER_e,
               TLx493D_ADC_ON_READ_e,
               TLx493D_ADC_ON_STOP_CONDITION_e,
} TLx493D_TriggerType_t;


/**
 * @brief The enumeration `TLx493D_SensitivityType_t` defines the different range settings for the sensors. You have to make sure that
 * you're using a mode which is available for your used sensor family (1st Gen, 2nd Gen, etc.).
 */
typedef enum {
               TLx493D_FULL_RANGE_e = 0, 
               TLx493D_SHORT_RANGE_e,
               TLx493D_EXTRA_SHORT_RANGE_e,
} TLx493D_SensitivityType_t;


/**
 * @brief The enumeration `TLx493D_AvailableSensitivityType_t` defines the different bits which define the range of the used sensor.
 * They are different depending on the used sensor type. The `TLx493D_SensitivityType_t` depends on the available `TLx493D_AvailableSensitivityType_t`.
 
 */
typedef enum {
               TLx493D_HAS_X1_e = 0, 
               TLx493D_HAS_X2_e, 
               TLx493D_HAS_X4_e,
} TLx493D_AvailableSensitivityType_t;


/**
 * @brief The enumeration `TLx493D_PowerModeType_t` defines the different power modes of the sensors. The available ones are depending
 * on the sensor variant that you are using.
 */
typedef enum {
               TLx493D_POWER_DOWN_MODE_e = 0,
               TLx493D_FAST_MODE_e,
               TLx493D_LOW_POWER_MODE_e,
               TLx493D_ULTRA_LOW_POWER_MODE_e,
               TLx493D_MASTER_CONTROLLED_MODE_e,
} TLx493D_PowerModeType_t;


/**
 * @brief The enumeration `TLx493D_UpdateRateType_t` defines the different update rates of the sensors. Depending on which sensor variant you're
 * using you can choose different update rates.
 */
typedef enum {
               /** Generation 2 */
               TLx493D_UPDATE_RATE_FAST_e = 0,
               TLx493D_UPDATE_RATE_SLOW_e,
               TLx493D_UPDATE_RATE_770_HZ_e,
               TLx493D_UPDATE_RATE_97_HZ_e,
               TLx493D_UPDATE_RATE_24_HZ_e,
               TLx493D_UPDATE_RATE_12_HZ_e,
               TLx493D_UPDATE_RATE_6_HZ_e,
               TLx493D_UPDATE_RATE_3_HZ_e,
               TLx493D_UPDATE_RATE_0_4_HZ_e,
               TLx493D_UPDATE_RATE_0_05_HZ_e,

               /** Generation 3 */
               TLx493D_UPDATE_RATE_1000_HZ_e,
               TLx493D_UPDATE_RATE_125_HZ_e,
               TLx493D_UPDATE_RATE_31_HZ_e,
               TLx493D_UPDATE_RATE_16_HZ_e,
} TLx493D_UpdateRateType_t;


#ifdef __cplusplus

}

#endif


#endif /** TLX493D_ENUMS_H */