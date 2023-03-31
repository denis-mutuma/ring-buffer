#include <stdint.h>
#include <stdlib.h>
#include "../include/ring_buffer.h"

Ring_Buffer *createBuffer(const uint32_t size)
{
    Ring_Buffer *ring_buffer = (Ring_Buffer *)malloc(sizeof(Ring_Buffer) + size * sizeof(uint32_t));
    if (ring_buffer == NULL)
    {
        return NULL;
    }
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    ring_buffer->size = size;
    ring_buffer->isFull = 0;
    return ring_buffer;
}

uint32_t push(Ring_Buffer *_this, uint32_t data)
{
    if (isFull(_this))
    {
        return -1;
    }
    _this->Buffer[_this->head] = data;
    _this->head = (_this->head + 1) % _this->size;
    if (_this->head == _this->tail)
    {
        _this->isFull = 1;
    }
    return 0;
}

uint32_t pop(Ring_Buffer *_this)
{
    if (isEmpty(_this))
    {
        return -1;
    }
    uint32_t val = _this->Buffer[_this->tail];
    _this->tail = (_this->tail + 1) % _this->size;
    _this->isFull = 0;
    return val;
}

uint32_t isFull(Ring_Buffer *_this)
{
    return _this->isFull;
}

uint32_t isEmpty(Ring_Buffer *_this)
{
    uint32_t temp = 0;
    if (_this->head == _this->tail && !isFull(_this))
    {
        temp = 1;
    }
    return temp;
}