#include "ring_buffer.h"

#include <string.h>


/*
 * Check whether a value is a power of two.
 *
 * Valid values:
 *
 *     1, 2, 4, 8, 16, ...
 *
 * This property allows the ring-buffer index to use
 * a bitwise mask instead of modulo division.
 */
static bool
anr_ring_buffer_is_power_of_two(size_t value)
{
    return value != 0 &&
           (value & (value - 1)) == 0;
}


/*
 * Calculate the physical position inside the ring buffer.
 *
 * Because capacity is guaranteed to be a power of two,
 *
 *     position % capacity
 *
 * is equivalent to:
 *
 *     position & (capacity - 1)
 *
 * This avoids modulo arithmetic in the hot path.
 */
static size_t
anr_ring_buffer_index(
    const anr_ring_buffer_t *rb,
    size_t position)
{
    return position & (rb->capacity - 1);
}


bool
anr_ring_buffer_init(
    anr_ring_buffer_t *rb,
    void *memory,
    size_t capacity,
    size_t element_size
)
{
    if (rb == NULL)
        return false;

    if (memory == NULL)
        return false;

    if (!anr_ring_buffer_is_power_of_two(capacity))
        return false;

    if (element_size == 0)
        return false;

    rb->data = (uint8_t *)memory;

    rb->element_size = element_size;
    rb->capacity = capacity;

    rb->head = 0;
    rb->tail = 0;

    return true;
}


void
anr_ring_buffer_reset(anr_ring_buffer_t *rb)
{
    if (rb == NULL)
        return;

    rb->head = 0;
    rb->tail = 0;
}


bool
anr_ring_buffer_empty(const anr_ring_buffer_t *rb)
{
    if (rb == NULL)
        return true;

    return rb->head == rb->tail;
}


bool
anr_ring_buffer_full(const anr_ring_buffer_t *rb)
{
    if (rb == NULL)
        return false;

    return (rb->head - rb->tail) >= rb->capacity;
}


size_t
anr_ring_buffer_size(const anr_ring_buffer_t *rb)
{
    if (rb == NULL)
        return 0;

    return rb->head - rb->tail;
}


size_t
anr_ring_buffer_capacity(const anr_ring_buffer_t *rb)
{
    if (rb == NULL)
        return 0;

    return rb->capacity;
}


bool
anr_ring_buffer_push(
    anr_ring_buffer_t *rb,
    const void *element
)
{
    if (rb == NULL || element == NULL)
        return false;

    if (anr_ring_buffer_full(rb))
        return false;

    size_t index =
        anr_ring_buffer_index(rb, rb->head);

    uint8_t *destination =
        rb->data + (index * rb->element_size);

    memcpy(
        destination,
        element,
        rb->element_size
    );

    rb->head++;

    return true;
}


bool
anr_ring_buffer_pop(
    anr_ring_buffer_t *rb,
    void *element
)
{
    if (rb == NULL || element == NULL)
        return false;

    if (anr_ring_buffer_empty(rb))
        return false;

    size_t index =
        anr_ring_buffer_index(rb, rb->tail);

    uint8_t *source =
        rb->data + (index * rb->element_size);

    memcpy(
        element,
        source,
        rb->element_size
    );

    rb->tail++;

    return true;
}


void *
anr_ring_buffer_peek(
    anr_ring_buffer_t *rb
)
{
    if (rb == NULL)
        return NULL;

    if (anr_ring_buffer_empty(rb))
        return NULL;

    size_t index =
        anr_ring_buffer_index(rb, rb->tail);

    return rb->data +
           (index * rb->element_size);
}
