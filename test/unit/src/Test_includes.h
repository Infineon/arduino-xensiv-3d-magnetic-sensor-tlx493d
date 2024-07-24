#ifndef TEST_INCLUDES_H
#define TEST_INCLUDES_H


// std includes
#include <stdbool.h>

// project c includes
#include "CommunicationInterface.h"
#include "Logger.h"

// common to all sensors
#include "tlx493d.h"
#include "tlx493d_types.h"
#include "tlx493d_common_defines.h"
#include "tlx493d_common.h"

// common to same generation of sensors
#include "tlx493d_gen_2_common_defines.h"
#include "tlx493d_gen_2_common.h"

#include "tlx493d_gen_3_common_defines.h"
#include "tlx493d_gen_3_common.h"

// Unity c includes
#include "unity.h"
#include "unity_fixture.h"

// IFX addons
#include "unity_ifx.h"


#endif // TEST_INCLUDES_H