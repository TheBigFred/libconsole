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

void options::add(const std::string &name, arg has_arg, uint32_t opt_code)
 {
   auto it = opt_list.find(name);
   if (opt_list.size() == 0 || it == opt_list.end())
   {
      opt opt = {};
      opt.has_arg = has_arg;
      opt.opt_code = opt_code;
      opt_list[name] = opt;
   }
 }

 void options::add_suboption(const std::string &optname, const std::string &suboptname, arg has_arg, uint32_t opt_code)
 {
   auto optIt = opt_list.find(optname);
   if (optIt != opt_list.end())
   {
      auto suboptIt = optIt->second.subopt_list.find(suboptname);
      if (optIt->second.subopt_list.size() == 0 || suboptIt == optIt->second.subopt_list.end())
      {
         opt opt = {};
         opt.has_arg = has_arg;
         opt.opt_code = opt_code;
         optIt->second.subopt_list[suboptname] = opt;
      }
   }
 }

int options::check_has_arg(arg has_arg)
{
   if (has_arg == options::arg::required)
      return 0;
   else if (has_arg == options::arg::optional)
      return 1;
   else
      return 0;
}

int options::long_opt(const char* arg0, const char* arg1, const char* arg2, action &act)
{
   auto optIt = opt_list.find(arg0);
   if (optIt != opt_list.end())
   {
      if (optIt->second.has_arg == options::arg::no)
      {
         act.opt_code = optIt->second.opt_code;
         return 1;
      }
      else if (arg1 != nullptr)
      {
         if (optIt->second.subopt_list.size() > 0)
         {
            auto suboptIt = optIt->second.subopt_list.find(arg1);
            if (suboptIt != optIt->second.subopt_list.end())
            {
               act.opt_code = suboptIt->second.opt_code;
               if (suboptIt->second.has_arg == options::arg::no)
                  return 1;
               else if (arg2)
               {
                  act.opt_arg = std::string(arg2);
                  return 1;
               }
               return check_has_arg(suboptIt->second.has_arg);
            }
            else
               return check_has_arg(suboptIt->second.has_arg);
         }
         else
         {
            act.opt_code = optIt->second.opt_code;
            act.opt_arg = std::string(arg1);
            return 1;
         }
      }
      else
      {
         act.opt_code = optIt->second.opt_code;
         return check_has_arg(optIt->second.has_arg);
      }
   }
   return 0;
}

int options::short_opt(const char arg0, const char* arg1, action &act)
{
   std::string arg;
   arg.push_back(arg0);

   auto optIt = opt_list.find(arg);
   if (optIt != opt_list.end())
   {
      if (optIt->second.has_arg == options::arg::no)
         act.opt_code = optIt->second.opt_code;

      else if (optIt->second.has_arg == options::arg::required)
      {
         if (arg1 != nullptr)
         {
            act.opt_code = optIt->second.opt_code;
            act.opt_arg = std::string(arg1);
         }
         else
            return 0;
      }
      else if (optIt->second.has_arg == options::arg::optional)
      {
         act.opt_code = optIt->second.opt_code;
         if (arg1 != nullptr)
            act.opt_arg = std::string(arg1);
      }
      return 1;
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
         if (short_opt(*arg, argv[n+1], act))
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
            if (short_opt(*arg, nullptr, act))
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
         int jump=1;
         char* arg2 = nullptr;
         if (n+1 < argc && *argv[n+1] != '-')
         {
            arg2 = argv[n+1];
            jump++;
         }

         char* arg3 = nullptr;
         if (arg2 && n+2 < argc && *argv[n+2] != '-')
         {
            arg3 = argv[n+2];
            jump++;
         }

         action act = {};
         if (long_opt(arg, arg2, arg3, act))
            actions_list.push_back(act);
         else
            return -1;
         
         n += jump;
      }
      else
         n++;
   }
   return 0;
}
} // namespace console
