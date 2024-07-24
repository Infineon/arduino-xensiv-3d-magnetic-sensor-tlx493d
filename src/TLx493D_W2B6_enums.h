#ifndef TLX493D_W2B6_ENUMS_H
#define TLX493D_W2B6_ENUMS_H


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_W2B6_regDef" defined below_e, so index values must match !
*/
typedef enum {
                W2B6_BX_MSBS_e = 0,
                W2B6_BY_MSBS_e,
                W2B6_BZ_MSBS_e,
                W2B6_TEMP_MSBS_e,
                W2B6_BX_LSBS_e,
                W2B6_BY_LSBS_e,
                W2B6_TEMP_LSBS_e,
                W2B6_ID_e,
                W2B6_BZ_LSBS_e,
                W2B6_P_e,
                W2B6_FF_e,
                W2B6_CF_e,
                W2B6_T_e,
                W2B6_PD3_e,
                W2B6_PD0_e,
                W2B6_FRM_e,
                W2B6_XL_MSBS_e,
                W2B6_XH_MSBS_e,
                W2B6_YL_MSBS_e,
                W2B6_YH_MSBS_e,
                W2B6_ZL_MSBS_e,
                W2B6_ZH_MSBS_e,
                W2B6_WA_e,
                W2B6_WU_e,
                W2B6_XH_LSBS_e,
                W2B6_XL_LSBS_e,
                W2B6_TST_e,
                W2B6_YH_LSBS_e,
                W2B6_YL_LSBS_e,
                W2B6_PH_e,
                W2B6_ZH_LSBS_e,
                W2B6_ZL_LSBS_e,
                W2B6_DT_e,
                W2B6_AM_e,
                W2B6_TRIG_e,
                W2B6_X2_e,
                W2B6_TL_MAG_e,
                W2B6_CP_e,
                W2B6_FP_e,
                W2B6_IICADR_e,
                W2B6_PR_e,
                W2B6_CA_e,
                W2B6_INT_e,
                W2B6_MODE_e,
                W2B6_PRD_e,
                W2B6_TYPE_e,
                W2B6_HWV_e,
} TLx493D_W2B6_registerNames_t;


typedef enum { 
               W2B6_TEMP2_REG_e  = 0x05,
               W2B6_DIAG_REG_e   = 0x06,
               W2B6_CONFIG_REG_e = 0x10,
               W2B6_MOD1_REG_e   = 0x11,
               W2B6_MOD2_REG_e   = 0x13,
               W2B6_VER_REG_e    = 0x16,
} TLx493D_W2B6_specialRegisters_t;


#endif /** TLX493D_W2B6_ENUMS_H */
