/* CCP support routines that do not vary
 * between the cpm.exe and standalone use
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* drive assignments for support files */
#include "drives.h"
#define MAXLINE 128

extern char altfiles[6][256];

/* Maximum length of a directory path */
#ifdef _POSIX_PATH_MAX
    #define CPM_MAXPATH _POSIX_PATH_MAX
#else
    #ifdef _MAX_PATH
        #define CPM_MAXPATH _MAX_PATH
    #else
        #define CPM_MAXPATH 260
    #endif
#endif

extern char redir_drive_prefix[16][CPM_MAXPATH];

#ifdef DEBUG
extern FILE *fpdebug;
#endif

/* ++tlb - added support routines - filename parsing,
 * convert strings to upper case, etc.
 */
int FCB_to_filename(unsigned char *p, char *name)
{
    int i;
	char buffer[25];
	int count = 0;

    for (i = 0; i < 8; ++i) {
		if (p[i+1] != ' ') {
		    buffer[count] = tolower(p[i+1]);
			count++;
		}
	}

	/* if one of the next three chars are non blank, put the period in */
	if (p[9] != ' ' || p[10] != ' ' || p[11] != ' ') {
		buffer[count] = '.';
		count++;
	}

	/* copy extension, if any */
	for (i = 0; i < 3; ++i) {
		if (p[i+9] != ' ') {
			buffer[count] = tolower(p[i+9]);
			count++;
		}
	}

	/* NULL terminate filename */ buffer[count] = '\0';
	/* return string to bdos */
	strcpy(name, buffer);
}

int filename_to_FCB(char *name, unsigned char *fcbptr)
{
	char *ptr;
	char nam[9];
	char typ[4];
	int x = 0;
	int count = 1;
	int y = 9;
	int k;
	char buffer[20];
	int len;
	char workcopy[129];
	unsigned char *file_nm_loc;

	file_nm_loc = fcbptr+1;

	/* null out 1st 16 bytes of fcb area -
	 * stray ' ' got in caused failure of seq read in bds c
	 */
	memset(fcbptr, 0, 16);

	/* build fcb */
	/* always drive a (also current drive) in this program
	 * if it doesn't open in current drive, BDOS C functions
	 * will look elsewhere
	 */

	/* make local writable working copy of name */
	strcpy(workcopy, name);

	/* now parse for period */
	ptr = strchr(workcopy, '.');
	if (ptr == NULL) {	/* no period in workcopy */
		strcpy(fcbptr, workcopy);
		spacepad(fcbptr, 11);
#if DEBUG
fprintf(fpdebug, "No filename extension...\n");
dump2_fcb(fcbptr);
#endif
		return(1);
	} else { /* period in workcopy - must process filename and ext */
		/* change period to NULL */
		*ptr = 0;
		/* bump ptr past NULL byte */
		ptr++;
		/* copy in filename */
		strcpy(fcbptr, workcopy);
		/* spacepad to 8 chars, if neccessary */
		spacepad(fcbptr, 8);

		/* add in extension */
		strcat(fcbptr, ptr);
		/* spacepad to 11, if necessary */
		spacepad(fcbptr, 11);
	}
#if DEBUG
fprintf(fpdebug, "Filename extension...\n");
dump2_fcb(fcbptr);
#endif
	return(1);
}
	
/*
 *	Convert a string to upper case and return TRUE.
 */

strupper(char *str)
{
	while(*str) {
		*str = toupper(*str);
		++str;
	}
	return(1);
}


/* spacepad - pad string with blanks to given length
 * The buffer better be big enough to hold it!
 *
 */

int spacepad(char *str, int len)
{
	int x,y;
	x = strlen(str);
	for (y = x; y != len; ++y) {
		str[y] = ' ';
		}
	str[len]='\0';
	return(1);
}

/* load paths for program name
 * Not an error if program name not known
 * In that case, it will use other
 *
 * It always loads at least two directory names into altfiles[0] and [1] 
 * They are to be sequentially searched for any open request.
 * The drive location is appended at the time of fopen()
 *
 * Changed 4/12/2015 to use support.cfg so users can change/add support
 * directories for programs/packages without needing a recompile or
 * C programming expertise.
 */
void set_altfiles(char *name)
{
	FILE *fps;
	char inbuf[MAXLINE];
	char *progptr;
	char *dirptr;
	int len;

	/* Auto path add depending on filename
	 * If the program is not known, generic and other are used.
	 */
	/* first, always use local directory for all searches
	 * that is done by default and does not need anything to do
	 */
	/* last, use other directory for file search - that's [1] of
	 * altfiles 2d string array
 	 * altfiles[0] is reserved for a specific support directory
	 * or GENERIC if there isn't one.
	 */
	strcpy(altfiles[0], "./");	/* first location always local directory */
	strcpy(redir_drive_prefix[0], "./");
	strcpy(altfiles[1], "./"); /* drive A: same as default */
	strcpy(redir_drive_prefix[1], "./");

	/* [2] (the specific support directory) filled in below */
	
	strcpy(altfiles[3], CPMCOM);
	strcpy(redir_drive_prefix[2], CPMCOM);
	
	strcpy(altfiles[4], CPMCOM); 
	strcpy(redir_drive_prefix[4], CPMCOM);

	if ((fps = fopen("support.cfg", "r")) == NULL) {
		fprintf(stderr, "Please create a support.cfg file\n");
		fprintf(stderr, "It may be empty\n");
		exit(1);
	}
	while ((fgets(inbuf, MAXLINE-1, fps)) != NULL) {
		if (strlen(inbuf) < 10) {
			/* skip invalid (or trailing blank!) lines */
			continue;
		}
		if (inbuf[0] == '#') {
			/* skip comment line */
			continue;
		}
		/* strip newline */
		inbuf[strlen(inbuf)-1] = '\0';

		/* get both fields */
		progptr = strtok(inbuf, ",\n");
		dirptr = strtok(NULL, ",\n");
		/* find matching program name or prefix and store */
		if (strchr(inbuf, '*')) {	/* use strncmp for wildcard */
			if (strncmp(name, progptr, strlen(progptr)-1) == 0) {
				/* found it - load with target directory */
				strcpy(altfiles[2], dirptr);
				strcpy(redir_drive_prefix[2], dirptr);
				/* done! */
				break;
			}
		} else {	/* no wildcard */
			if (strcmp(name, progptr) == 0) {
				/* found it - load with target directory */
				strcpy(altfiles[2], dirptr);
				strcpy(redir_drive_prefix[2], dirptr);
				/* done! */
				break;
			}
		}
	}
	fclose(fps);
	return;
		
}
void get_ext(char *fn, char *ext)
{
	char *ptr;
	ptr = strchr(fn, '.');
	if (ptr == NULL) {
		*ext = '\0';
		return;
	} else {
		ptr++; /* move past period */
		strcpy(ext, ptr);
		return;
	}
}

