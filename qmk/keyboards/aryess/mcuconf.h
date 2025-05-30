#pragma once
#include_next <mcuconf.h>

// Enable only I2C0
#undef  RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
#undef  RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE
