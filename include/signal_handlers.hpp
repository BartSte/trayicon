#pragma once

#include <csignal>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
BOOL WINAPI handle_console(DWORD signal);
#else
void handle_sigint(int signal);
#endif

void setup_signal_handlers();
