
#ifndef __DMBREAKPAD_H__
#define __DMBREAKPAD_H__

#include <cstdio>
#include <string>

#ifdef _WIN32
#include "../src/client/windows/handler/exception_handler.h"
#else
#include "../src/client/linux/handler/exception_handler.h"
#include "third_party/lss/linux_syscall_support.h"
#endif


class CDMBreakPad
{
public:
    CDMBreakPad()
        :
#ifdef _WIN32
        eh(
            L".", NULL, callback, NULL,
            true)
#endif

#if __linux__
        eh(descriptor, NULL, dumpCallback, NULL, true, -1), descriptor(".")
#endif

    {

    }
    ~CDMBreakPad()
    {

    }

#ifdef _WIN32
    static bool callback(const wchar_t* dump_path, const wchar_t* id,
        void* context, EXCEPTION_POINTERS* exinfo,
        MDRawAssertionInfo* assertion,
        bool succeeded)
    {
        if (succeeded)
        {
            printf("dump path is %ws, guid is %ws\n", dump_path, id);
        }
        else
        {
            printf("dump failed\n");
        }
        fflush(stdout);

        return succeeded;
    }
#endif

#if __linux__
    static bool dumpCallback(const google_breakpad::MinidumpDescriptor& desc, void* context, bool succeeded)
    {
        printf("Dump path: %s\n", desc.path());
        return succeeded;
    }
#endif
private:
    google_breakpad::ExceptionHandler eh;
#ifdef __linux__
    google_breakpad::MinidumpDescriptor descriptor;
#endif
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
