# 🗑️ Building What C++ Refuses to Have

> *"After 38 years, C++23 finally removes Garbage Collection from C++"* [from this tweet](https://x.com/i/status/2009933642949177826) — A joke that's only funny because C++ never had it in the first place.

But what if we could add it ourselves?

## The Challenge

In January 2026, while the programming world debates whether C++ should embrace garbage collection, I decided to stop debating and **build it from scratch**.

This project implements a **reference-counting garbage collector** using smart pointers in C++—essentially recreating what `std::shared_ptr` does under the hood, but with full visibility into the mechanics of automatic memory management.

## Why This Matters
```cpp
// The Problem: Manual Memory Management
int* p = new int(19);
p = new int(21);  // 💥 LEAK! Lost pointer to 19
p = new int(28);  // 💥 LEAK! Lost pointer to 21
// We're bleeding memory...

// The Solution: Automatic Garbage Collection
Pointer<int> p = new int(19);
p = new int(21);  // ✅ Auto-freed 19
p = new int(28);  // ✅ Auto-freed 21
// Memory managed automatically
```

C++ gives you control. But with great control comes great responsibility—and memory leaks, dangling pointers, and sleepless nights debugging segfaults.

## Philosophical Underpinnings ( from what I understood)

This memory and garbage management is the underpinning for **fundamental tradeoff** for systems programming (along with preventing the memory leaks).

**The C++ Way:** "Give me control, I'll manage it myself" (in-built RAII features)
**The GC Way:** "Free me from this burden, I'll trade some performance" (for other languages like python)

By building both, I now understand why:
- Python developers don't think about `delete`
- C++ developers obsess over RAII
- `std::shared_ptr` exists as a compromise
- Modern languages make different choices

## How this works
Every `Pointer<T>` object maintains a shared reference count:

```cpp
Pointer<int> p1 = new int(42);  // refcount = 1
Pointer<int> p2 = p1;           // refcount = 2
Pointer<int> p3 = p2;           // refcount = 3

// When p3 goes out of scope → refcount = 2 ( this going out of scope thing is defined for C++ when the compiler is crossd this symbol '}')
// When p2 goes out of scope → refcount = 1
// When p1 goes out of scope → refcount = 0 → Collected and released 
```

## The file structure
```
┌─────────────────────────────────────────┐
│  Pointer<T>                             │
│  ├─ addr: T*                            │
│  ├─ isArray: bool                       │
│  ├─ arraySize: unsigned                 │
│  └─ static refContainer: List<Details>  │
└─────────────────────────────────────────┘
         │
         ├──→ PtrDetails<T>
         │    ├─ memPtr: T*
         │    ├─ refcount: unsigned
         │    ├─ isArray: bool
         │    └─ arraySize: unsigned
         │
         └──→ collect() // Frees zero-ref objects
```

When `refcount` hits zero, `collect()` automatically calls `delete` or `delete[]` as appropriate.

## Build && Run

Git clone this rep and cd into project file 

```bash
# Compile
g++ -o main.exe main.cpp -std=c++11

# Run
./main.exe
```

### Example Usage

```cpp
#include "gc_pointer.h"
#include "LeakTester.h"

int main() {
    INCLUDE_NOTIFICATIONS  // GC monitoring
    
    Pointer<int> p = new int(100);
    p = new int(200);  // 100 freed up
    
    // Shared ownership
    Pointer<int> p1 = new int(42);
    Pointer<int> p2 = p1;  // Both point to same object so both memory is freed only when both goes out of scope.
    Pointer<int, 5> arr = new int[5];

  for(int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    
    return 0;
} //This is the scope trigger
```
## Output

The integrated `LeakTester` provides detailed memory tracking:

```
>>> Allocated 4 bytes, on address 0x1a2b3c4d
>>> Releasing 4 bytes on address 0x1a2b3c4d

+---------------+
| FINAL REPORT: |
+---------------+

Total allocations: 3
Total deallocations: 3
Max memory occupation: 12 bytes

GREAT JOB! YOU DO NOT HAVE MEMORY LEAKAGE
```

## What I learnt

### Technically:
- **Template metaprogramming** for generic pointer types
- **RAII principles** (Resource Acquisition Is Initialization)
- **Reference counting** vs tracing garbage collection
- **Operator overloading** for natural pointer syntax
- **Static member management** across template instances
- **Custom iterators** for STL-like interfaces

### Design Tradeoffs
- GC adds overhead but prevents leaks
- Manual deletion is predictable, GC is automatic
- Reference counting trades CPU for memory safety
- The Achilles' heel of ref-counting (requires weak pointers)

### The Bigger Picture
This project demonstrated why:
- Rust chose ownership over GC
- Go includes a concurrent GC
- C++ provides smart pointers as opt-in GC
- Python's GC uses reference counting + cycle detection

## Limitations

1. Problem of **Circular References**: Two objects pointing to each other never get freed
   ```cpp
   // This will leak:
   Pointer<Node> a = new Node();
   Pointer<Node> b = new Node();
   a->next = b;
   b->next = a;  // Circular reference!
   ```
   *Solution: Implement weak pointers (future work)*

2. Not thread-safe without mutex protection
3. Reference counting overhead on every assignment
4. Objects freed when refcount hits 0, not immediately
--- 


*"The best way to learn how something works is to build it from scratch."*  
*— Every systems programmer ever*
