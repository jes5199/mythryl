/* machine-id.h
 *
 */

#ifndef _MACHINE_ID_
#define _MACHINE_ID_

#ifndef _LIB7_BASE_
#  include "runtime-base.h"
#endif

#if defined(TARGET_M68)
#  define MACHINE_ID	"m68"
#elif defined(TARGET_RS6000)
#  define MACHINE_ID	"rs6000"
#elif defined(TARGET_PPC)
#  define MACHINE_ID	"ppc"
#elif defined(TARGET_SPARC)
#  define MACHINE_ID	"sparc"
#elif defined(TARGET_X86)
#  define MACHINE_ID	"x86"
#elif defined(TARGET_BYTECODE)
#  define MACHINE_ID	"bytecode"
#else
#  error unknown architecture type
#endif

#if   defined(OPSYS_UNIX)
#  if   (defined(OPSYS_AIX))
#    define OPSYS_ID	"aix"
#  elif (defined(OPSYS_DARWIN))
#    define OPSYS_ID    "darwin"
#  elif (defined(OPSYS_DUNIX))
#    define OPSYS_ID	"dunix"
#  elif (defined(OPSYS_FREEBSD) || defined(OPSYS_NETBSD) || defined(OPSYS_NETBSD2))
#    define OPSYS_ID	"bsd"
#  elif (defined(OPSYS_HPUX9))
#    define OPSYS_ID	"hpux9"
#  elif (defined(OPSYS_HPUX))
#    define OPSYS_ID	"hpux"
#  elif (defined(OPSYS_IRIX4) || defined(OPSYS_IRIX5))
#    define OPSYS_ID	"irix"
#  elif (defined(OPSYS_LINUX))
#    define OPSYS_ID	"linux"
#  elif (defined(OPSYS_OSF1))
#    define OPSYS_ID	"osf1"
#  elif (defined(OPSYS_SOLARIS))
#    define OPSYS_ID	"solaris"
#  elif (defined(OPSYS_SUNOS))
#    define OPSYS_ID	"sunos"
#  elif (defined(OPSYS_CYGWIN))
#    define OPSYS_ID    "cygwin"
#  else
#    define OPSYS_ID	"unix"
#  endif
#elif defined(OPSYS_MACOS)
#  define OPSYS_ID	"macos"
#elif defined(OPSYS_BEOS)
#  define OPSYS_ID	"beos"
#elif defined(OPSYS_WIN32)
#  define OPSYS_ID	"win32"
#else
#  error unknown operating system
#endif

#endif /* _MACHINE_ID_ */



/* COPYRIGHT (c) 1996 AT&T Research.
 * Subsequent changes by Jeff Prothero Copyright (c) 2010,
 * released under Gnu Public Licence version 3.
 */
