#pragma once

#include QMK_KEYBOARD_H

void pomodoro_init(void);
void pomodoro_start(void);
void pomodoro_reset(void);
void pomodoro_update(void);
bool pomodoro_is_active(void);
bool pomodoro_is_paused(void);
const char* pomodoro_get_status(void);
