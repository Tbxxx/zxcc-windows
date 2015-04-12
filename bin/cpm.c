/* Port of ZXCC to Windows - Tom Burnett
 */

#include "zxcc.h"
#include <errno.h>

/* Z80 registers and data from Marat Fayzullin's Z80.c */
Z80 R;


/* includes for native user interface development programs */
#ifdef MBASIC
#include "mbasic.h"
#elif OBASIC
#include "obasic.h"
#elif M80
#include "m80.h"
#elif M80NEW
#include "m80new.h"
#elif BASCOM
#include "bascom.h"
#elif L80
#include "l80.h"
#elif LD80
#include "ld80.h"
#elif F80
#include "f80.h"
#elif MAC
#include "mac.h"
#elif RMAC
#include "rmac.h"
#elif AZCC
#include "azcc.h"
#elif AZAS
#include "azas.h"
#elif AZLN
#include "azln.h"
#elif BDSCC
#include "bdscc.h"
#elif BDSCLINK
#include "bdsclink.h"
#elif HTC
#include "htc.h"
#elif HTCPP
#include "htcpp.h"
#elif XXXX
#include "xxxx.h" /* gcc hack-can't look, smell, taste or feel like a ????er */
#elif HTZAS
#include "htzas.h"
#elif HTOPTIM
#include "htoptim.h"
#elif HTLIBR
#include "htlibr.h"
#elif HTP1
#include "htp1.h"
#elif HTCGEN
#include "htcgen.h"
#elif MSH
#include "msh.h"
#elif XYCPMBCD
#include "xycpmbcd.h"
#elif DRILINK
#include "drilink.h"
#elif DRILIB
#include "drilib.h"
#elif ZCPR
#include "zcpr16.h"
#elif MSH
#include "msh.h"
#elif SLR180
#include "slr180.h"
#elif SLRZ80
#include "slrz80.h"
#elif SLRNK1
#include "slrnk1.h"
#elif SLRIB
#include "slrib.h"
#elif CPM
char tpa[] = {0x00}; /* keep compiler happy - no program at tpa to start */
#endif

/* This will be tested later in main() and reset if necessary
 * the alternative ccp's load at a different address (0xf600)
 * instead of 0x100.  One flag for any CCP.
 */
int zcpr = 0;

/* phony declarations to keep compiler happy when they're not used
 * they will be overwritten with real data if needed
 */

/*  NOTE - CPM is defined if used for testing i.e. cpm prog <args> mode */

/* testing flag
 * tflag = 0 means program name is CP/M command ran directly from cmd.exe
 * command line e.g. mbasic, m80, azcc, bdscc, etc. along with arguments
 * the CP/M program expects to see e.g. "m80 file,file=file".
 *
 * tflag = 1 means the CP/M program is indirectly run via the program
 * cpm*.exe.  The name(s) can't change from the list below without changes
 * to the source code.  So, for the above example "cpm m80 file,file=file".
 * Any variation of argv[0] is OK as long as the program starts with cpm.
 *
 * Default is testing is FALSE and argv[0] is checked for cpm*.
 */
int tflag = 0;

/* Global variables */

/* put bios in the final image and memcpy into place */
#include "bios2.h"

char **argv;
int argc;

byte cpm_drive;	
byte cpm_user;
extern byte cpm_error;

/* auto path sequence-only MAXALT (see zxcc.h) used */
char altfiles[6][256];
int maxalt=MAXALT;

char progname[100]; /* way overkill-famous last words of a C programmer... */
char tmpname[100]; /* used for basename() call */

byte RAM[65536]; /* The Z80's address space */

void load_com(void);	/* Forward declaration */

static int deinit_term, deinit_gsx;

char key = '\0';

void dump_regs(Z80 *R)
{
	printf("AF=%04x BC=%04x DE=%04x HL=%04x IX=%04x IY=%04x PC=%04x, SP=%04x\n",
			R->AF.W, R->BC.W, R->DE.W, R->HL.W,
			R->IX.W, R->IY.W, R->PC.W, R->SP.W);
}


