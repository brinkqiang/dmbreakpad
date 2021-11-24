
#ifndef __DMBREAKPAD_H__
#define __DMBREAKPAD_H__

#include <cstdio>
#include <string>

#ifdef WIN32
#include "../src/client/windows/handler/exception_handler.h"
#else
#include "../src/client/linux/handler/exception_handler.h"
#endif

class CDMBreakPad
{
public:
    CDMBreakPad()
        :
        eh(descriptor, NULL, dumpCallback, NULL,  true, -1)
    {

    }
    ~CDMBreakPad()
    {

    }

    static bool dumpCallback(const google_breakpad::MinidumpDescriptor& desc, void* context, bool succeeded)
    {
        printf("Dump path: %s\n", desc.path());
        return succeeded;
    }
private:
    google_breakpad::ExceptionHandler eh;
    google_breakpad::MinidumpDescriptor descriptor(".");

};

#define DMBREAKPAD_INIT()               CDMBreakPad oInitBreakpad
//static void CrashFunction()
//{   
//    int *i = reinterpret_cast<int*>(0x45);   
//    *i = 5;  // crash!   
//}   

//int main(int argc, char **argv) 
//{   
//    CGBreakPad oBreakPad;
//
//    try
//    {
//        CrashFunction();
//    }
//    catch(...)
//    {
//        printf("catch crash\n");   
//    }
//    printf("did not crash?\n");   
//    return 0;   
//} 

#endif // __DMBREAKPAD_H__
