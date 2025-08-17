#pragma once

// Base command class
class Command {
public:
    virtual const char* name() const = 0;
    virtual void execute(int argc, const char** argv) = 0;
};

// Registration macro
#define REGISTER_COMMAND(cmdclass) \
static cmdclass __##cmdclass##_instance; \
static Command* __##cmdclass##_ptr \
__attribute__((used, section(".commands"), aligned(4))) = &__##cmdclass##_instance;


// Symbols provided by the linker
extern "C" {
    extern Command* __start_commands;
    extern Command* __stop_commands;
}