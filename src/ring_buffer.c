#include "ring_buffer.h"

#include <string.h>


static size_t
anr_ring_buffer_index(const anr_ring_buffer_t *rb, size_t position)
{
    return position % rb->capacity;
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

    if (capacity == 0)
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

    size_t index = anr_ring_buffer_index(rb, rb->head);

    uint8_t *destination =
        rb->data + (index * rb->element_size);

    memcpy(destination, element, rb->element_size);

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

    size_t index = anr_ring_buffer_index(rb, rb->tail);

    uint8_t *source =
        rb->data + (index * rb->element_size);

    memcpy(element, source, rb->element_size);

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

    size_t index = anr_ring_buffer_index(rb, rb->tail);

    return rb->data + (index * rb->element_size);
}
