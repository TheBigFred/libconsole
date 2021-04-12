////////////////////////////////////////////////////////////////////////////////
// File      : menu.h
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

#include <list>
#include <string>
#include "export.h"

namespace console {

class EXPORT menu final
{
public:
   menu() = default;
   ~menu() = default;

   void add_entry(int keyCode,const std::string &description, void(*callback)(void)=nullptr);
   void add_exit(int keyCode,const std::string &description, void(*callback)(void)=nullptr);
   void add_entry(int keyCode,const std::string &key_str,const std::string &description, void(*callback)(void)=nullptr);
   void add_exit(int keyCode,const std::string &key_str,const std::string &description, void(*callback)(void)=nullptr);
   void add_txt(const std::string &description);
   void add_separator();
   void set_title(const std::string&);
   void show();

private:

   struct menu_item {
      bool        quit;
      int         key_code;
      std::string key_str;
      std::string description;
      void (*callback)(void);
   };

   std::list<std::pair<int,menu_item>>  items_list;
   std::string title;
};

} // namespace console