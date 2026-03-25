#ifndef TLX493D_P2B6_ENUMS_H
#define TLX493D_P2B6_ENUMS_H


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_P2B6_regDef" defined below, so index values must match !
*/
typedef enum {
                P2B6_BX_MSBS_e = 0,
                P2B6_BY_MSBS_e,
                P2B6_BZ_MSBS_e,
                P2B6_TEMP_MSBS_e,
                P2B6_BX_LSBS_e,
                P2B6_BY_LSBS_e,
                P2B6_TEMP_LSBS_e,
                P2B6_ID_e,
                P2B6_BZ_LSBS_e,
                P2B6_P_e,
                P2B6_FF_e,
                P2B6_CF_e,
                P2B6_T_e,
                P2B6_PD3_e,
                P2B6_PD0_e,
                P2B6_FRM_e,
                P2B6_XL_MSBS_e,
                P2B6_XH_MSBS_e,
                P2B6_YL_MSBS_e,
                P2B6_YH_MSBS_e,
                P2B6_ZL_MSBS_e,
                P2B6_ZH_MSBS_e,
                P2B6_WA_e,
                P2B6_WU_e,
                P2B6_XH_LSBS_e,
                P2B6_XL_LSBS_e,
                P2B6_TST_e,
                P2B6_YH_LSBS_e,
                P2B6_YL_LSBS_e,
                P2B6_PH_e,
                P2B6_ZH_LSBS_e,
                P2B6_ZL_LSBS_e,
                P2B6_DT_e,
                P2B6_AM_e,
                P2B6_TRIG_e,
                P2B6_X2_e,
                P2B6_TL_MAG_e,
                P2B6_CP_e,
                P2B6_FP_e,
                P2B6_IICADR_e,
                P2B6_PR_e,
                P2B6_CA_e,
                P2B6_INT_e,
                P2B6_MODE_e,
                P2B6_PRD_e,
                P2B6_TYPE_e,
                P2B6_HWV_e,
} TLx493D_P2B6_registerNames_te;


typedef enum { 
               P2B6_TEMP2_REG_e  = 0x05,
               P2B6_DIAG_REG_e   = 0x06,
               P2B6_CONFIG_REG_e = 0x10,
               P2B6_MOD1_REG_e   = 0x11,
               P2B6_MOD2_REG_e   = 0x13,
               P2B6_VER_REG_e    = 0x16,
} TLx493D_P2B6_SpecialRegisters_te;


#endif /** TLX493D_P2B6_ENUMS_H */
