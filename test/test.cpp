#include <gtest/gtest.h>

extern "C"
{
#include "../include/ring_buffer.h"
}

TEST(BufferTest, CreateBuffer)
{
    Ring_Buffer *buff = createBuffer(3);
    EXPECT_EQ(buff->isFull, 0);
    EXPECT_EQ(isEmpty(buff), 1);
    EXPECT_EQ(buff->head, 0);
    EXPECT_EQ(buff->tail, 0);
}

TEST(BufferTest, WriteBuffer)
{
    Ring_Buffer *buff = createBuffer(3);
    push(buff, 10);
    push(buff, 20);
    push(buff, 30);
    EXPECT_EQ(isFull(buff), 1);
    EXPECT_EQ(isEmpty(buff), 0);
    EXPECT_EQ(buff->tail, 0);
    EXPECT_EQ(buff->head, 0);
}

TEST(BufferTest, ReadBuffer)
{
    Ring_Buffer *buff = createBuffer(3);
    push(buff, 10);
    push(buff, 20);
    push(buff, 30);
    EXPECT_EQ(isFull(buff), 1);
    EXPECT_EQ(isEmpty(buff), 0);
    EXPECT_EQ(buff->tail, 0);
    EXPECT_EQ(buff->head, 0);

    EXPECT_EQ(pop(buff), 10);
    EXPECT_EQ(buff->tail, 1);
    EXPECT_EQ(isFull(buff), 0);
    EXPECT_EQ(isEmpty(buff), 0);
}

TEST(BufferTest, WriteAfterRead)
{
    Ring_Buffer *buff = createBuffer(3);
    push(buff, 10);
    push(buff, 20);
    push(buff, 30);
    EXPECT_EQ(isFull(buff), 1);
    EXPECT_EQ(isEmpty(buff), 0);
    EXPECT_EQ(buff->tail, 0);
    EXPECT_EQ(buff->head, 0);

    EXPECT_EQ(pop(buff), 10);
    EXPECT_EQ(buff->tail, 1);
    EXPECT_EQ(isFull(buff), 0);
    EXPECT_EQ(isEmpty(buff), 0);

    push(buff, 40);
    EXPECT_EQ(isFull(buff), 1);
    EXPECT_EQ(isEmpty(buff), 0);
    EXPECT_EQ(buff->tail, 1);
    EXPECT_EQ(buff->head, 1);
}

// int main(int argc, char **argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }