/* originally from the bitsavers/convergent directory
 *
 * Used stdin/stdout that won't work in Windows.  Files
 * must be opened explicity in binary mode for both input and output
 *
 * Testing: Converts *.IMD file identical to IMDU /B as verified
 * by both size and an MD5 cryptographic hash.
 *
 * Tom Burnett
 * December, 2013
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
 * IMD image format
 * 
 * IMD v.v: dd/mm/yyy hh:mm:ss (ascii header)
 * comment terminated with 0x1a
 * for each track
 *  char mode (0-5)
 *  char cylinder
 *  char head
 *  char sector count
 *  char sector size (0-6)
 *  sector numbering map
 *  optional cylinder map
 *  optional head map
 *  sector data records (type) (val, or data)
 */

char *modetbl[] = { "500K FM", "300K FM", "250K FM", "500K MFM", "300K MFM", "250K MFM" };

FILE *fpin, *fpout;

int main(int argc, char *argv[])
{
	unsigned char sectbl[32];
	unsigned char sectyp[32];
	unsigned char secdata[64][8192];
	unsigned int mode, cyl, hd, seccnt, secsiz;
	int i, j;
	unsigned char c, value;


	if (argc != 3) {
		fprintf(stderr, "Usage: imd2raw <infile.imd> <outfile.dsk>\n");
		exit(1);
	}

	if ((fpin = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Open failure on %s for read.\n", argv[1]);
		exit(2);
	}

	if ((fpout = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "Open failure on %s for write.\n", argv[2]);
		exit(3);
	}

	if( (fgetc(fpin) != 'I') || (fgetc(fpin) != 'M') || (fgetc(fpin) != 'D') ) {
	  fprintf(stderr,"File doesn't start with 'IMD'\n");
	  exit(4);
	}	

	while(1){
	 c = fgetc(fpin);
	 if(c == 0x1a)
	  break;
	}

	while(1){
	 c = fgetc(fpin);
	 if(feof(fpin)) break;
	 mode   = c;
	 if(mode > 6){
	  fprintf(stderr,"Stream out of sync at mode, got 0x%x\n", mode);
	  exit(EXIT_FAILURE);
	 }
	 cyl    = fgetc(fpin);
	 if(cyl > 80){
	  fprintf(stderr,"Stream out of sync at cyl, got 0x%x\n", cyl);
	  exit(5);
	 }
	 hd     = fgetc(fpin);
	 if(hd > 1){
	  fprintf(stderr,"Stream out of sync at hd, got %d\n", hd);
	  exit(6);
	 }
	 seccnt = fgetc(fpin);

	 c = fgetc(fpin);

	 switch(c) {
	  case 0:
	   secsiz = 128;
	   break;
	  case 1:
	   secsiz = 256;
	   break;
	  case 2:
	   secsiz = 512;
	   break;
	  case 3:
	   secsiz = 1024;
	   break;
	  case 4:
	   secsiz = 2048;
	   break;
	  case 5:
	   secsiz = 4096;
	   break;
	  case 6:
	   secsiz = 8192;
	   break;
	 }

	 // fprintf(stderr,"Cyl:%d Hd:%d %s %d sectors size %d\n", cyl, hd, modetbl[mode], seccnt, secsiz);

	 // copy interleave table
	 for (i=0; i < seccnt; i++)
	  sectbl[i] = fgetc(fpin);

	 // fprintf(stderr,"Tbl ");
	 // for (i=0; i < seccnt; i++) fprintf(stderr,"%d ",sectbl[i]);
	 // fprintf(stderr, "\n");

	 // copy sector information indexed by the sector number

	 for (i=0; i < seccnt; i++){
	  c = fgetc(fpin);

	  switch(c){
	   case 0:			// sector data unavailable - could not be read
           case 5:
           case 7:
	    sectyp[i] = 'X';
	    for(j=0; j < secsiz; j++)
	     secdata[sectbl[i]][j] = 0xE5;
	     // fprintf(stderr,"Cyl %d Hd %d Sec %d bad, type %d\n",cyl,hd,sectbl[i],c);
	    break;

	   case 1:			// normal data 'secsiz' bytes follow
	    sectyp[i] = '.';
	    for(j=0; j < secsiz; j++)
	     secdata[sectbl[i]][j] = fgetc(fpin);
	    break;

	   case 3:			// data with 'deleted data' address mark
	    sectyp[i] = 'd';	
	    for(j=0; j < secsiz; j++)
	     secdata[sectbl[i]][j] = fgetc(fpin);
	    break;

	   case 2:			// compressed with value in next byte
           case 4:
           case 6:
           case 8:
	    sectyp[i] = 'C';
	    value = fgetc(fpin);
	    for(j=0; j < secsiz; j++)
	     secdata[sectbl[i]][j] = value;
	    // fprintf(stderr,"Cyl %d Hd %d Sec %d all %x\n",cyl,hd,sectbl[i],value);
	    break;
	  }
	 }
         fprintf(stderr,"Cyl %02d Hd %d %-4d ", cyl, hd, secsiz );
	 for(i=0; i<seccnt; i++){
	  fprintf(stderr,"%c",sectyp[i]);
	  for(j=0; j<secsiz; j++){
	   fputc(secdata[sectbl[i]][j], fpout);
	  }
	 }
	 for(i=0; i<seccnt; i++){
	  fprintf(stderr," %-2d",sectbl[i]);
	 }
	 fprintf(stderr,"\n");
	} 
	fclose(fpin);
	fclose(fpout);
	return(0);
}

