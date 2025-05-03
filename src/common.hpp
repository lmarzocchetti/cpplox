#pragma once

#include <cstdlib>

#ifdef __linux__
#include <cstdint>
#endif

#define DEBUG_TRACE_EXECUTION

#ifndef NODEBUG
#ifdef _WIN32
#define DEBUG_MEMORY_LEAKS
#endif
#endif