byte RdZ80(word addr);
void WrZ80(word addr, byte value);
byte InZ80(word addr);
void OutZ80(word addr, byte value);

char *parse_to_fcb(char *s, int afcb)
{
	byte *fcb = &RAM[afcb+1];

	RAM[afcb] = 0;
	memset(fcb, ' ', 11);

	while (1)
	{
		if (s[0] == 0) break;	
		if (s[0] == ' ') {++s; continue; }
		if (s[1] == ':')
		{
			RAM[afcb] = s[0] - '@';
			if (RAM[afcb] > 16) RAM[afcb] -= 0x20;
			s+=2;
			continue;
		}
		if (s[0] == '.')
		{
			++s;
			fcb = &RAM[afcb+9];
			continue;
		}
		*fcb = *s;  if (islower(*fcb)) *fcb = toupper(*fcb);
		++s;
		++fcb;	
		if (fcb >= &RAM[afcb+12]) break;
	}
	return s;
}


void Msg(char *s, ...)
{
#ifdef DEBUG
	va_list ap;

        va_start(ap, s);
	printf("%s trace: ", progname);
	vprintf(s, ap);
	fflush(stdout);
	if (s[strlen(s) - 1] == '\n') putchar('\r');
	va_end(ap);
#endif
}

void ed_fe(Z80 *R)
{
	switch(R->AF.B.h)
	{
		case 0xC0:
		cpmbdos(R);
		break;

		case 0xC2:
		fprintf(stderr,"%s: Incompatible BIOS.BIN\n", progname);
		zxcc_term();
		zxcc_exit(1);

		case 0xC3:
		cpmbios(R);
		break;

		default:
		fprintf(stderr, "%s: Z80 encountered invalid trap\n", progname);
/*
		dump_regs(R);
*/
		zxcc_term();
		zxcc_exit(1);

	}
}


/* 
 * load_bios() loads the minimal CP/M BIOS and BDOS.
 *
 */

void load_bios(void)
{
	/* move bios into place */
	memcpy(RAM+0xfe00, bios, sizeof(bios));
}

/*
 * try_com() attempts to open file, file.com, file.COM, file.cpm and file.CPM
 *
 */

FILE *try_com(char *s)
{
	char fname[CPM_MAXPATH + 1];
	FILE *fp;
	
	strcpy(fname, s);

    fp = fopen(s, "rb");
	if (fp) return fp;
	sprintf(s,"%s.com", fname);
	fp = fopen(s, "rb"); if (fp) return fp;
	sprintf(s,"%s.COM", s);
	fp = fopen(s, "rb"); if (fp) return fp;
	sprintf(s,"%s.cpm", s);
	fp = fopen(s, "rb"); if (fp) return fp;
	sprintf(s,"%s.CPM", s);
	fp = fopen(s, "rb"); if (fp) return fp;

	strcpy(s, fname);
	return NULL;
}

/*
 * load_com() loads the COM file into z80 memory
 *
 */


void load_com()
{
	int com_len;
	char fname[CPM_MAXPATH + 1];
	FILE *fp;
	int count;

	for(count = 0; count != maxalt; count++) {
		strcpy(fname, altfiles[count]);
		/* if testing mode, argv[1], else argv[0] */
		if (tflag) {
			strcat(fname, argv[1]);
		} else {
			strcat(fname, argv[0]);
		}
		fp = try_com(fname);
		if (fp == NULL) {
			continue;
		} else {
			break;
		}
	}
	if (fp == NULL) {
		fprintf(stderr,"%s: Cannot locate %s, %s.com, %s.COM, %s.cpm _or_ %s.CPM\r\n", 
			progname, argv[1], argv[1], argv[1], argv[1], argv[1]);
		zxcc_term();
		zxcc_exit(1);
	}
	com_len = fread(RAM + 0x0100, 1, 0xFD00, fp);

	if (com_len < 1 || ferror(fp)) {
		fclose(fp);
		fprintf(stderr,"%s: Cannot load %s\n", progname, fname);
		zxcc_term();
		zxcc_exit(1);
	}
	fclose(fp);
/*
printf("Loaded %d bytes from %s\n", com_len, fname);
*/
}


