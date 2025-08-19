#pragma once
#include <stdexcept>

#ifndef NDEBUG
#define PHYS_THROW_EXCEPTION(exception_class, message) throw exception_class(message)
#define PHYS_THROW_RUNTIME_ERROR(message) PHYS_THROW_EXCEPTION(std::runtime_error, message)
#else
#define PHYS_THROW_EXCEPTION(exception_class, message) ((void)0)
#define PHYS_THROW_RUNTIME_ERROR(message) ((void)0)
#endif
