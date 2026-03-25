#ifndef TLX493D_W2BW_ENUMS_H
#define TLX493D_W2BW_ENUMS_H


typedef enum {
                W2BW_BX_MSBS_e = 0,
                W2BW_BY_MSBS_e,
                W2BW_BZ_MSBS_e,
                W2BW_TEMP_MSBS_e,
                W2BW_BX_LSBS_e,
                W2BW_BY_LSBS_e,
                W2BW_TEMP_LSBS_e,
                W2BW_ID_e,
                W2BW_BZ_LSBS_e,
                W2BW_P_e,
                W2BW_FF_e,
                W2BW_CF_e,
                W2BW_T_e,
                W2BW_PD3_e,
                W2BW_PD0_e,
                W2BW_FRM_e,
                W2BW_XL_MSBS_e, 
                W2BW_XH_MSBS_e,
                W2BW_YL_MSBS_e, 
                W2BW_YH_MSBS_e, 
                W2BW_ZL_MSBS_e, 
                W2BW_ZH_MSBS_e,
                W2BW_WA_e,
                W2BW_WU_e,
                W2BW_XH_LSBS_e,
                W2BW_XL_LSBS_e,
                W2BW_YH_LSBS_e,
                W2BW_YL_LSBS_e,
                W2BW_ZH_LSBS_e,
                W2BW_ZL_LSBS_e, 
                W2BW_DT_e,
                W2BW_AM_e,
                W2BW_TRIG_e,
                W2BW_X2_e,
                W2BW_TL_MAG_e,
                W2BW_CP_e,
                W2BW_FP_e,
                W2BW_IICADR_e,
                W2BW_PR_e,
                W2BW_CA_e,
                W2BW_INT_e,
                W2BW_MODE_e,
                W2BW_PRD_e,
                W2BW_X4_e,
                W2BW_TYPE_e,
                W2BW_HWV_e,
                W2BW_X4_READWRITE_e,
} TLx493D_W2BW_registerNames_te;


typedef enum { 
               W2BW_TEMP2_REG_e   = 0x05,
               W2BW_DIAG_REG_e    = 0x06,
               W2BW_CONFIG_REG_e  = 0x10,
               W2BW_MOD1_REG_e    = 0x11,
               W2BW_MOD2_REG_e    = 0x13,
               W2BW_CONFIG2_REG_e = 0x14,
               W2BW_VER_REG_e     = 0x16,
} TLx493D_W2BW_SpecialRegisters_te;


#endif /** TLX493D_W2BW_ENUMS_H */
