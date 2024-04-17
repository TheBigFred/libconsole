////////////////////////////////////////////////////////////////////////////////
// File      : options.h
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

#include <map>
#include <list>
#include <string>
#include <cstdint>
#include <libconsole/export.h>

namespace console {

class LIBCONSOLE_EXPORT options final
{
public:
   options() = default;
   ~options() = default;

   struct action
   {
      uint32_t    opt_code;
      std::string opt_arg;
   };
   std::list<action> actions_list;

   enum class arg : uint32_t {
      no = 0,
      required,
      optional
   };

   void add(const std::string &name, arg has_arg, uint32_t opt_code);
   void add_suboption(const std::string &optname, const std::string &suboptname, arg has_arg, uint32_t opt_code);
   int  parse(int argc, char **argv);

private:

   struct opt
   {
      arg         has_arg;
      uint32_t    opt_code;
      std::map<std::string,opt> subopt_list;
   };

   std::map<std::string,opt> opt_list;

   int long_opt(const char* arg0, const char* arg1, const char* arg2, action& act);
   int short_opt(const char arg0, const char* arg1, action& act);
   int check_has_arg(arg has_arg);
};

} // namespace console