unsigned int in() { return 0; }
unsigned int out() { return 0; }



/* 
 * xltname: Convert a unix filepath into a CP/M compatible drive:name form.
 *          The unix filename must be 8.3 or the CP/M code will reject it.
 *
 * This uses the library xlt_name to do the work, and then just strcat()s 
 * the result to the command line.
 */

void zxcc_xltname(char *name, char *pcmd)
{
	char nbuf[CPM_MAXPATH + 1];

	xlt_name(pcmd, nbuf);

	strcat(name, nbuf);
}

/* main() parses the arguments to CP/M form. argv[1] is the name of the CP/M
  program to load; the remaining arguments are arguments for the CP/M program.

  main() also loads the vestigial CP/M BIOS and does some sanity checks 
         on the endianness of the host CPU and the sizes of data types.
 */

char *basename(char *);

int main(int ac, char **av)
{
	int n;
	char *pCmd, *str;

	argc = ac;
	argv = av;
	
/* DJGPP includes the whole path in the program name, which looks untidy...
 * ++tlb note - needed anyway both for forward slash and backward slash
 * because it may be run from c:\bin, /usr/local/bin or wherever and
 * we only want the basename() - used below
 *
 */
		

	if (sizeof(int) > 8 || sizeof(byte) != 1 || sizeof(word) != 2) {
		fprintf(stderr,"%s: type lengths incorrect; edit typedefs "
                               "and recompile.\n", progname);
		zxcc_exit(1); 
	}

/* must start with "cpm" or "zxcc" - either case for either */
	if ((strncmp(argv[0],"cpm", 3)==0) || (strncmp(argv[0], "CPM",3)==0) ||
	  (strncmp(argv[0],"zxcc", 4)==0) || (strncmp(argv[0], "ZXCC",4)==0)) {
		/* set testing mode flag for argument(s) parse.
		 */
		tflag = 1;
	}
	if ((strcmp(argv[0], "zcpr") == 0) || (strcmp(argv[0], "driccp") == 0)) {
		zcpr = 1;
	}
			

	if (tflag && argc < 2) {
		fprintf(stderr,"%s: No CP/M program name provided.\n",progname);
		zxcc_exit(1);
	}

	if (tflag) {
		strcpy(tmpname, argv[1]); /* string must be writable-argv[1] isn't */
	} else {
		strcpy(tmpname, argv[0]); /* string must be writable-argv[0] isn't */
	}

	strcpy(progname,basename(tmpname));
	if (zcpr == 0) {	
		/* parse command line and put into RAM */
		ccp(ac, av, tflag);
	}
	
	/* set alternative paths for when open fails */
	set_altfiles(progname);

	/* move bios image to needed location */
	load_bios();

	/* initialize page 0 here - NOT in BIOS code any longer */

	/* put warm start address of BIOS call at loc 0,1,2 */
	RAM[0x0] = 0xc3;
	RAM[0x1] = 0x03;
	RAM[0x2] = 0xFF;

    /* iobyte - console */
    RAM[0x3] = 0x0;

    /* current drive */
    RAM[0x4] = 0x0;

    /* BDOS entry */
    RAM[0x5] = 0xc3;
    RAM[0x6] = 0x6;
    RAM[0x7] = 0xfe;


	memset(RAM + 0xFE9C, 0, 0x64);	/* Zap the SCB */
	RAM[0xFE98] = 0x06; 
	RAM[0xFE99] = 0xFE;		/* FE06, BDOS entry */
	RAM[0xFEA1] = 0x31;		/* BDOS 3.1 */
	RAM[0xFEA8] = 0x01;		/* UK date format */
	RAM[0xFEAF] = 0x01;		/* CCP drive */

	RAM[0xFEB6] = 79;
	RAM[0xFEB8] = 23;
	RAM[0xFED1] = 0x80;	/* Buffer area */
	RAM[0xFED2] = 0xFF;
	RAM[0xFED3] = '$';
	RAM[0xFED6] = 0x9C;
	RAM[0xFED7] = 0xFE;	/* SCB address */
	RAM[0xFED8] = 0x80;	/* DMA address */
	RAM[0xFED9] = 0x00;
	RAM[0xFEDA] = 0x01;	/* A: */
	RAM[0xFEE6] = 0x01;	/* Multi sector count */
	RAM[0xFEFE] = 0x06;
	RAM[0xFEFF] = 0xFE;	/* BDOS */

	cpm_drive = 0x00;	/* Start logged into current drive - same as A: */
	cpm_user  = 0;		/* and user 0 */

	if (zcpr == 0) { /* regular com file at 0x100 */
		/* load file into tpa at 0x100 */
		if (tflag == 1) {
			load_com();
		} else { /* program memcpy() into tpa */
			memcpy(&RAM[0x100], tpa, sizeof(tpa));
		}

		/* Note - FE26h is "BEGIN" in the BIOS source code.  This calls
		 * the program at 100h in case the program terminates with a RET
		 * instead of a warm or cold start BIOS call.  It's done to simulate
		 * being called by a real CCP
		 */
		ResetZ80(&R);
		/* Start the Z80 at 0xFE26, with stack at 0xFE00 */
		R.PC.W = 0xfe26;
		R.SP.W = 0xFE00;
		/* Note - FE26h is "BEGIN" in the BIOS source code. */
		RunZ80(&R);
	} else {
		memcpy(&RAM[0xF600], tpa, sizeof(tpa));
		/* CCP's live at 0xf600
		 * non auto program entry at 0xf603
		 */
		ResetZ80(&R);
		/* Start the Z80 at 0xF603, with stack at 0xFE00 */
		R.PC.W = 0xF603;
		R.SP.W = 0xFE00;
		RunZ80(&R);
	}

	return zxcc_term();
}

