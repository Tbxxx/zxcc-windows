/* ccp.c
 * Poor Man's Console Command Processor with as much
 * CP/M 3 functionality as possible
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* globals for writable args - accessible anywhere in program */
char arg[20][129]; /* arguments - way overkill, but any one arg could be 128 */
int agc;
char allargs[129];	/* all arguments concatenated */
int num;			/* number of bytes read from CP/M executable file */

extern unsigned char RAM[0x10000];

#ifdef DEBUG
extern FILE *fpdebug;
#endif

/* Called with flag = 0, it's for standalone operation where the
 * program name is argv[0], etc.  So, for example when running
 * "m80 filename,filename=filename" directly from the command line,
 * call ccp() with flag = 0;
 *
 * Called with flag = 1, it's for the CP/M binary used for one-time
 * running of a program.  So, for example, when running a program
 * "test" after compilation/assembly via "cpm test <optional args>",
 * call ccp with flag = 1, otherwise 0 for native program name
 * invocation.
 */
ccp(int argc, char *argv[], int flag)
{
	char *pCmd, *str, *ptr;
	int n, x, c, lentot, i, count = 0, num_filenames = 0;
	int j, len, addr, first = 1; /* first = flag for strtok() call */

	pCmd = (char *)(RAM+0x81);

	/* Tom's poor man's Console Command Processor section -
	 * New version for CP/M 3.0 - Much more exact requirements
	 * in parsing filenames and setting up the first two
	 * recognized filenames in FCB's at 5ch and 6ch.
	 *
	 * Still need to complete CP/M 3.0 BDOS parsing requirements.
	 * Might be easiest to steal DRI code that does it in assembly
	 * and check for BDOS call and let DRI code do it.
	 * I dunno yet.
	 */
	if (flag == 0) {
		agc = 2; /* at least two command arguments if 1 is eliminated
		 		  * with a specific test.  Specific test is below before
		 		  * the loop on number of arguments
		 		  */
	} else if (flag == 1) {
		/* at least three if two are eliminated as above */
		agc = 3;
	}

	if (argc == agc-1) {  /* specific test - nothing extra on command line? */
 		/* need to save argv[0] or argv[1] for signal/cntrl-c handling
		 * e.g. mbasic/obasic even if no args are given
		 */
		strcpy(arg[0], argv[flag]);
        RAM[0x80] = 0; /* length byte */
        RAM[0x81] = 0; /* no command tail - done! */
	} else {
		/* still must save name of program */
		strcpy(arg[0], argv[flag]);

		
		while (agc != argc+1) {	/* argc at least two/three */

			/* make writable copy for strtok() of argv[agc-1] */
			strcpy(arg[agc-1], argv[agc-1]);

 			/* everything is upper case in CP/M */
			strupper(arg[agc-1]);
	
			/* note - first (agc == 2, 1st argument to the
			 * program) it's strcpy() to build the command
			 * tail string,  All others after that are strcat()
			 * to append to the command tail string.
			 */

			if ((agc == 2 && flag == 0) || (agc == 3 && flag == 1)) {
				strcpy(allargs, arg[agc-1]);
			} else {
				strcat(allargs, " "); /* separate by spaces */
				strcat(allargs, arg[agc-1]);
			}

			/* find string before token list below
			 * the strtok string for delimiters is
			 * from "CPM 3 Programmer's Guide by DRI
			 */
			/* give ptr meaningless address so while will work */
			ptr = (char *)0x01;
			first = 1; /* first flag for strtok() call args */
			while (ptr != NULL) {
				if (first) {
					ptr = strtok(arg[agc-1], "=,[]<> /\t");
					first = 0;
				} else  {
					ptr = strtok(NULL, "=,[]<> /\t");
				}
					
				if (ptr == NULL) {
					break;
				} else {
					/* CCP only processes the first
					 * two filenames, others are in
					 * the command tail for the
					 * individual application to process
					 */
					if (num_filenames == 0) { /* its the first */
 						/* set up FCB for first filename
						/* 5c gets zero - always drive a: */
						/* filename to 0x5d */
						*(RAM+0x5c) = '\0';
						filename_to_FCB(ptr, &RAM[0x5d]);
						num_filenames++; /* bump counter */
					} else if (num_filenames == 1) {
						/* else it's the 2nd */
 						/* set up FCB for 2nd
						 * filename  arg at 0x6c
						 */
						/* 6c gets zero - always drive a: */
						/* arg at 0x6d */
						*(RAM+0x6c) = '\0';
						filename_to_FCB(ptr,&RAM[0x6d]);
						/* bump counter */
						num_filenames++;
					}
				}
			}
			agc++;	/* bump agc to process next argument */
		}
	}

	strcpy (pCmd,allargs);
	/* Truncate to fit the buffer in case it went into TPA */
	*(pCmd+0x7F) = 0;
	RAM[0x80] = strlen(pCmd);
	/* End Poor Man's CCP */

#ifdef DEBUG
Msg("CCP: Length byte is %d - Command Tail is [%s]\n", strlen(pCmd), pCmd);
#endif
	return(0);
}


