void cpmbios(byte *a, byte *b, byte *c, byte *d, byte *e, byte *f, 
	     byte *h, byte *l, word *pc, word *ix, word *iy)
{
int func;
int retv;
	func = *(b);
#ifdef DEBUG
Msg("BIOS function called = %d\n", func);
#endif
	switch(func)	/* BIOS function */
	{
		/* exit with cold start request */
		case 0:
#ifdef DEBUG
			Msg("Cold start requested in cpmbios\n");
#endif
			/* clean up and exit */
			goodbye(99);
		break;

		/* exit with warm start request */
		case 1:
#ifdef DEBUG
			Msg("Warm start requested in cpmbios\n");
#endif
			/* clean up and exit */
			goodbye(99);
		break;

		case 2:		/* CONST */
			*a = x_const() ? 0xFF : 0x00;

			/* return must be in A reg */
#ifdef DEBUG
			Msg("const returns %d\n", *a);
#endif
		break;

		case 3: 	/* CONIN */
			*a = x_conin() & 0xFF;
			if (*a == 127) {
				/* ++tlb - needed for mbasic/obasic */
				*a = 8;
			}
			/* xlate for mbasic/obasic from lf to cr
			 * if CYGW
			 */
#ifdef CYGW
			if (strcmp("mbasic", progname) == 0 || strcmp("obasic",
				progname) == 0) {
			    if (*a == 10) {
				/* cygwin is a Unix believer - lf
				 * terminates lines. Change to CR to
				 * keep mbasic/obasic happy.  mbasic is
				 * a CP/M believer and you get a CR from
				 * a terminal.  Need to be sure getting LF
				 * doesn't break anything else i.e. BDOS
				 * or else make the xlate for all CYGW
				 * compiles.
				 * This must be done in BIOS 'cuz that's
				 * mbasic/obasic does all it's terminal i/o.
				 */
				*a = 13;
			    }
			}
	
#endif
			/* function returns char in A register */
#ifdef DEBUG
Msg("bios conin after processing %c\n", *a);
dump_regs(*a,*b,*c,*d,*e,*f,*h,*l,*pc,*ix,*iy);
#endif
		break;

		case 4:		/* CONOUT */
			/* output char in register C */
			x_conot(*c);

		break;

		case 5:		/* PRINTER OUTPUT */
		if ((lstout = fopen("lstout", "a")) == NULL) {
			fprintf(stderr, "Open fail on lstout\n");
			exit(3);
		}
		/* send char to printer file via low-level bios call */
		x_lstot(*c);
		fclose(lstout);
		break;

		case 20:	/* DEVTBL */
		setw(l, h, 0xFFFF);
		break;

		case 22:	/* DRVTBL */
		setw(l, h, 0xFFFF);
		break;

		case 26:	/* TIME */
		RAM[0xFEF8] = get_time(0xFEF4);
		break;	

		case 30:	/* USERF!!! */
#ifdef USE_CPMIO
		cpm_bdos_110('$');
		cpm_bdos_9("This program has attempted to call USERF, "
                           "which is not implemented\r\n$");
#else
		printf("This program has attempted to call USERF, which "
                       "is not implemented.\n");
#endif
		zxcc_term();
		zxcc_exit(1);
		break;

		default:
#ifdef USE_CPMIO
                cpm_scr_unit();
#endif
#ifdef USE_CPMGSX
                gsx_deinit();
#endif

                fprintf(stderr,"%s: Unsupported BIOS call %d\n", progname, func);
#ifdef DEBUG
		dump_regs(*a,*b,*c,*d,*e,*f,*h,*l,*pc,*ix,*iy);
#endif
                zxcc_exit(1);
	}
}
