#include "ring_buffer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 1024
#define OPERATIONS 1000000

int
main(void)
{
    uint32_t *storage =
        malloc(CAPACITY * sizeof(uint32_t));

    if (storage == NULL) {
        printf("Result: FAIL\n");
        return 1;
    }

    anr_ring_buffer_t rb;

    if (!anr_ring_buffer_init(
            &rb,
            storage,
            CAPACITY,
            sizeof(uint32_t))) {

        printf("Result: FAIL\n");
        free(storage);
        return 1;
    }

    uint32_t value;
    uint32_t output;

    for (size_t i = 0; i < OPERATIONS; ++i) {

        value = (uint32_t)i;

        if (!anr_ring_buffer_push(&rb, &value)) {

            if (!anr_ring_buffer_pop(&rb, &output)) {
                printf("Result: FAIL\n");
                free(storage);
                return 1;
            }

            if (!anr_ring_buffer_push(&rb, &value)) {
                printf("Result: FAIL\n");
                free(storage);
                return 1;
            }
        }
    }

    while (!anr_ring_buffer_empty(&rb)) {

        if (!anr_ring_buffer_pop(&rb, &output)) {
            printf("Result: FAIL\n");
            free(storage);
            return 1;
        }
    }

    if (!anr_ring_buffer_empty(&rb)) {
        printf("Result: FAIL\n");
        free(storage);
        return 1;
    }

    printf("=== Ring Buffer Stress Test ===\n");
    printf("Operations: %d\n", OPERATIONS);
    printf("Capacity:   %d\n", CAPACITY);
    printf("Result:     PASS\n");

    free(storage);

    return 0;
}
