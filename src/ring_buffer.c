#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/ring_buffer.h"

void InitBuffer(RingBuffer *ring_buffer, uint8_t *data, size_t capacity)
{
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    ring_buffer->capacity = capacity;
    ring_buffer->length = 0;
    ring_buffer->data = data;
    return;
}

void ReadBuffer(RingBuffer *_this, RingBufferValue *result)
{
    if (IsBufferEmpty(_this))
    {
        result->value = 0;
        result->is_valid = false;
        return;
    }
    result->value = _this->data[_this->tail];
    result->is_valid = true;
    _this->tail = (_this->tail + 1) % _this->capacity;
    _this->length--;
    return;
}

bool WriteBuffer(RingBuffer *_this, const uint8_t data)
{
    if (IsBufferFull(_this))
    {
        return false;
    }
    _this->data[_this->head] = data;
    _this->length++;
    if (IsBufferFull(_this))
    {
        return true;
    }
    _this->head = (_this->head + 1) % _this->capacity;

    return true;
}

size_t GetBufferLength(const RingBuffer *ring_buffer)
{
    return ring_buffer->length;
}

size_t GetReadIndex(const RingBuffer *ring_buffer)
{
    return ring_buffer->tail;
}

size_t GetWriteIndex(const RingBuffer *ring_buffer)
{
    return ring_buffer->head;
}

bool IsBufferFull(const RingBuffer *_this)
{
    return _this->length == _this->capacity;
}

bool IsBufferEmpty(const RingBuffer *_this)
{
    return _this->head == _this->tail;
}

void Reset(RingBuffer *ring_buffer)
{
    for (size_t i = 0; i < ring_buffer->capacity; i++)
    {
        ring_buffer->data[i] = 0;
    }
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    ring_buffer->length = 0;
}