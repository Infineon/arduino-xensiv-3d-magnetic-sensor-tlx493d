#ifndef TLx493D_A1B6_DEFINES_H
#define TLx493D_A1B6_DEFINES_H


#define GEN_1_WRITE_REGISTERS_MAX_COUNT             4

#define GEN_1_REG_MAP_SIZE                          14

#define GEN_1_READ_REGISTERS_MAX_COUNT              10 

#define GEN_1_WRITE_REGISTERS_OFFSET                10

/** General defines. */
#define GEN_1_TEMP_MULT                             1.10
#define GEN_1_TEMP_OFFSET                           340.0
#define GEN_1_REF_TEMP                              25.0

#define GEN_1_MAG_FIELD_MULT                        0.098

#define GEN_1_STD_IIC_ADDR                          0xBC

/** Addresses for generation 1. */
/** (A0-A3 - for SDA/ADDR high at power-up). */
/** (A4-A7 - for SDA/ADDR low at power-up). */

/** A0 */
#define GEN_1_STD_IIC_ADDR_WRITE_A0                 0xBC

/** A1 */
#define GEN_1_STD_IIC_ADDR_WRITE_A1                 0xB4

/** A2 */
#define GEN_1_STD_IIC_ADDR_WRITE_A2                 0x9C

/** A3 */
#define GEN_1_STD_IIC_ADDR_WRITE_A3                 0x94

/** A4 */
#define GEN_1_STD_IIC_ADDR_WRITE_A4                 0x3E

/** A5 */
#define GEN_1_STD_IIC_ADDR_WRITE_A5                 0x36

/** A6 */
#define GEN_1_STD_IIC_ADDR_WRITE_A6                 0x1E

/** A7 */
#define GEN_1_STD_IIC_ADDR_WRITE_A7                 0x16


#define GEN_1_BITFIELDS_COUNT                       28


#define TLX493D_A1B6_REGISTER_HEADLINE   "      Bx      By      Bz    Temp     Bx2     Bz2   Temp2     FS1     FS2     FS3    Res.    MOD1    Res.    MOD2\n\
----------------------------------------------------------------------------------------------------------------"


#endif /** TLx493D_A1B6_DEFINES_H */
