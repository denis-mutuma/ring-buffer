#include <gtest/gtest.h>

extern "C"
{
#include "../include/ring_buffer.h"
}

class RingBufferTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        InitBuffer(&buffer, data, 3);
    }

    // void TearDown() override {}

    RingBuffer buffer;
    RingBufferValue result;
    uint8_t data[3];
};

TEST_F(RingBufferTest, TestInitBuffer)
{
    ReadBuffer(&buffer, &result);
    EXPECT_EQ(result.is_valid, false);
    EXPECT_EQ(result.value, 0);
    EXPECT_EQ(IsBufferFull(&buffer), false);
    EXPECT_EQ(IsBufferEmpty(&buffer), true);
    EXPECT_EQ(GetBufferLength(&buffer), 0);
    EXPECT_EQ(GetReadIndex(&buffer), 0);
    EXPECT_EQ(GetWriteIndex(&buffer), 0);
    EXPECT_EQ(buffer.head, 0);
    EXPECT_EQ(buffer.tail, 0);
}

TEST_F(RingBufferTest, TestWriteBuffer)
{
    EXPECT_EQ(WriteBuffer(&buffer, 10), true);
    EXPECT_EQ(WriteBuffer(&buffer, 20), true);
    EXPECT_EQ(WriteBuffer(&buffer, 30), true);
    EXPECT_EQ(GetBufferLength(&buffer), 3);
    EXPECT_EQ(GetReadIndex(&buffer), 0);
    EXPECT_EQ(GetWriteIndex(&buffer), 2);
    EXPECT_EQ(WriteBuffer(&buffer, 40), false);
    EXPECT_EQ(GetWriteIndex(&buffer), 2);
    EXPECT_EQ(IsBufferFull(&buffer), true);
    EXPECT_EQ(IsBufferEmpty(&buffer), false);
}

TEST_F(RingBufferTest, TestReadBuffer)
{
    ReadBuffer(&buffer, &result);
    EXPECT_EQ(result.is_valid, true);
    EXPECT_EQ(result.value, 10);
    EXPECT_EQ(GetBufferLength(&buffer), 2);
    EXPECT_EQ(GetReadIndex(&buffer), 1);
    EXPECT_EQ(GetWriteIndex(&buffer), 2);

    ReadBuffer(&buffer, &result);
    EXPECT_EQ(result.is_valid, true);
    EXPECT_EQ(result.value, 20);

    ReadBuffer(&buffer, &result);
    EXPECT_EQ(result.is_valid, true);
    EXPECT_EQ(result.value, 30);

    EXPECT_EQ(IsBufferEmpty(&buffer), true);
    EXPECT_EQ(IsBufferFull(&buffer), false);

    ReadBuffer(&buffer, &result);
    EXPECT_EQ(result.is_valid, false);
    EXPECT_EQ(result.value, 0);

    EXPECT_EQ(IsBufferEmpty(&buffer), true);
    EXPECT_EQ(IsBufferFull(&buffer), false);
}