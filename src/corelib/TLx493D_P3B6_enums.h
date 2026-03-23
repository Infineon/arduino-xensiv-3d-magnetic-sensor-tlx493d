#ifndef TLX493D_P3B6_ENUMS_H
#define TLX493D_P3B6_ENUMS_H


/*
  Listing of all register names for this sensor.
  Used to index "TLx493D_P3B6_regDef" defined below_e, so index values must match !
*/
typedef enum {
                P3B6_BX_MSBS_e = 0,
                P3B6_IIC_ADR_CP_e,
                P3B6_BX_LSBS_e,
                P3B6_BY_MSBS_e,
                P3B6_BY_LSBS_e,
                P3B6_BZ_MSBS_e,
                P3B6_BZ_LSBS_e,
                P3B6_TEMP_MSBS_e,
                P3B6_TEMP_LSBS_e,
                P3B6_CRC_e,
                P3B6_MEAS_FLG_e,
                P3B6_TEST_FLG_e,
                P3B6_FRAME_COUNTER_e,
                P3B6_RST_FLG_e,
                P3B6_WU_PAR_FLG_e,
                P3B6_CRC_WR_FLG_e,
                P3B6_FUSE_PAR_FLG_e,
                P3B6_MODE_SEL_e,
                P3B6_INT_DIS_e,
                P3B6_COLLISION_DIS_e,
                P3B6_WU_EN_e,
                P3B6_TRIGGER_SEL_e,
                P3B6_PROT_SEL_e,
                P3B6_CRC_WR_EN_e,
                P3B6_CHANNEL_SEL_e,
                P3B6_F_UPDATE_SEL_e,
                P3B6_XTR_SHORT_EN_e,
                P3B6_SHORT_EN_e,
                P3B6_WU_XH_MSBS_e,
                P3B6_WU_XL_MSBS_e,
                P3B6_WU_YH_MSBS_e,
                P3B6_WU_YL_MSBS_e,
                P3B6_WU_ZH_MSBS_e,
                P3B6_WU_ZL_MSBS_e,
                P3B6_WU_XH_LSBS_e,
                P3B6_WU_XL_LSBS_e,
                P3B6_WU_YH_LSBS_e,
                P3B6_WU_YL_LSBS_e,
                P3B6_WU_PAR_e,
                P3B6_WU_EN_CP_e,
                P3B6_WU_ZH_LSBS_e,
                P3B6_WU_ZL_LSBS_e,
                P3B6_RST_FLG_CLR_e,
                P3B6_SOFT_RST_e,
                P3B6_CHIP_ID_0_e,
                P3B6_CHIP_ID_1_e,
                P3B6_CHIP_ID_2_e,
                P3B6_CHIP_ID_3_e,
                P3B6_CHIP_ID_4_e,
                P3B6_ID_PAR_e,
                P3B6_CHIP_ID_5_e,
                P3B6_CHANNEL_SEL_SAVE_e,
} TLx493D_P3B6_registerNames_te;


typedef enum { 
               P3B6_CRC_REG_e    = 0x08,
               P3B6_DIAG_REG_e   = 0x09,
               P3B6_MOD1_REG_e   = 0x0A,
               P3B6_MOD2_REG_e   = 0x0B,
} TLx493D_P3B6_SpecialRegisters_te;


#endif /** TLX493D_P3B6_ENUMS_H */
