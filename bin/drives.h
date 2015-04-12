/* define these to the location of cpm *.com files and specialized support
 * directories usually go below the *.com files.
 * 
 * microsoft, aztec_c, bds_c, dri, hitech_c, slr, generic and any others
 * that are needed.
 *
 * For compilers, these are based on all programs having the same prefix
 * e.g. Aztec C programs are named azcc, azas, azln, etc.  BDS C programs
 * are named bdscc, bdsclink, etc.  Note that cc2.com must be in either
 * CPMCOM or bds_c directory or it won't be found automatically.
 */
#define DRIVEA "./"					/* local directory and drive a: */
#define CPMCOM "c:/cpm_com/"		/* generic *.com location - b:*/

/* drive mappings below (c:,d:) depend on program name */
#define MS "c:/cpm_com/microsoft/"	/* baslib.rel, brun.com, bcload, etc. */
#define AZTEC "c:/cpm_com/aztec_c/" /* libc.lib, stdio.h, libc.h, etc. */
#define HTC "c:/cpm_com/hitech_c/"	/* stdio.h, etc. */
#define BDS "c:/cpm_com/bds_c/"		/* cc2.com, deff*.crl, bdscio.h, etc. */
#define DRI "c:/cpm_com/dri/"		/* *.lib macros, pl*.ovl, etc. */
#define SLR "c:/cpm_com/slr/"		/* macros, include files, etc. */
#define OTHER "c:/cpm_com/other/"	/* defaults */
#define GENERIC "c:/cpm_com/generic/"	/* defaults */

