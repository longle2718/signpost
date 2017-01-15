#include <tock.h>
#include <rng.h>

struct rng_data {
  bool fired;
  uint32_t num_read;
};

struct rng_data result = { .fired = false };

// Internal callback for faking synchronous reads
static void rng_cb(__attribute__ ((unused)) int callback_type,
                   __attribute__ ((unused)) int val1,
                   int num_read,
                   void* ud) {
  struct rng_data* result = (struct rng_data*) ud;
  result->num_read = num_read;
  result->fired = true;
}

int rng_set_buffer(uint8_t* buffer, uint32_t len) {
    return allow(DRIVER_NUM_RNG, 0, (void*) buffer, len);
}

int rng_set_callback (subscribe_cb callback, void* callback_args) {
    return subscribe(DRIVER_NUM_RNG, 0, callback, callback_args);
}

int rng_async(uint8_t* buf, uint32_t buflen, uint32_t num) {
    int err;

    err = rng_set_buffer(buf, buflen);

    return command(DRIVER_NUM_RNG, 0, num);
}

int rng_sync(uint8_t* buf, uint32_t buflen, uint32_t num) {
    int err;

    err = rng_set_buffer(buf, buflen);

    err = rng_set_callback(rng_cb, (void*) &result);
    if (err < 0) return err;

    printf("before\n");
    err = command(DRIVER_NUM_RNG, 0, num);
    printf("after\n");
    if (err < 0) return err;

    printf("yeilding\n");
    //yield_for(&result.fired);

    return result.num_read;
}
