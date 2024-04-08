////////////////////////////////////////////////////////////////////////////////
// File      : hexa.h
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

#include <string>
#include "export.h"

namespace console {

EXPORT std::string HexaDump(const std::string& data, int nbBit=8);
EXPORT std::string HexaStrToByteStr(const std::string& str);

} // namespace console