#include "stdio.h"
char buffer="Hello, world from Aztec C.\n";
main()
{
	int i;
	for (i = 0; buffer[i] != '\0'; i++) {
		bdos(2,buffer[i]);
	}
	exit(0);
}