void zxcc_exit(int code)
{
	exit(code);
}

int zxcc_term(void)
{
	word n;


	n = RAM[0x81];		  /* Get the return code. This is Hi-Tech C */
	n = (n << 8) | RAM[0x80]; /* specific and fails with other COM files */

	putchar('\n');

	if (cpm_error != 0)	/* The CP/M "set return code" call was used */
	{			/* (my modified Hi-Tech C library uses this */
		n = cpm_error;	/*  call) */
	}	
	if (n < 256 || n == 0xFFFF)
	{
		Msg("Return code %d\n", n);
		return n;
	}
	else	return 0;
}

/* signal trap - reset tty modes and leave program
 * 99 is used if the program wants to exit gracefully,
 */
void goodbye(sig)
int sig;
{
	/* close devices ++tlb - not in use yet - not sure yet how they
     * will be used, but probably file i/o.
     */
/*
        fclose(fplist);
        fclose(fppun);
        if (fprdr != NULL) {
                fclose(fprdr);
        }
*/
        /* bye - normal exit */
        exit(0);
}

byte RdZ80(word addr)
{
	return(RAM[addr]);
}
void WrZ80(word addr, byte value)
{
	RAM[addr] = value;
}
byte InZ80(word addr)
{
	return(0);
}
void OutZ80(word addr, byte value)
{
	return;
}
word LoopZ80(Z80 *R)
{
	/* not used for now */
	return(0);
}

void PatchZ80(Z80 *R)
{
	ed_fe(R);
}


