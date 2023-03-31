#ifndef RING_BUFFER_H
#define RING_BUFFER_H

typedef struct
{
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t isFull;
    uint32_t Buffer[];
} Ring_Buffer;

Ring_Buffer *createBuffer(uint32_t size);
uint32_t push(Ring_Buffer *ring_buffer, uint32_t data);
uint32_t pop(Ring_Buffer *ring_buffer);
uint32_t isFull(Ring_Buffer *ring_buffer);
uint32_t isEmpty(Ring_Buffer *ring_buffer);

#endif