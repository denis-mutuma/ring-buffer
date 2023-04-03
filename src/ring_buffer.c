#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/ring_buffer.h"

RingBuffer *CreateRingBuffer(size_t capacity)
{
    RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
    buffer->data = malloc(sizeof(uint8_t) * capacity);

    buffer->head = 0;
    buffer->tail = 0;
    buffer->capacity = capacity;
    buffer->length = 0;

    return buffer;
}

void DeleteRingBuffer(RingBuffer *buffer)
{
    if (!buffer)
    {
        return;
    }
    free(buffer->data);
    buffer->data = NULL;
    free(buffer);
    buffer = NULL;
}

RingBufferResult *CreateRingBufferResult()
{
    RingBufferResult *result = (RingBufferResult *)malloc(sizeof(RingBufferResult));
    result->is_valid = false;
    result->value = 0;
    return result;
}

void DeleteBufferResult(RingBufferResult *result)
{
    if (!result)
    {
        return;
    }
    free(result);
    result = NULL;
}

void ReadBuffer(RingBuffer *_this, RingBufferResult *result)
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

bool WriteBuffer(RingBuffer *_this, uint8_t data)
{
    if (IsBufferFull(_this))
    {
        return false;
    }
    _this->data[_this->head] = data;
    _this->length++;
    _this->head = (_this->head + 1) % _this->capacity;

    return true;
}

size_t GetBufferLength(RingBuffer *ring_buffer)
{
    return ring_buffer->length;
}

size_t GetBufferReadIndex(RingBuffer *ring_buffer)
{
    return ring_buffer->tail;
}

size_t GetBufferWriteIndex(RingBuffer *ring_buffer)
{
    return ring_buffer->head;
}

bool IsBufferFull(RingBuffer *_this)
{
    return (_this->head == _this->tail && _this->length > 0);
}

bool IsBufferEmpty(RingBuffer *_this)
{
    return (_this->head == _this->tail && _this->length == 0);
}

void RingBufferReset(RingBuffer *ring_buffer)
{
    for (size_t i = 0; i < ring_buffer->capacity; ++i)
    {
        ring_buffer->data[i] = 0;
    }
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    ring_buffer->length = 0;
}