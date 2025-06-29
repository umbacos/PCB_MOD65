#if defined(POMODORO)
#include "pomodoro.h"
#include "timer.h"
#include "rgblight.h"

#define POMODORO_WORK_DURATION_MS    25 * 60 * 1000 // 25 min
#define POMODORO_SHORT_BREAK_MS       5 * 60 * 1000 //  5 min
#define POMODORO_LONG_BREAK_MS       15 * 60 * 1000 // 15 min
#define POMODORO_LEDS_REFRESH_MS     500
#define POMODORO_CYCLES_BEFORE_LONG  4
#define POMODORO_FLASH_COUNT         5
#define POMODORO_FLASH_BLINK_MS      150
#define POMODORO_FLASH_BRIGHTNESS    255
#define POMODORO_PROGRESS_BRIGHTNESS 1

typedef enum {
  POMODORO_IDLE,
  POMODORO_WORK,
  POMODORO_BREAK_SHORT,
  POMODORO_BREAK_LONG,
  POMODORO_PAUSED
} pomodoro_state_t;

static pomodoro_state_t pomodoro_state = POMODORO_IDLE;
static pomodoro_state_t last_active_state = POMODORO_IDLE;
static uint32_t pomodoro_start_time = 0;
static uint32_t paused_elapsed = 0;
static uint8_t pomodoro_cycle_count = 0;

// Lighting Layer

enum pomodoro_layer_ids {
  POMODORO_PROGRESS_LAYER,
  POMODORO_FLASH_LAYER
};

static rgblight_segment_t pomodoro_progress_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLIGHT_LED_COUNT, HSV_OFF});
static rgblight_segment_t pomodoro_flash_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLIGHT_LED_COUNT, HSV_OFF});

const rgblight_segment_t* const PROGMEM pomodoro_layers[] = RGBLIGHT_LAYERS_LIST(
  pomodoro_progress_layer,
  pomodoro_flash_layer
);

// Flash notification

static void flash(uint8_t h, uint8_t s, uint8_t v) {
  pomodoro_flash_layer[0].hue = h;
  pomodoro_flash_layer[0].sat = s;
  pomodoro_flash_layer[0].val = POMODORO_FLASH_BRIGHTNESS;
  rgblight_blink_layer_repeat(POMODORO_FLASH_LAYER, POMODORO_FLASH_BLINK_MS, POMODORO_FLASH_COUNT);
}

// Progress bar

static void progress_update_leds(uint32_t elapsed, uint32_t duration, uint8_t h, uint8_t s, uint8_t v) {
  // Throttle updates to at most once per 1000 ms
  static uint32_t last_update = 0;
  if (timer_elapsed32(last_update) < POMODORO_LEDS_REFRESH_MS) {
    return;
  }
  last_update = timer_read32();
  uint8_t progress = (elapsed * RGBLIGHT_LED_COUNT) / duration;
  // pomodoro_progress_layer[0].index = 0;
  pomodoro_progress_layer[0].count = progress == 0 ? 1 : progress;
  pomodoro_progress_layer[0].hue = h;
  pomodoro_progress_layer[0].sat = s;
  pomodoro_progress_layer[0].val = POMODORO_PROGRESS_BRIGHTNESS;
  rgblight_set_layer_state(POMODORO_PROGRESS_LAYER, true);
}

// Public API

void pomodoro_init(void) {
  rgblight_layers = pomodoro_layers;
}

void pomodoro_start(void) {
  if (pomodoro_state == POMODORO_IDLE) {
    pomodoro_state = POMODORO_WORK;
    pomodoro_start_time = timer_read32();
    rgblight_disable_noeeprom();
  } else if (pomodoro_state == POMODORO_PAUSED) {
    pomodoro_state = last_active_state;
    pomodoro_start_time = timer_read32() - paused_elapsed;
  } else {
    last_active_state = pomodoro_state;
    paused_elapsed = timer_elapsed32(pomodoro_start_time);
    pomodoro_state = POMODORO_PAUSED;
  }
}

void pomodoro_reset(void) {
  pomodoro_state = POMODORO_IDLE;
  pomodoro_cycle_count = 0;
  rgblight_enable_noeeprom();
  rgblight_set_layer_state(POMODORO_PROGRESS_LAYER, false);
  rgblight_set_layer_state(POMODORO_FLASH_LAYER, false);
}

void pomodoro_update(void) {
  if (pomodoro_state == POMODORO_IDLE || pomodoro_state == POMODORO_PAUSED) return;

  uint32_t elapsed = timer_elapsed32(pomodoro_start_time);

  switch (pomodoro_state) {
    case POMODORO_WORK:
      progress_update_leds(elapsed, POMODORO_WORK_DURATION_MS, HSV_RED);
      if (elapsed >= POMODORO_WORK_DURATION_MS) {
        pomodoro_state = (pomodoro_cycle_count+1 == POMODORO_CYCLES_BEFORE_LONG) ? POMODORO_BREAK_LONG : POMODORO_BREAK_SHORT;
        pomodoro_start_time = timer_read32();
        flash(HSV_GREEN);
      }
      break;
    case POMODORO_BREAK_SHORT:
      progress_update_leds(elapsed, POMODORO_SHORT_BREAK_MS, HSV_GREEN);
      if (elapsed >= POMODORO_SHORT_BREAK_MS) {
        pomodoro_state = POMODORO_WORK;
        pomodoro_cycle_count++;
        pomodoro_start_time = timer_read32();
        flash(HSV_RED);
      }
      break;
    case POMODORO_BREAK_LONG:
      progress_update_leds(elapsed, POMODORO_LONG_BREAK_MS, HSV_GREEN);
      if (elapsed >= POMODORO_LONG_BREAK_MS) {
        pomodoro_state = POMODORO_WORK;
        pomodoro_cycle_count = 0;
        pomodoro_start_time = timer_read32();
        flash(HSV_RED);
      }
      break;
    default:
      break;
  }
}

bool pomodoro_is_active(void) {
  return pomodoro_state != POMODORO_IDLE && pomodoro_state != POMODORO_PAUSED;
}

bool pomodoro_is_paused(void) {
  return pomodoro_state == POMODORO_PAUSED;
}

const char* pomodoro_get_status(void) {
  if (pomodoro_state == POMODORO_IDLE) {
    return "OFF";
  }

  if (pomodoro_state == POMODORO_PAUSED) {
    return "PAUSE";
  }

  uint32_t elapsed = timer_elapsed32(pomodoro_start_time);
  uint32_t duration = 0;

  switch (pomodoro_state) {
    case POMODORO_WORK: duration = POMODORO_WORK_DURATION_MS; break;
    case POMODORO_BREAK_SHORT: duration = POMODORO_SHORT_BREAK_MS; break;
    case POMODORO_BREAK_LONG: duration = POMODORO_LONG_BREAK_MS; break;
    default: return "?";
  }

  static char buffer[16];
  uint32_t remaining = (elapsed < duration) ? (duration - elapsed) / 1000 : 0;
  uint8_t min = remaining / 60;
  uint8_t sec = remaining % 60;

  snprintf(buffer, sizeof(buffer), "%02d:%02d(%d)", min, sec, pomodoro_cycle_count+1);
  return buffer;
}

#endif
