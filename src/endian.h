////////////////////////////////////////////////////////////////////////////////
// File      : endian.h
// Content   : choose the right include for endianness
//
// Author    : TheBigFred - thebigfred.github@gmail.com
// URL       : https://github.com/TheBigFred/libSocket
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#pragma once

#if defined(__linux__) || defined(__CYGWIN__)

#   include <endian.h>
#   define htonll(x) htobe64(x)
#   define ntohll(x) be64toh(x)

#elif defined(__APPLE__)

#elif defined(__OpenBSD__)

#   include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)

#   include <sys/endian.h>

#   define be16toh(x) betoh16(x)
#   define le16toh(x) letoh16(x)

#   define be32toh(x) betoh32(x)
#   define le32toh(x) letoh32(x)

#   define be64toh(x) betoh64(x)
#   define le64toh(x) letoh64(x)

#elif defined(_WIN32) || defined(WIN32)

#   include <winsock2.h>
#   pragma comment(lib, "Ws2_32.lib")

#   define __BYTE_ORDER    BYTE_ORDER
#   define __BIG_ENDIAN    BIG_ENDIAN
#   define __LITTLE_ENDIAN LITTLE_ENDIAN

#  if BYTE_ORDER == LITTLE_ENDIAN
#     define htobe16(x) htons  (x)
#     define htole16(x)        (x)
#     define be16toh(x) ntohs  (x)
#     define le16toh(x)        (x)

#     define htobe32(x) htonl  (x)
#     define htole32(x)        (x)
#     define be32toh(x) ntohl  (x)
#     define le32toh(x)        (x)

#     define htobe64(x) htonll (x)
#     define htole64(x)        (x)
#     define be64toh(x) ntohll (x)
#     define le64toh(x)        (x)

#   elif BYTE_ORDER == BIG_ENDIAN
#      define htobe16(x) (x)
#      define htole16(x) __builtin_bswap16(x)
#      define be16toh(x) (x)
#      define le16toh(x) __builtin_bswap16(x)
 
#      define htobe32(x) (x)
#      define htole32(x) __builtin_bswap32(x)
#      define be32toh(x) (x)
#      define le32toh(x) __builtin_bswap32(x)
 
#      define htobe64(x) (x)
#      define htole64(x) __builtin_bswap64(x)
#      define be64toh(x) (x)
#      define le64toh(x) __builtin_bswap64(x)
#   endif

#else
#   error platform not supported
#endif
