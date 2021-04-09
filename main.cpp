////////////////////////////////////////////////////////////////////////////////
// File      : main.cpp
// Contents  :
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "options.h"

enum {
   OPT_A=0,
   OPT_B,
   OPT_C,
};

int main(int argc, char** argv)
{
   console::options opt;
   opt.add("a",   console::options::arg::no,       OPT_A, "");
   opt.add("b",   console::options::arg::required, OPT_B, "");
   opt.add("c",   console::options::arg::optional, OPT_C, "");
   opt.add("--a", console::options::arg::no,       OPT_A, "");
   opt.add("--b", console::options::arg::required, OPT_B, "");
   opt.add("--c", console::options::arg::optional, OPT_C, "");

   auto rc = opt.parse(argc,argv);
   if (rc < 0)
   {
      //usage();
      return rc;
   }

   for (auto act : opt.actions_list)
   {
      switch (act.opt_code)
      {
         case OPT_A: std::cout << "a" << act.opt_arg << std::endl;  break;
         case OPT_B: std::cout << "b" << act.opt_arg << std::endl;  break;
         case OPT_C: std::cout << "c" << act.opt_arg << std::endl;  break;
      }
   }
   return 0;
}
