////////////////////////////////////////////////////////////////////////////////
// File      : init.h
// Contents  :
//
// Author    : TheBigFred - thebigfred.github@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include "platform.h"
#include "init.h"

#ifdef OS_WINDOWS
#   include <Windows.h>   
#endif

namespace console {

int console_init()
{
#ifdef OS_WINDOWS
   // Set output mode to handle virtual terminal sequences
   HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
   if (hOut == INVALID_HANDLE_VALUE)
      return GetLastError();

   DWORD dwMode = 0;
   if (!GetConsoleMode(hOut, &dwMode))
      return GetLastError();

   dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
   if (!SetConsoleMode(hOut, dwMode))
      return GetLastError();
#endif
   return 0;
}

} // namespace console