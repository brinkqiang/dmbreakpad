
#include "dmbreakpad.h"
#include <time.h>


static void CrashFunction_INNER()
{
    int *i = reinterpret_cast<int*>(0x45);
    *i = 5;  // crash!
}

static void CrashFunction()
{   
    srand(time(0));
    int x = rand() % 2;
    int y = 10;
    int z = y / x;// crash!

    printf("%d", z);
    CrashFunction_INNER();
}

int main(int argc, char **argv) 
{   
    CDMBreakPad oBreakPad;
    
    CrashFunction();

    printf("did not crash?\n");   
    return 0;   
}

