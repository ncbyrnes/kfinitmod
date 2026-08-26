#ifndef LOAD_H
#define LOAD_H

#include <stdint.h>

#define XOR_KEY (0x5A)

typedef struct __attribute__((packed)) bin_data {
    uint64_t len;
    unsigned char payload[];
} bin_data_t;

#endif /*LOAD_H*/