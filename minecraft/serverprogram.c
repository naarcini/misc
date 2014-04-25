#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	// Variables
	const char *runcommand = "sh startserver.sh";
	const char *detectcommand = "ps -aux > detectserver.txt";
	const char *searchable = "java";
	char *output, *substr;
	int numbytes;
	FILE *in;

	do
	{
		if(system(detectcommand) != -1) {
			// Reading in file
			in = fopen("detectserver.txt", "r");
			
			if ( in == NULL) 
				printf("Couldn't find file\n"), exit(0);

			fseek(in, 0L, SEEK_END);
			numbytes = ftell(in);

			fseek(in, 0L, SEEK_SET);

			output = (char*)calloc(numbytes, sizeof(char));

			if (output == NULL)
				printf("Error: Memory issue\n"), exit(0);

			fread(output, sizeof(char), numbytes, in);
			fclose(in);

			printf("Successfully read in file\n");

			// Serach for substring
			substr = strstr(output, searchable);

			if(!substr)
				system(runcommand);

			substr = 0;

			free(output);
		}

		usleep(60000000);
	} while(1);

	return 0;
}
