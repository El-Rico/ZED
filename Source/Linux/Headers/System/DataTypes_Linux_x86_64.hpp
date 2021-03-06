#ifndef __ZED_DATATYPES_LINUX_X86_32_HPP__
#define __ZED_DATATYPES_LINUX_X86_32_HPP__

// int64_t and uint64_t
#include <stdint.h>
// size_t
#include <linux/types.h>
#include <cstddef>

typedef char				ZED_CHAR8;
typedef signed char			ZED_SCHAR8;
typedef unsigned char		ZED_UCHAR8;
typedef wchar_t				ZED_CHAR16;
typedef signed char			ZED_SINT8;
typedef unsigned char		ZED_UINT8;
typedef signed short		ZED_SINT16;
typedef unsigned short		ZED_UINT16;
typedef signed int			ZED_SINT32;
typedef unsigned int		ZED_UINT32;
typedef int64_t				ZED_SINT64;
typedef uint64_t			ZED_UINT64;

typedef int					ZED_FILE_DESCRIPTOR;
const int					ZED_INVALID_FILE_DESCRIPTOR	= -1;

// Define the platform as x86 Endian (Little)
#define ZED_BIG_ENDIAN		0
#define ZED_LITTLE_ENDIAN	1

#define ZED_64BIT			1
#define	ZED_32BIT			0

#endif

