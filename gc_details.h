
template <class T>
class PtrDetails
{
  public:
    unsigned refcount; // current reference count
    T *memPtr;         // pointer to allocated memory
    bool isArray; // true if pointing to array
    unsigned arraySize; // size of array
    // Here, mPtr points to the allocated memory.

    PtrDetails(T *ptr, unsigned int size = 0) :
        refcount(1), memPtr(ptr), isArray(size > 0), arraySize(size)
    {
    }
};
// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    return (ob1.memPtr == ob2.memPtr);
}
