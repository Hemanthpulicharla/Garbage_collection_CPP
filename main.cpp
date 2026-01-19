#include "gc_pointer.h"
#include "LeakTester.h"  

int main()
{
    int* p = new int(19);
    int* p1 = new int(21);
    int * p2 = new int(28);

    return 0;
}