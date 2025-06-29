#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BUFFvar;

typedef struct {
    BUFFvar* buffer;  // buffer array
    uint8_t size;     // total buffer size
    uint8_t head;     // write position
    uint8_t tail;     // read position (oldest data)
} CircularBuffer;

// Initialize the buffer
void Buffer_init(CircularBuffer* b, BUFFvar* buffArray, uint8_t size) {
    b->buffer = buffArray;
    b->size = size;
    b->head = 0;
    b->tail = 0;
    memset(b->buffer, 0, size);
}

// Push one byte, overwriting oldest data if full
void Buffer_push(CircularBuffer* b, BUFFvar data) {
    b->buffer[b->head] = data;
    b->head = (b->head + 1) % b->size;

    // Overwrite oldest data? Move tail forward
    if (b->head == b->tail) {
        b->tail = (b->tail + 1) % b->size;
    }

    // Always null terminate after head
    b->buffer[b->head] = '\0';
}

// Peek string from tail, copying up to max_len-1 bytes, guaranteed null-terminated
// Stops copying on '\0' or reaching max_len-1 or until head is reached
size_t Buffer_peek_string(const CircularBuffer* b, char* dest, size_t max_len) {
    if (max_len == 0) return 0;

    size_t i = 0;
    uint8_t pos = b->tail;

    while (pos != b->head && i < max_len - 1) {
        BUFFvar byte = b->buffer[pos];
        dest[i++] = byte;
        if (byte == '\0') break;
        pos = (pos + 1) % b->size;
    }

    // No need to add '\0' here, buffer already guarantees null termination

    return i;
}

// Flush buffer: reset to empty
void Buffer_flush(CircularBuffer* b) {
    b->head = 0;
    b->tail = 0;
    memset(b->buffer, 0, b->size);
}
