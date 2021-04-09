////////////////////////////////////////////////////////////////////////////////
// File      : conio.cpp
// Contents  :
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <iostream>
#include "platform.h"

namespace console {

#ifdef OS_UNIX
#include <sys/ioctl.h>
#include <termios.h>
#include <cstdio>

static struct termios old, current;

void enable_raw_mode(bool echo)
{
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;    /* disable buffered i/o */
    if (echo)
       current.c_lflag |= ECHO;    /* set echo mode */
    else
       current.c_lflag &= ~ECHO;   /* set no echo mode */

    tcsetattr(0, TCSANOW, &current);
}

void disable_raw_mode(void)
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

bool kbhit(void)
{
   int byteswaiting;
   enable_raw_mode(false);
   ioctl(0, FIONREAD, &byteswaiting);
   resetTermios();
   return byteswaiting > 0;
}

/* Read 1 character - echo defines echo mode */
char getch_(bool echo)
{
  char ch;
  enable_raw_mode(echo);
  tcflush(0,TCIFLUSH);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(false);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(true);
}
#endif

void clear()
{
   std::cout << "\033[2J\033[1;1H";
}

char read_key()
{
   return getch();
}

void read_str(std::string& value)
{
   std::cin >> value;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   std::cin.clear();
}

int read_int()
{
   int val;
   std::cin >> val;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   std::cin.clear();
   return val;
}

bool read_int(int& value, int min, int max)
{
   auto rc = false;
   int val;
   std::cin >> val;
   if (val>=min && val<=max)
   {
      value = val;
      rc = true;
   }
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   std::cin.clear();
   return rc;
}

bool read_int_loop(int& value, int min, int max, const std::string& txt)
{
   while(1)
   {
      std::cout << std::endl << txt << " (" << min << "-" << max << "): ";
      int val;
      if (read_int(val,min,max))
      {
         value = val;
         return true;
      }
      else
      {
         std::cout << "Bad value, continue (y/n)? ";
         if (read_key() != 'y')
            return false;
      }
   }
}

} // namespace console