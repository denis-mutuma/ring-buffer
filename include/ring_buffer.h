#include <stdbool.h>

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

// RingBuffer type declaration
typedef struct
{
    size_t head;
    size_t tail;
    size_t capacity;
    size_t length;
    uint8_t *data;
} RingBuffer;

// RingBufferResult is used to check if what was read from the buffer is valid or not when
// the ReadBuffer function is called. It is not used anywhere else.
// If the value is valid, the "value" field is set to the oldest value in the ring
// buffer and the "is_valid" field set to true.
// Otherwise these fields will be set to zero and false respectively if we read from an empty buffer.
// NOTE: You should check if the RingBufferResult is valid in your application before
// using the value after calling ReadBuffer function.
typedef struct
{
    uint8_t value;
    bool is_valid;
} RingBufferResult;

// Function creates a ring buffer on the heap and returns its address.
// The ring buffer data array size is set to the capacity and all otherr fields are initialized to zero.
RingBuffer *CreateRingBuffer(size_t capacity);

// Function to delete a ring buffer from memory.
void DeleteRingBuffer(RingBuffer *buffer);

// Function creates a ring buffer result on the heap and returns its address.
RingBufferResult *CreateRingBufferResult();

// Function deletes a ring buffer result from memory.
void DeleteBufferResult(RingBufferResult *result);

// Function reads a buffer and modifies a result variable of type RingBufferResult.
// The read value is valid if the result->is_valid is true and invalid otherwise.
// If the read is successful, the tail and the length of the buffer are decremented by one.
// NOTE: You should check that the result is valid before using that value as explained above.
void ReadBuffer(RingBuffer *ring_buffer, RingBufferResult *result);

// Function returns true if a write to the buffer is successful and false otherwise.
// If the write is successful, the head pointer and length are incremented by one
// NOTE: The write fails if the buffer is full and the data to be written to the buffer will be lost
bool WriteBuffer(RingBuffer *ring_buffer, uint8_t data);

// Function returns the number of elements in the buffer
// NOTE: The elements may not necessarily start from index 0 of the array
size_t GetBufferLength(RingBuffer *ring_buffer);

// Function returns the index of the tail
size_t GetBufferReadIndex(RingBuffer *ring_buffer);

// Function returns the index of the head
size_t GetBufferWriteIndex(RingBuffer *ring_buffer);

// Function returns true if buffer is full and false otherwise
bool IsBufferFull(RingBuffer *ring_buffer);

// Function returns true if buffer is empty and false otherwise
bool IsBufferEmpty(RingBuffer *ring_buffer);

// resets the head to 0 and tail to 0
// resets all values of the data array to 0
// resets the length of the buffer to 0
void RingBufferReset(RingBuffer *ring_buffer);

#endif