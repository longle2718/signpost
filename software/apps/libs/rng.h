#pragma once

#define DRIVER_NUM_RNG 111


int rng_set_callback(subscribe_cb callback, void* callback_args);
int rng_set_buffer(uint8_t* buffer, uint32_t len);
int rng_async(uint8_t* buf, uint32_t buflen, uint32_t num);
int rng_sync(uint8_t* buf, uint32_t buflen, uint32_t num);
