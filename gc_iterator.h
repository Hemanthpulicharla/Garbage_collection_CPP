// Exception thrown when an attempt is made to
// use an Iter that exceeds the range of the
// underlying object i.e the max count/length.
#include <iostream>
class OutOfRangeExc
{
   public:
   explicit OutOfRangeExc(std::string err) : m_error(err)
   {
    std::cout << m_error << std::endl;
   }

   private:
    std::string m_error;
   };


// An iterator-like class for cycling through arrays
// that are pointed to by GCPtrs. Iter pointers
// ** do not ** participate in or affect garbage
// collection. Thus, an Iter pointing to
// some object does not prevent that object
// from being recycled.
template <class T>
class Iter
{
    T *ptr;
    T *end;

    T *begin;        // points to start of allocated array
    unsigned length; // length of sequence
  public:
    Iter()
    {
        ptr = end = begin = NULL;
        length = 0;
    }
    Iter(T *p, T *first, T *last)
    {
        ptr = p;
        end = last;
        begin = first;
        length = last - first;
    }
    // Return length of sequence to which this Iter points.
    unsigned size() { return length; }

   T &operator*()
{
    if ((ptr >= end) || (ptr < begin))
        throw OutOfRangeExc("Iterator out of range in operator*");
    return *ptr;
}
    T *operator->()
{
    if ((ptr >= end) || (ptr < begin))
        throw OutOfRangeExc("Iterator out of range in operator->");
    return ptr;
}
    // Prefix ++.
    Iter &operator++()
    {
        ptr++;
        return *this;
    }
    // Prefix --.
    // Postfix ++.
    Iter operator++(int notused)
    {
        T *tmp = ptr;
        ptr++;
        return Iter<T>(tmp, begin, end);
    }
    // Postfix --.
    Iter operator--(int notused)
    {
        T *tmp = ptr;
        ptr--;
        return Iter<T>(tmp, begin, end);
    }
    bool operator==(Iter op2)
    {
        return ptr == op2.ptr;
    }
    bool operator!=(Iter op2)
    {
        return ptr != op2.ptr;
    }
    bool operator<(Iter op2)
    {
        return ptr < op2.ptr;
    }
    bool operator<=(Iter op2)
    {
        return ptr <= op2.ptr;
    }
    bool operator>(Iter op2)
    {
        return ptr > op2.ptr;
    }
    bool operator>=(Iter op2)
    {
        return ptr >= op2.ptr;
    }
    // Subtract an integer from an Iter.
    Iter operator-(int n)
    {
        ptr -= n;
        return *this;
    }
    // Add an integer to an Iter.
    Iter operator+(int n)
    {
        ptr += n;
        return *this;
    }
    // Return number of elements between two Iters.
    int operator-(Iter<T> &itr2)
    {
        return ptr - itr2.ptr;
    }
};
