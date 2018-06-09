#ifndef C_JIT_X64_LINUX_ABI_H
#define C_JIT_X64_LINUX_ABI_H

enum auxv_types {
    AT_NULL = 0,
    AT_IGNORE = 1,
    AT_EXECFD = 2,
    AT_PHDR = 3,
    AT_PHENT = 4,
    AT_PHNUM = 5,
    AT_PAGESZ = 6,
    AT_BASE = 7,
    AT_FLAGS = 8,
    AT_ENTRY = 9,
    AT_NOTELF = 10,
    AT_UID = 11,
    AT_EUID = 12,
    AT_GID = 13,
    AT_EGID = 14,
    AT_PLATFORM = 15,
    AT_HWCAP = 16,
    AT_CLKTCK = 17,
    AT_SECURE = 23,
    AT_BASE_PLATFORM = 24,
    AT_RANDOM = 25,
    AT_HWCAP2 = 26,
    AT_EXECFN = 31
};

typedef struct {
    enum auxv_types a_type;

    union {
        long a_val;
        void *a_ptr;
        void (*a_fnc)();
    } a_un;
} auxv_t;

#endif //C_JIT_X64_LINUX_ABI_H
