#ifndef TLX493D_A1B6_ENUMS_H
#define TLX493D_A1B6_ENUMS_H


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_A1B6_regDef" defined below, so index values must match !
*/
typedef enum {
                A1B6_BX_MSB_e = 0,
                A1B6_BY_MSB_e,
                A1B6_BZ_MSB_e,
                A1B6_TEMP_MSB_e,
                A1B6_FRM_e,
                A1B6_CH_e,
                A1B6_BX_LSB_e,
                A1B6_BY_LSB_e,
                A1B6_T_e,
                A1B6_FF_e,
                A1B6_PD_e,
                A1B6_BZ_LSB_e,
                A1B6_TEMP_LSB_e,
                A1B6_R_RES_1_e,
                A1B6_R_RES_2_e,
                A1B6_R_RES_3_e,
                A1B6_W_RES_0_e,
                A1B6_P_e,
                A1B6_IICADR_e,
                A1B6_W_RES_1_e,
                A1B6_INT_e,
                A1B6_FAST_e,
                A1B6_LOW_POWER_e,
                A1B6_W_RES_2_e,
                A1B6_Temp_NEN_e,
                A1B6_LP_e,
                A1B6_PT_e,
                A1B6_W_RES_3_e,
} TLx493D_A1B6_registerNames_te;


typedef enum { 
                A1B6_MOD1_REG_e   = 0x01,
                A1B6_MOD2_REG_e   = 0x03,
} TLx493D_A1B6_SpecialRegisters_te;           


#endif /** TLX493D_A1B6_ENUMS_H */
