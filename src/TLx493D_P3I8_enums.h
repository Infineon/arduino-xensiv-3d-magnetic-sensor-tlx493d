#ifndef TLX493D_P3I8_ENUMS_H
#define TLX493D_P3I8_ENUMS_H


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_P3I8_regDef" defined below, so index values must match !
*/
typedef enum {
                P3I8_BX_MSBS_e = 0,
                P3I8_BX_LSBS_e,
                P3I8_BY_MSBS_e,
                P3I8_BY_LSBS_e,
                P3I8_BZ_MSBS_e,
                P3I8_BZ_LSBS_e,
                P3I8_TEMP_MSBS_e,
                P3I8_TEMP_LSBS_e,
                P3I8_CRC_e,
                P3I8_MEAS_FLG_e,
                P3I8_TEST_FLG_e,
                P3I8_FRAME_COUNTER_e,
                P3I8_RST_FLG_e,
                P3I8_WU_PAR_FLG_e,
                P3I8_CRC_WR_FLG_e,
                P3I8_FUSE_PAR_FLG_e,
                P3I8_MODE_SEL_e,
                P3I8_INT_DIS_e,
                P3I8_WU_EN_e,
                P3I8_TRIGGER_SEL_e,
                P3I8_CRC_WR_EN_e,
                P3I8_CHANNEL_SEL_e,
                P3I8_F_UPDATE_SEL_e,
                P3I8_XTR_SHORT_EN_e,
                P3I8_SHORT_EN_e,
                P3I8_WU_XH_MSBS_e,
                P3I8_WU_XL_MSBS_e,
                P3I8_WU_YH_MSBS_e,
                P3I8_WU_YL_MSBS_e,
                P3I8_WU_ZH_MSBS_e,
                P3I8_WU_ZL_MSBS_e,
                P3I8_WU_XH_LSBS_e,
                P3I8_WU_XL_LSBS_e,
                P3I8_WU_YH_LSBS_e,
                P3I8_WU_YL_LSBS_e,
                P3I8_WU_PAR_e,
                P3I8_WU_EN_CP_e,
                P3I8_WU_ZH_LSBS_e,
                P3I8_WU_ZL_LSBS_e,
                P3I8_RST_FLG_CLR_e,
                P3I8_SOFT_RST_e,
                P3I8_CHIP_ID_0_e,
                P3I8_CHIP_ID_1_e,
                P3I8_CHIP_ID_2_e,
                P3I8_CHIP_ID_3_e,
                P3I8_CHIP_ID_4_e,
                P3I8_ID_PAR_e,
                P3I8_CHIP_ID_5_e,
                P3I8_CHANNEL_SEL_SAVE_e,
} TLx493D_P3I8_registerNames_te;


typedef enum { 
               P3I8_CRC_REG_e    = 0x08,
               P3I8_DIAG_REG_e   = 0x09,
               P3I8_MOD1_REG_e   = 0x0A,
               P3I8_MOD2_REG_e   = 0x0B,
} TLx493D_P3I8_SpecialRegisters_te;


#endif /** TLX493D_P3I8_ENUMS_H */
