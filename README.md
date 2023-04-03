# Ring Buffer

# About the project

This project presents a ring buffer library which can be used to create an instance of a fixed-size buffer as if it were connected end-to-end. Elements are accessed in the order in which they were inserted into the buffer.

The buffer utilizes a first-in first-out (FIFO) approach similar to that of a queue data structure. The underlying implementation for the ring buffer is an array and elements are inserted at the front and accessed from the back.

This buffer is designed for use in microcontrollers but can be modified for use as explained [here](#usage).

> **Note:** If the buffer is full, any elements added to the buffer will be discarded.

## Built with:
 - C
 - CMake

# Getting Started

## Prerequisites  

- `C` compiler

## Installation
1. Clone the repo with
```
git clone https://github.com/denis-mutuma/ring-buffer.git
```

2. In the project folder:
   -  `cd build`
   -  `cmake ..`
   -  `cmake --build .`

3. If you make changes to the source code, write custom unit tests, repeat step 2 and run the tests with by running the executable `RingBuffer` in the `build` folder. In this project, the [Unity](https://github.com/ThrowTheSwitch/Unity) testing framework was used. You can download it and uzip it in the `test/lib/Unity` folder.

# Usage

```
// Create a ring buffer of a specified size e.g., 128
RingBuffer *buffer = CreateRingBuffer(128);

// Create a ring buffer result
RingBufferResult *result = CreateRingBufferResult();

// Insert elements to the buffer
// If buffer is full, WriteBuffer will return false and the data to be written is discarded

uint_8 my_data[data_size];
for(int i = 0; i < data_size; i++) {
    if(!WriteBuffer(buffer, some_value)){
        // print an error or handle the failure by terminating the write
    }
}

// Read from the buffer
ReadBuffer(buffer, result);

// check that the resul is valid
if(result->is_valid) {
    // do something with the result->value
} else {
    // handle the invalid case when buffer is empty
}

// cleanup by deleting the buffer and the buffer result
DeleteRingBuffer(buffer);
DeleteRingBufferResult(result);
```


You can use the library as it is or you can modify it. For instance you can modify the buffer to store `uint16_t` or any other data type as follows:

Change the `data` field of the ring buffer struct:
```
    typedef struct
    {
        size_t head;
        size_t tail;
        size_t capacity;
        size_t length;
        uint8_t *data;
    } RingBuffer;
```
to:

```
    typedef struct
    {
        size_t head;
        size_t tail;
        size_t capacity;
        size_t length;
        uint16_t *data;
    } RingBuffer;
```

# Contributing

1. Fork the Project

2. Create your Feature Branch (git checkout -b feature/AmazingFeature)

3. Commit your Changes (git commit -m 'Add some AmazingFeature')

4. Push to the Branch (git push origin feature/AmazingFeature)

5. Open a Pull Request

# License

Distributed under the **BSD** License.