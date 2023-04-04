#include "lib/Unity/src/unity.h"
#include "../include/ring_buffer.h"

void setUp(void) {}

void tearDown(void) {}

void test_CreateRingBuffer(void)
{
    RingBuffer *buffer = CreateRingBuffer(3);
    TEST_ASSERT_NOT_NULL(buffer);
    TEST_ASSERT_EQUAL_INT(buffer->capacity, 3);
    TEST_ASSERT_EQUAL_INT(GetBufferLength(buffer), 0);
    TEST_ASSERT_EQUAL_INT(GetBufferReadIndex(buffer), 0);
    TEST_ASSERT_EQUAL_INT(GetBufferWriteIndex(buffer), 0);
    TEST_ASSERT_FALSE(IsBufferFull(buffer));
    TEST_ASSERT_TRUE(IsBufferEmpty(buffer));

    DeleteRingBuffer(buffer);
}

void test_CreateRingBufferResult(void)
{
    RingBufferResult *result = CreateRingBufferResult();
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(result->value, 0);
    TEST_ASSERT_FALSE(result->is_valid);

    DeleteBufferResult(result);
}

void test_WriteRingBuffer(void)
{
    RingBuffer *buffer = CreateRingBuffer(3);
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 10));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 20));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 30));

    TEST_ASSERT_EQUAL_INT(GetBufferLength(buffer), 3);
    TEST_ASSERT_EQUAL_INT(GetBufferReadIndex(buffer), 0);
    TEST_ASSERT_EQUAL_INT(GetBufferWriteIndex(buffer), 0);
    TEST_ASSERT_FALSE(WriteBuffer(buffer, 40));
    TEST_ASSERT_EQUAL_INT(GetBufferWriteIndex(buffer), 0);
    TEST_ASSERT_EQUAL_INT(GetBufferReadIndex(buffer), 0);
    TEST_ASSERT_TRUE(IsBufferFull(buffer));
    TEST_ASSERT_FALSE(IsBufferEmpty(buffer));

    DeleteRingBuffer(buffer);
}

void test_ReadRingBuffer(void)
{
    RingBuffer *buffer = CreateRingBuffer(3);
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 10));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 20));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 30));

    RingBufferResult *result = CreateRingBufferResult();
    ReadBuffer(buffer, result);
    TEST_ASSERT_TRUE(result->is_valid);
    TEST_ASSERT_EQUAL_INT(result->value, 10);
    TEST_ASSERT_EQUAL_INT(GetBufferLength(buffer), 2);
    TEST_ASSERT_EQUAL_INT(GetBufferReadIndex(buffer), 1);
    TEST_ASSERT_EQUAL_INT(GetBufferWriteIndex(buffer), 0);

    ReadBuffer(buffer, result);
    TEST_ASSERT_TRUE(result->is_valid);
    TEST_ASSERT_EQUAL_INT(result->value, 20);

    ReadBuffer(buffer, result);
    TEST_ASSERT_TRUE(result->is_valid);
    TEST_ASSERT_EQUAL_INT(result->value, 30);

    TEST_ASSERT_EQUAL_INT(GetBufferWriteIndex(buffer), 0);
    TEST_ASSERT_EQUAL_INT(GetBufferReadIndex(buffer), 0);

    TEST_ASSERT_TRUE(IsBufferEmpty(buffer));
    TEST_ASSERT_FALSE(IsBufferFull(buffer));

    ReadBuffer(buffer, result);
    TEST_ASSERT_FALSE(result->is_valid);
    TEST_ASSERT_EQUAL_INT(result->value, 0);

    TEST_ASSERT_TRUE(IsBufferEmpty(buffer));
    TEST_ASSERT_FALSE(IsBufferFull(buffer));

    DeleteRingBuffer(buffer);
    DeleteBufferResult(result);
}

void test_RingBufferReset(void)
{
    RingBuffer *buffer = CreateRingBuffer(3);
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 10));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 20));
    TEST_ASSERT_TRUE(WriteBuffer(buffer, 30));

    RingBufferReset(buffer);

    for (size_t i = 0; i < buffer->capacity; ++i)
    {
        TEST_ASSERT_EQUAL_INT(buffer->data[i], 0);
    }

    DeleteRingBuffer(buffer);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_CreateRingBuffer);
    RUN_TEST(test_WriteRingBuffer);
    RUN_TEST(test_ReadRingBuffer);
    RUN_TEST(test_CreateRingBufferResult);

    return UNITY_END();
}