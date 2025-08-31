#pragma once
#include <stdexcept>

#ifndef NDEBUG
#define PHYS_THROW_EXCEPTION(exception_class, message) throw exception_class(message)
#define PHYS_THROW_RUNTIME_ERROR(message) PHYS_THROW_EXCEPTION(std::runtime_error, message)
// Use do-while to ensure this behaves like a single statement
#define PHYS_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            PHYS_THROW_RUNTIME_ERROR(message); \
        } \
    } while (false)
#else
#define PHYS_THROW_EXCEPTION(exception_class, message) ((void)0)
#define PHYS_THROW_RUNTIME_ERROR(message) ((void)0)
#define PHYS_ASSERT(condition, message) (condition)
#endif
