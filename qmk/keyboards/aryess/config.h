#pragma once

// Layers
#define MAC 0
#define WIN 1
#define FN1 2
#define FN2 3

// OLED pins
#define I2C_DRIVER I2CD0 // i2c0, require mcuconf.h
#define I2C1_SDA_PIN GP24
#define I2C1_SCL_PIN GP25

// OLED config
#define OLED_TIMEOUT 600000 // 10 minutes

// Lighting layers
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYER_BLINK
// #define RGB_MATRIX_DISABLE_SHARED_KEYCODES

// Custom features
#define TOGGLE_SWITCH
#define POMODORO
