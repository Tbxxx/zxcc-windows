#include "zxcc.h"
#include "zxbdos.h"
#include "zxdbdos.h"

extern int maxalt;	/* maximum number of alternative paths */
/* from libredir */
extern char redir_drive_prefix[16][CPM_MAXPATH];
extern char altfiles[6][256];


/* This file used to deal with all disc-based BDOS calls. 
  Now the calls have been moved into libcpmredir, it's a bit empty round
  here. 

   ZXCC does a few odd things when searching, to make Hi-Tech C behave
   properly.
*/

word x_fcb_open(byte *fcb, byte *dma)
{
	byte odrv;
	int count;
	word rv;
	static int first = 1;
	char typ[5];
	int n, ret;
	
    /* get filetype for azas/axln creat issue */
    for (n = 0; n < 3; n++) typ[n] = fcb[n+9] & 0x7F;

    typ[3] = 0;
/*
printf("open: typ = %s\n", typ);
*/

	for (count = 0; count != maxalt; count++) {
		strcpy(redir_drive_prefix[count],altfiles[count]);

		/* bump fcb pointer to next drive letter/directory location */
		*fcb = count;
#ifdef DEBUG
		fcb_dump(fcb);
#endif
/*
		printf("open:\n");
		fcb_dump(fcb);
*/

		rv = fcb_open(fcb, dma);
#if 0
printf("open: rv = %d, count = %d\n", rv, count);
if (rv == 0) {
	printf("open succeeded\n");
} else {
	printf("open failed\n");
}
#endif
/*
fcb_dump(fcb);
*/
		if (rv == 0) { /* open succeeded, drop out of for and return */
			break;
		}
	}
	return rv;
}



word x_fcb_stat(byte *fcb)
{
	int count;
	byte odrv;
	for (count = 0; count != maxalt; count++) {
		*fcb = count;	
        word rv = fcb_stat(fcb);
        if (rv == 0xFF) {
			continue;
		}
/*
printf("x_fcb_stat failed!\n");
fcb_dump(fcb);
*/

	}
	return 0xffff;
}

