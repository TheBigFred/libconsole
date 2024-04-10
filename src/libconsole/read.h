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

EXPORT char read_key();
EXPORT void read_str(std::string& value);
EXPORT int  read_int();
EXPORT bool read_int(int& value, int min, int max);
EXPORT bool read_int_loop(int& value, int min, int max, const std::string& txt);

} // namespace console