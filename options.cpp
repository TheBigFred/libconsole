////////////////////////////////////////////////////////////////////////////////
// File      : options.cpp
// Contents  :
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <iostream>
#include <iomanip>
#include "options.h"

namespace console {

void options::add(const std::string &name, arg has_arg, uint32_t opt_code, const std::string &description)
 {
   opt opt = {};
   opt.name = name;
   opt.has_arg = has_arg;
   opt.opt_code = opt_code;
   opt.description = description;
   opt_list.push_back(opt);
 }

int options::long_opt(const char* arg0, const char* arg1, action &act)
{
   for (auto opt : opt_list)
   {
      if (opt.name.compare(arg0) == 0)
      {
         if (opt.has_arg == arg::no)
            act.opt_code = opt.opt_code;

         else if (opt.has_arg == arg::required) 
         {
            if (arg1 != nullptr)
            {
               act.opt_code = opt.opt_code;
               act.opt_arg = std::string(arg1);
            }
            else
               return 0;
         }
         else if (opt.has_arg == arg::optional)
         {
            act.opt_code = opt.opt_code;

            if (arg1 != nullptr)
               act.opt_arg = std::string(arg1);
         }
         return 1;
      }
   }
   return 0;
}

int options::short_opt(const char* arg0, const char* arg1, action &act)
{
   for (auto opt : opt_list)
   {
      if (*opt.name.c_str() == *arg0)
      {
         if (opt.has_arg == arg::no)
            act.opt_code = opt.opt_code;

         else if (opt.has_arg == arg::required)
         {
            if (arg1 != nullptr)
            {
               act.opt_code = opt.opt_code;
               act.opt_arg = std::string(arg1);
            }
            else
               return 0;
         }
         else if (opt.has_arg == arg::optional)
         {
            act.opt_code = opt.opt_code;
            if (arg1 != nullptr)
               act.opt_arg = std::string(arg1);
         }
         return 1;
      }
   }
   return 0;
}

int options::parse(int argc, char **argv)
{
   if (argc < 2)
      return -1;

   actions_list.clear();

   int n = 1;
   while (n < argc)
   {
      auto arg = argv[n];
      auto len = strlen(argv[n])-1;
      
      // -
      if (*arg == '-' && len == 0)
         n++;
      // -a value
      else if (*arg == '-' && *(arg+1) != '-' && len == 1 && n+1 < argc && *argv[n+1] != '-')
      {
         arg++; // a value
         action act = {};
         if (short_opt(arg, argv[n+1], act))
            actions_list.push_back(act);
         else
            return -1;
         n += 2;
      }
      // -abc
      else if (*arg == '-' && *(arg+1) != '-')
      {
          arg++; // abc
          for(uint32_t i=0; i<len; i++)
          {
            action act = {};
            if (short_opt(arg, nullptr, act))
               actions_list.push_back(act);
            else
               return -1;
            arg++;
          }
          n++;
      }
      // --xyz
      else if (*arg == '-' && *(arg+1) == '-')
      {
         char* arg2 = nullptr;
         if (n+1 < argc && *argv[n+1] != '-')
            arg2 = argv[n+1];

         action act = {};
         if (long_opt(arg, arg2, act))
            actions_list.push_back(act);
         else
            return -1;
         
         if (arg2) n += 2;
         else n++;
      }
      else
         n++;
   }
   return 0;
}
} // namespace console

// int main()
// {

//    const char *arg[] = {
//       "AppName",
//       "-ac", "toto",
//       "-b", "toto",
//       "--a",
//       "--b", "titi",
//       "--c"
//    };

//    auto rc = opt.parse(8,(char**)arg);
//    for (auto act : opt.actions_list)
//       std::cout << act.opt_code << " " << act.opt_arg << std::endl;
// }