#ifndef TLX493D_A2B6_ENUMS_H
#define TLX493D_A2B6_ENUMS_H


/***
 * Listing of all register names for this sensor.
 * Used to index "TLx493D_A2B6_regDef" defined below, so index values must match !
*/
typedef enum {
                A2B6_BX_MSBS_e = 0,
                A2B6_BY_MSBS_e,
                A2B6_BZ_MSBS_e,
                A2B6_TEMP_MSBS_e,
                A2B6_BX_LSBS_e,
                A2B6_BY_LSBS_e,
                A2B6_TEMP_LSBS_e,
                A2B6_ID_e,
                A2B6_BZ_LSBS_e,
                A2B6_P_e,
                A2B6_FF_e,
                A2B6_CF_e,
                A2B6_T_e,
                A2B6_PD3_e,
                A2B6_PD0_e,
                A2B6_FRM_e,
                A2B6_DT_e,
                A2B6_AM_e,
                A2B6_TRIG_e,
                A2B6_X2_e,
                A2B6_TL_MAG_e,
                A2B6_CP_e,
                A2B6_FP_e,
                A2B6_IICADR_e,
                A2B6_PR_e,
                A2B6_CA_e,
                A2B6_INT_e,
                A2B6_MODE_e,
                A2B6_PRD_e,
                A2B6_TYPE_e,
                A2B6_HWV_e,
} TLx493D_A2B6_registerNames_t;


typedef enum { 
               A2B6_TEMP2_REG_e  = 0x05,
               A2B6_DIAG_REG_e   = 0x06,
               A2B6_CONFIG_REG_e = 0x10,
               A2B6_MOD1_REG_e   = 0x11,
               A2B6_MOD2_REG_e   = 0x13,
               A2B6_VER_REG_e    = 0x16,
} TLx493D_A2B6_specialRegisters_t;


#endif /** TLX493D_A2B6_ENUMS_H */
