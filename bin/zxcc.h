/*
 *  Change the directories in these #defines if necessary. Note trailing slash.
 */

#include "config.h"
#include "z80/z80.h"
/* maximum alternate directories at this time
 */

#define MAXALT 5

#if 0
#ifdef __MSDOS__

	#define BINDIR80 "c:/cpm_com/"
	#define LIBDIR80 "c:/cpm_com/aztec_c/"
	#define INCDIR80 "c:/cpm_com/bds_c/"
#else
/* Unless overridden, these are defined by autoconf. Note trailing slash.
 	#undef BINDIR80
 	#undef LIBDIR80
 	#undef INCDIR80
	#define BINDIR80 "/usr/local/lib/cpm/bin80/"
	#define LIBDIR80 "/usr/local/lib/cpm/lib80/"
	#define INCDIR80 "/usr/local/lib/cpm/include80/"
*/
#endif
#endif

#define SERIAL "ZXCC05"

/* System include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#ifdef __MSDOS
#include <dos.h>
#endif

/* Library includes */

/* ++tlb - use native Windows console I/O */
/*
#ifdef USE_CPMIO
#include "cpmio.h"
#endif

#ifdef USE_CPMGSX
#include "cpmgsx.h"
#endif
*/

#include <cpmredir.h>	/* BDOS disc simulation */

typedef unsigned char byte;	/* Must be exactly 8 bits */
typedef unsigned short word;	/* Must be exactly 16 bits */

/* Prototypes */

void ed_fe  (Z80 *R);
void cpmbdos(Z80 *R); 
void cpmbios(Z80 *R);
void dump_regs(Z80 *R);
void Msg(char *s, ...);
int zxcc_term(void);
void zxcc_exit(int code);

/* Global variables */

extern char progname[100];
extern char **argv;
extern int argc;
extern byte RAM[65536]; /* The Z80's address space */

/* Z80 CPU emulation */


