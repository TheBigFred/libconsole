////////////////////////////////////////////////////////////////////////////////
// File      : menu.cpp
// Contents  :
//
// Author    : TheBigFred - thebigfred.github@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "menu.h"
#include "read.h"

namespace console {

void menu::add_entry(int key_code,const std::string &description, void(*callback)(void))
{
   if (!description.empty() && callback)
   {
      char keyChar[2];
      keyChar[0] = (char)key_code; keyChar[1]=0;
      menu_item item = { false, key_code, std::string(keyChar), description, callback };
      items_list.push_back(std::make_pair(key_code,item));
   }
}

void menu::add_exit(int key_code,const std::string &description, void(*callback)(void))
{
   if (!description.empty())
   {
      char keyChar[2];
      keyChar[0] = (char)key_code; keyChar[1]=0;
      menu_item item = { true, key_code, std::string(keyChar), description, callback };
      items_list.push_back(std::make_pair(key_code,item));
   }
}

void menu::add_entry(int key_code,const std::string &key_str,const std::string &description, void(*callback)(void))
{
   if (!key_str.empty() && !description.empty() && callback)
   {
      menu_item item = { false, key_code, key_str, description, callback };
      items_list.push_back(std::make_pair(key_code,item));
   }
}

void menu::add_exit(int key_code,const std::string &key_str,const std::string &description, void(*callback)(void))
{
   if (!key_str.empty() && !description.empty())
   {
      menu_item item = { true, key_code, key_str, description, callback };
      items_list.push_back(std::make_pair(key_code,item));
   }
}

void menu::add_txt(const std::string &description)
{
      menu_item item = { false, 0, "", description, nullptr };
      items_list.push_back(std::make_pair(0,item));
}

void menu::add_separator()
{
   menu_item item = { false, 0, "", "", nullptr };
   items_list.push_back(std::make_pair(0,item));
}

void menu::set_title(const std::string& str)
{
   title = str;
}

void menu::show()
{
   bool end = false;
   int  draw = 1;
   do
   {
      if (draw)
      {
         std::cout << "\033[2J\033[1;1H";
         std::cout << title << std::endl <<std::endl;

         auto it=items_list.begin();
         while (it!=items_list.end())
         {
            if (it->second.key_code == 0)
            {
               std::cout << it->second.description.c_str() << std::endl;
            }
            else
            {
               std::cout << "<" << it->second.key_str.c_str() << "> ";
               std::cout << it->second.description.c_str() << std::endl;
            }
            it++;
         }
         draw = 0;
      }

      int ch = getch();

      auto it = items_list.begin();
      while (it != items_list.end())
      {
         if (it->first == ch)
         {
            if (it->second.callback)
            {
               it->second.callback();
               draw = 1;
            }
            if (it->second.quit)
               end = true;
            break;
         }
         it++;
      }
   }while (!end);
}

} // namespace console