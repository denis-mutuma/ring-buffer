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

// RingBufferValue is used to check if what was read from the buffer is valid or not
// when the ReadBuffer function is called. It is not used anywhere else.
// If the value is valid, the "value" field is set to the oldest value in the ring buffer and
// the "is_valid" field set to true.
// Otherwise these fields will be set to zero and false respectively.
// NOTE: You should check if the RingBufferValue is valid or not in your application before
// using the value.
typedef struct
{
    uint8_t value;
    bool is_valid;
} RingBufferValue;

// Function initializes a RingBuffer's fields to the supplied ones and the rest to zero
void InitBuffer(RingBuffer *ring_buffer, uint8_t *data, size_t capacity);

// Modifies a result variable of type RingBufferValue to signify a valid result as described above
// The length of the buffer is decremented by one
// NOTE: You should check that the result is valid before using that value
void ReadBuffer(RingBuffer *ring_buffer, RingBufferValue *result);

// Function returns true if a write to the buffer is successful and false otherwise
// The write fails is the buffer is full and the data to be written to the buffer is lost
// If the write is successful, the head pointer and length are incremented by one
bool WriteBuffer(RingBuffer *ring_buffer, const uint8_t data);

// returns the number of elements in the buffer
// NOTE: The elements may not necessarily start from index 0 of the array
size_t GetBufferLength(const RingBuffer *ring_buffer);

// returns the index of the tail
size_t GetReadIndex(const RingBuffer *ring_buffer);

// returns the index of the head
size_t GetWriteIndex(const RingBuffer *ring_buffer);

// returns true if buffer is full and false otherwise
bool IsBufferFull(const RingBuffer *ring_buffer);

// returns true if buffer is empty and false otherwise
bool IsBufferEmpty(const RingBuffer *ring_buffer);

// resets the head to 0 and tail to 0
// resets all values of the data array to 0
// resets the length of the buffer to 0
void Reset(RingBuffer *ring_buffer);

#endif