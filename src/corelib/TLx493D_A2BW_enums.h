#ifndef TLX493D_A2BW_ENUMS_H
#define TLX493D_A2BW_ENUMS_H


typedef enum {
                A2BW_BX_MSBS_e = 0,
                A2BW_BY_MSBS_e,
                A2BW_BZ_MSBS_e,
                A2BW_TEMP_MSBS_e,
                A2BW_BX_LSBS_e,
                A2BW_BY_LSBS_e,
                A2BW_TEMP_LSBS_e,
                A2BW_ID_e,
                A2BW_BZ_LSBS_e,
                A2BW_P_e,
                A2BW_FF_e,
                A2BW_CF_e,
                A2BW_T_e,
                A2BW_PD3_e,
                A2BW_PD0_e,
                A2BW_FRM_e,
                A2BW_DT_e,
                A2BW_AM_e,
                A2BW_TRIG_e,
                A2BW_X2_e,
                A2BW_TL_MAG_e,
                A2BW_CP_e,
                A2BW_FP_e,
                A2BW_IICADR_e,
                A2BW_PR_e,
                A2BW_CA_e,
                A2BW_INT_e,
                A2BW_MODE_e,
                A2BW_PRD_e,
                A2BW_X4_e,
                A2BW_TYPE_e,
                A2BW_HWV_e,
                A2BW_X4_READWRITE_e,
} TLx493D_A2BW_registerNames_te;


typedef enum { 
               A2BW_TEMP2_REG_e   = 0x05,
               A2BW_DIAG_REG_e    = 0x06,
               A2BW_CONFIG_REG_e  = 0x10,
               A2BW_MOD1_REG_e    = 0x11,
               A2BW_MOD2_REG_e    = 0x13,
               A2BW_CONFIG2_REG_e = 0x14,
               A2BW_VER_REG_e     = 0x16,
} TLx493D_A2BW_SpecialRegisters_te;


#endif /** TLX493D_A2BW_ENUMS_H */
