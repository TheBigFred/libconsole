////////////////////////////////////////////////////////////////////////////////
// File      : conio.h
// Contents  :
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <cstdint>
#include "platform.h"

namespace console {

#ifdef OS_UNIX
bool kbhit(void);
char getch(void);
char getche(void);
#endif

void clear();
void read_str(std::string& value);
int  read_int();
char read_key();
bool read_int(int& value, int min, int max);
bool read_int_loop(int& value, int min, int max, const std::string& txt);

} // namespace console