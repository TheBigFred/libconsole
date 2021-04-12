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
#include <iostream>
#include <iomanip>
#include "platform.h"
#include "export.h"

namespace console {

#ifdef OS_UNIX
EXPORT bool kbhit(void);
EXPORT char getch(void);
EXPORT char getche(void);
#endif

template<typename T>
struct omanip{
   std::ostream& (*impl) (std::ostream&, T);
   T t;

   omanip(std::ostream& (*f)(std::ostream&, T), T arg) : impl(f), t(arg) {}
   
   void operator()(std::ostream& s) const { impl(s, t); }
   friend std::ostream& operator<<( std::ostream& s, const omanip& f) { f(s); return s; }
};

template<typename T>
struct omanip2{
   std::ostream& (*impl) (std::ostream&, T, T);
   T t1;
   T t2;

   omanip2(std::ostream& (*f)(std::ostream&, T, T), T arg1, T arg2) : impl(f), t1(arg1), t2(arg2) {}

   void operator()(std::ostream& s) const { impl(s, t1, t2); }
   friend std::ostream& operator<<( std::ostream& s, const omanip2& f) { f(s); return s; }
};

// Erase
EXPORT std::ostream& clear(std::ostream& os)                      { return os << "\033[2J\033[H"; }
EXPORT std::ostream& clscr(std::ostream& os)                      { return os << "\033[2J"; }
EXPORT std::ostream& clline(std::ostream& os)                     { return os << "\033[2K"; }
EXPORT std::ostream& cllend(std::ostream& os)                     { return os << "\033[0K"; }
EXPORT std::ostream& cllstart(std::ostream& os)                   { return os << "\033[1K"; }

// Cursor control
       std::ostream& setyx(std::ostream& os, int y, int x)        { return os << "\033[" << y << ";" << x << "H"; }
       std::ostream& setup(std::ostream& os, int y)               { return os << "\033[" << y << "A"; }
       std::ostream& setdown(std::ostream& os, int y)             { return os << "\033[" << y << "B"; }
       std::ostream& setright(std::ostream& os, int x)            { return os << "\033[" << x << "C"; }
       std::ostream& setleft(std::ostream& os, int x)             { return os << "\033[" << x << "D"; }
EXPORT std::ostream& savepos(std::ostream& os)                    { return os << "\033[s"; }
EXPORT std::ostream& restorepos(std::ostream& os)                 { return os << "\033[u"; }
EXPORT std::ostream& nocursor(std::ostream& os)                   { return os << "\033[?25l"; }
EXPORT std::ostream& cursor(std::ostream& os)                     { return os << "\033[?25h"; }

// Attributes
EXPORT std::ostream& noattr(std::ostream& os)                     { return os << "\033[0m"; }
EXPORT std::ostream& bold(std::ostream& os)                       { return os << "\033[1m"; }
EXPORT std::ostream& dim(std::ostream& os)                        { return os << "\033[2m"; }
EXPORT std::ostream& italic(std::ostream& os)                     { return os << "\033[3m"; }
EXPORT std::ostream& underline(std::ostream& os)                  { return os << "\033[4m"; }
EXPORT std::ostream& blink(std::ostream& os)                      { return os << "\033[5m"; }
EXPORT std::ostream& inverse(std::ostream& os)                    { return os << "\033[7m"; }
EXPORT std::ostream& invisible(std::ostream& os)                  { return os << "\033[8m"; }
EXPORT std::ostream& strikethrough(std::ostream& os)              { return os << "\033[9m"; }
       std::ostream& setcolor(std::ostream& os, int code)         { return os << "\033[" << code << "m"; }

// Save Restore screen
EXPORT std::ostream& savescr(std::ostream& os)                    { return os << "\033[?47h"; }
EXPORT std::ostream& restorscr(std::ostream& os)                  { return os << "\033[?47l"; }

EXPORT omanip2<int> yx(int y, int x)                              { return omanip2<int>(setyx,y,x);   }
EXPORT omanip<int> up(int y)                                      { return omanip<int> (setup, y);    }
EXPORT omanip<int> down(int y)                                    { return omanip<int> (setdown, y);  }
EXPORT omanip<int> right(int x)                                   { return omanip<int> (setright, x); }
EXPORT omanip<int> left(int x)                                    { return omanip<int> (setleft, x);  }
EXPORT omanip<int> color(int x)                                   { return omanip<int> (setcolor, x); }

// Colors
constexpr uint8_t fg_black   = 30;
constexpr uint8_t fg_red     = 31;
constexpr uint8_t fg_green   = 32;
constexpr uint8_t fg_yellow  = 33;
constexpr uint8_t fg_blue    = 34;
constexpr uint8_t fg_magenta = 35;
constexpr uint8_t fg_cyan    = 36;
constexpr uint8_t fg_white   = 37;

constexpr uint8_t bg_black   = 40;
constexpr uint8_t bg_red     = 41;
constexpr uint8_t bg_green   = 42;
constexpr uint8_t bg_yellow  = 43;
constexpr uint8_t bg_blue    = 44;
constexpr uint8_t bg_magenta = 45;
constexpr uint8_t bg_cyan    = 46;
constexpr uint8_t bg_white   = 47;


EXPORT void read_str(std::string& value);
EXPORT int  read_int();
EXPORT char read_key();
EXPORT bool read_int(int& value, int min, int max);
EXPORT bool read_int_loop(int& value, int min, int max, const std::string& txt);

} // namespace console