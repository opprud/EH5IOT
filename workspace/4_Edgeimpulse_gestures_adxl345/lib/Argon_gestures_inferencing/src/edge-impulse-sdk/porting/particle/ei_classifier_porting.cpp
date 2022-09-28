#include "../ei_classifier_porting.h"
#if EI_PORTING_PARTICLE == 1

#include "Particle.h"
//#include <stdarg.h>
//#include <stdlib.h>

#define EI_WEAK_FN __attribute__((weak))

EI_WEAK_FN EI_IMPULSE_ERROR ei_run_impulse_check_canceled() {
    return EI_IMPULSE_OK;
}

EI_WEAK_FN EI_IMPULSE_ERROR ei_sleep(int32_t time_ms) {
    delay(time_ms);
    return EI_IMPULSE_OK;
}

uint64_t ei_read_timer_ms() {
    return millis();
}

uint64_t ei_read_timer_us() {
    return micros();
}

void ei_serial_set_baudrate(int baudrate)
{

}

/**
 *  Printf function uses vsnprintf and output using Arduino Serial
 */
void ei_printf(const char *format, ...) {
    static char print_buf[1024] = { 0 };

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);

    if (r > 0) {
        Serial.write(print_buf);
    }
}

void ei_printf_float(float f) {
    ei_printf("%f", f);
}

void *ei_malloc(size_t size) {
    return malloc(size);
}

void *ei_calloc(size_t nitems, size_t size) {
    return calloc(nitems, size);
}

void ei_free(void *ptr) {
    free(ptr);
}

#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C"
#endif
void DebugLog(const char* s) {
    ei_printf("%s", s);
}
#endif
