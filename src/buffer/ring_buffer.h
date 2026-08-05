#ifndef ANR_RING_BUFFER_H
#define ANR_RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Single Producer / Single Consumer ring buffer.
 *
 * The buffer stores fixed-size elements in a pre-allocated
 * memory region.
 *
 * Producer:
 *   - writes elements
 *   - advances the write position
 *
 * Consumer:
 *   - reads elements
 *   - advances the read position
 *
 * The implementation does not allocate memory internally.
 *
 * Capacity must be a power of two.
 */

typedef struct {
    uint8_t *data;

    size_t element_size;
    size_t capacity;

    /*
     * Positions are monotonically increasing counters.
     *
     * The physical position inside the buffer is calculated
     * using a bitwise mask because capacity is required to be
     * a power of two:
     *
     *     position & (capacity - 1)
     *
     * This is equivalent to position % capacity for
     * power-of-two capacities.
     *
     * Using monotonically increasing counters instead of
     * directly wrapping indices makes full/empty detection
     * explicit.
     */
    size_t head;
    size_t tail;
} anr_ring_buffer_t;


/*
 * Initialize a ring buffer over an existing memory region.
 *
 * memory:
 *     Pre-allocated storage for the buffer.
 *
 * capacity:
 *     Number of elements that can be stored.
 *
 *     Must be a power of two.
 *
 * element_size:
 *     Size of one element in bytes.
 *
 * Returns:
 *     true  - initialization succeeded.
 *     false - invalid parameters.
 */
bool anr_ring_buffer_init(
    anr_ring_buffer_t *rb,
    void *memory,
    size_t capacity,
    size_t element_size
);


/*
 * Reset the ring buffer.
 *
 * Existing data is considered consumed.
 * The underlying memory is not cleared.
 */
void anr_ring_buffer_reset(anr_ring_buffer_t *rb);


/*
 * Check whether the buffer is empty.
 */
bool anr_ring_buffer_empty(const anr_ring_buffer_t *rb);


/*
 * Check whether the buffer is full.
 */
bool anr_ring_buffer_full(const anr_ring_buffer_t *rb);


/*
 * Return the number of elements currently stored.
 */
size_t anr_ring_buffer_size(const anr_ring_buffer_t *rb);


/*
 * Return the maximum number of elements the buffer can store.
 */
size_t anr_ring_buffer_capacity(const anr_ring_buffer_t *rb);


/*
 * Write one element into the buffer.
 *
 * Returns false if the buffer is full.
 */
bool anr_ring_buffer_push(
    anr_ring_buffer_t *rb,
    const void *element
);


/*
 * Read one element from the buffer.
 *
 * Returns false if the buffer is empty.
 */
bool anr_ring_buffer_pop(
    anr_ring_buffer_t *rb,
    void *element
);


/*
 * Return a pointer to the next element without removing it.
 *
 * Returns NULL if the buffer is empty.
 */
void *anr_ring_buffer_peek(
    anr_ring_buffer_t *rb
);

#ifdef __cplusplus
}
#endif

#endif /* ANR_RING_BUFFER_H */
