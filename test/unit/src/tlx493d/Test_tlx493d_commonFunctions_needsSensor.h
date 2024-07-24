#ifndef TEST_TLX493D_COMMON_FUNCTIONS_NEEDS_SENSOR_H
#define TEST_TLX493D_COMMON_FUNCTIONS_NEEDS_SENSOR_H


// test includes
#include "Test_includes.h"


// Variables used in the tests below that have to be accessed in the setup and tear down methods.
// The "dut" variable is taken from the respective sensor that the common functions are applied to.


// define test group name
TEST_GROUP(SensorsCommonFunctions);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(SensorsCommonFunctions)
{
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(SensorsCommonFunctions)
{
}


TEST_IFX(SensorsCommonFunctions, checkGetMagneticFieldAndTemperature)
{
    double  x, y, z, t;

    TEST_ASSERT_TRUE( tlx493d_common_getTemperature(&dut, &t) );
    TEST_ASSERT_FLOAT_WITHIN( 20.0, 25.0, t );

    tlx493d_common_getMagneticField(&dut, &x, &y, &z);
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, x );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, y );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, z );

    x = 0.0;
    y = 0.0;
    z = 0.0;
    t = 0.0;
    tlx493d_common_getMagneticFieldAndTemperature(&dut, &x, &y, &z, &t);
    TEST_ASSERT_FLOAT_WITHIN( 20.0, 25.0, t );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, x );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, y );
    TEST_ASSERT_FLOAT_WITHIN( 100.0, 0.0, z );
}


// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(SensorsCommonFunctions)
{
    RUN_TEST_CASE(SensorsCommonFunctions, checkGetMagneticFieldAndTemperature);
}


#endif // TEST_TLX493D_COMMON_FUNCTIONS_NEEDS_SENSOR_H
