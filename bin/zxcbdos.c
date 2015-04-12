#include "zxcc.h"
#include "zxbdos.h"
#include "zxcbdos.h"

/* Line input */
dummy()
{
}

#if 0
void bdos_rdline(word line, word *PC)
{
	char *buf;

	if (!line) line = cpm_dma;
	else RAM[line + 1] = 0;

	buf = (char *)&RAM[line];

	if (cpm_bdos_10(buf)) *PC = 0;
}

/* else */
void bdos_rdline(word line, word *PC)
{
	int maxlen;

	if (!line) line = cpm_dma;
	maxlen = RAM[line];

	fgets((char *)(RAM + line + 2), maxlen, stdin);
	RAM[line + 1] = strlen((char *)(RAM + line + 2)) - 1;	

	Msg("Input: [%d] %-*.*s\n", RAM[line + 1], RAM[line + 1], RAM[line +1], (char *)(RAM+line+2));
}

int cpm_bdos_6(byte e)
{
	int c;

	switch(e)
	{
#ifdef __MSDOS__
		case 0xFF:	/* Not implemented */
		if (kbhit()) return getch();
		return 0;

		case 0xFE:
		return kbhit();	

		case 0xFD:
		c = getch();
		return c;

		default:
		putch(e);
		break;
#else /* __MSDOS__ */
		case 0xFF:	/* Not implemented */
		return 0;

		case 0xFE:
		return 0;	

		case 0xFD:
		c = getchar();
		return c;

		default:
		putchar(e);
		break;
	}
	return 0;
}
#endif
#endif

