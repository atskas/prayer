#pragma once
#include "command.h"

void shell_loop(); // The shell's main loop.

int split_args(char* line, const char** argv); // Splits line's arguments.

void handle_input(char* line); // Handles input.