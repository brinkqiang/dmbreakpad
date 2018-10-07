# dmbreakpad

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[dmbreakpad GitHub](https://github.com/brinkqiang/dmbreakpad)

## Build status
| [Linux][lin-link] | [MacOSX][osx-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![osx-badge]       | ![win-badge]        |

[lin-badge]: https://travis-ci.org/brinkqiang/dmbreakpad.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/brinkqiang/dmbreakpad "Travis build status"
[osx-badge]: https://travis-ci.org/brinkqiang/dmbreakpad.svg?branch=master "Travis build status"
[osx-link]:  https://travis-ci.org/brinkqiang/dmbreakpad "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/github/brinkqiang/dmbreakpad?branch=master&svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/brinkqiang/dmbreakpad "AppVeyor build status"

## Intro
C++ dmp file generate. based on breakpad.
```cpp

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
    DMBREAKPAD_INIT();
    
    CrashFunction();

    printf("did not crash?\n");   
    return 0;   
}

```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmbreakpad/Lobby.svg)](https://gitter.im/brinkqiang/dmbreakpad)

## Thanks
