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
