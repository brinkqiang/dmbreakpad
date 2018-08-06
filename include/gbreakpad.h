
#ifndef __GBREAKPAD_H__
#define __GBREAKPAD_H__

#include <cstdio>
#ifdef WIN32
#include "../google_breakpad/client/windows/handler/exception_handler.h"
#else
#include "../google_breakpad/client/linux/handler/exception_handler.h"
#endif

class CGBreakPad
{
public:
    CGBreakPad()
        :
#ifndef WIN32
        eh(   
        ".", NULL, callback, NULL,   
        true)
#else
        eh(   
        L".", NULL, callback, NULL,   
        true)
#endif
    {


    }
    ~CGBreakPad()
    {

    }

#ifndef WIN32
    static bool callback(const char *dump_path,
        const char *id,
        void *context,
        bool succeeded)
    {
        if (succeeded)
        {   
            printf("dump path is %s, guid is %s\n", dump_path, id);   
        }
        else
        {   
            printf("dump failed\n");   
        }   
        fflush(stdout);   

        return succeeded;   
    }
#else
    static bool callback(const wchar_t *dump_path, const wchar_t *id,   
        void *context, EXCEPTION_POINTERS *exinfo,   
        MDRawAssertionInfo *assertion,   
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
private:
    google_breakpad::ExceptionHandler eh;
};

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

#endif // __GBREAKPAD_H__
