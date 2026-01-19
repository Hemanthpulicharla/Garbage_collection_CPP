// gc_implementation.cpp
#include "LeakTester.h"
#include "gc_pointer.h"

// Force explicit instantiation for common types
template class Pointer<int, 0>;
template class Pointer<float, 0>;
template class Pointer<double, 0>;
template class Pointer<char, 0>;

// This ensures static variables are defined in ONE place only