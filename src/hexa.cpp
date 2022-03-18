////////////////////////////////////////////////////////////////////////////////
// File      : hexa.cpp
// Contents  :
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "endian.h"

namespace console {

std::string HexaDump(const std::string& data, int nbBit/*=8*/)
{
   int BytePerCol=0, nbByte=0, nbCol=0, cntCol=0, line=0;
   switch (nbBit) {
      case 16: BytePerCol = 2; nbCol =  8; break;
      case 32: BytePerCol = 4; nbCol =  4; break;
      case 64: BytePerCol = 8; nbCol =  2; break;
      case  8: 
      default: BytePerCol = 1; nbCol = 16; break;
   }

   std::stringstream ss;
   ss << std::hex << std::setfill('0') << std::setw(8) << line << "  ";
   for(auto it=data.begin();it!=data.end();it++)
   {
      ss << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)*it;
      nbByte++;
      if (nbByte >= BytePerCol)  { 
         ss << " ";
         nbByte=0;
         cntCol++;
      }
      if (cntCol >= nbCol) {
         cntCol=0;
         line++;
         ss << std::endl << std::hex << std::setfill('0') << std::setw(8) << line*16 << "  ";
      }
   }
   ss << std::endl;

   std::string str(ss.str());
   return str;
}

std::string HexaStrToByteSt(const std::string& str)
{
   std::string data;
   std::size_t ppos=0;
   std::size_t size=0;
   std::size_t dpos=0;
   char *next = (char*)str.c_str();
   do
   {
      auto npos = str.find(' ',ppos);
      if (npos == std::string::npos)
         size = (str.size() - ppos)/2;
      else
         size = (npos - ppos)/2;
      
      switch(size) {
         case 1:
         {
            auto val = std::strtol (next,&next,16);
            data.insert(dpos,(char*)&val,size);
            break;
         }
         case 2:
         {
            auto val = (int16_t)std::strtol (next,&next,16);
            val = htobe16(val);
            data.insert(dpos,(char*)&val,size);
            break;
         }
         case 4:
         {
            auto val = std::strtol (next,&next,16);
            val = htobe32(val);
            data.insert(dpos,(char*)&val,size);
            break;
         }
         case 8:
         {
            auto val = std::strtoll (next,&next,16);
            val = htobe64(val);
            data.insert(dpos,(char*)&val,size);
            break;
         }
      }
      dpos += size;
      ppos = npos+1;
   } while(next != str.c_str()+str.size());
   return data;
}

} // namespace console