////////////////////////////////////////////////////////////////////////////////
// File      : read.h
// Contents  :
//
// Author    : TheBigFred - thebigfred.github@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <cstdint>
#include <iostream>
#include "platform.h"
#include <libconsole/export.h>

namespace console {

#ifdef OS_UNIX

   bool kbhit(void);
   char getch(void);
   char getche(void);

#elif defined OS_WINDOWS

#  include <conio.h>
#  define getch _getch

#endif

LIBCONSOLE_EXPORT char read_key();
LIBCONSOLE_EXPORT void read_str(std::string& value);
LIBCONSOLE_EXPORT int  read_int();
LIBCONSOLE_EXPORT bool read_int(int& value, int min, int max);
LIBCONSOLE_EXPORT bool read_int_loop(int& value, int min, int max, const std::string& txt);

} // namespace console