////////////////////////////////////////////////////////////////////////////////
// File      : options.h
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
#include <list>
#include <cstdint>

namespace console {

class options final
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

   void add(const std::string &name, arg has_arg, uint32_t opt_code, const std::string &description);
   int  parse(int argc, char **argv);

private:

   struct opt
   {
      std::string name;
      arg         has_arg;
      uint32_t    opt_code;
      std::string description;
   };

   std::list<opt> opt_list;
   int long_opt(const char* arg0, const char* arg1, action& act);
   int short_opt(const char* arg0, const char* arg1, action& act);
};

} // namespace console