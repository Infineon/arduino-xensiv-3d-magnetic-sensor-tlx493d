#ifndef TEST_TLX493D_GEN_2_COMMON_H
#define TEST_TLX493D_GEN_2_COMMON_H


// std includes
#include <string.h>

// test includes
#include "Test_includes.h"


// Variables used in the tests below that have to be accessed in the setup and tear down methods.
// The "dut" variable is taken from the respective sensor that the common functions are applied to.


// define test group name
TEST_GROUP(SensorsGen2Common);


// // Setup method called before every individual test defined for this test group
// static TEST_SETUP(SensorsGen2Common)
// {
// }


// // Tear down method called before every individual test defined for this test group
// static TEST_TEAR_DOWN(SensorsGen2Common)
// {
// }


// TEST_IFX(SensorsGen2Common, checkCalculateMagneticFieldAndTemperature)
// {
//     // double temperature = 0.0;
//     // tlx493d_gen_2_calculateTemperature(&dut, &temperature);
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, -GEN_2_TEMP_OFFSET * GEN_2_TEMP_MULT + GEN_2_TEMP_REF, temperature );

//     // double x = 0.0, y = 0.0, z = 0.0;
//     // tlx493d_gen_2_calculateMagneticField(&dut, &x, &y, &z);
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, x );
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, y );
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, z );

//     // temperature = 0.0;
//     // x = 0.0;
//     // y = 0.0;
//     // z = 0.0;
//     // dut.functions->calculateMagneticFieldAndTemperature(&dut, &x, &y, &z, &temperature);
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, -GEN_2_TEMP_OFFSET * GEN_2_TEMP_MULT + GEN_2_TEMP_REF, temperature );
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, x );
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, y );
//     // TEST_ASSERT_FLOAT_WITHIN( 1.0, 0.0, z );
// }


// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(SensorsGen2Common)
{
    // RUN_TEST_CASE(SensorsGen2Common, checkCalculateMagneticFieldAndTemperature);
}


#endif // TEST_TLX493D_GEN_2_COMMON_H
