
#include "stdio.h"
main()
{

	char buffer[50];
	int i;

	strcpy(buffer, "Hello, world from Hitech C\n");
	for (i = 0; buffer[i] != '\0'; i++) {
		bios(2,buffer[i]);
	}

} 

