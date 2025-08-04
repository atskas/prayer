#ifndef PANIC_H
#define PANIC_H

#ifdef __cplusplus
extern "C" {
#endif

    [[noreturn]] void panic(const char* info);

#ifdef __cplusplus
}
#endif

#endif // PANIC_H
