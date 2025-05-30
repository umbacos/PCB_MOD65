#if defined(RAW_ENABLE)
#include QMK_KEYBOARD_H
#include "raw_hid.h"

// #define RAW_BUFFER_SIZE 32

// void raw_hid_receive(uint8_t *data, uint8_t length) {
//   if (memcmp(data, "hello", 5) == 0) {
//     // Reply with "world"
//     uint8_t buff[RAW_BUFFER_SIZE] = {0};
//     memcpy(buff, "world", 5); // +1 for report ID
//     raw_hid_send(buff, RAW_BUFFER_SIZE);
//   }
// }

void raw_hid_receive(uint8_t *data, uint8_t length) {
  raw_hid_send(data, length);
}

#endif
