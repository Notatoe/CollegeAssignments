// Noah Morris
// 9/28/2021
// cosc360
// fakemake.c

#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv) 
{
    if(argc > 2)
	{
        fprintf(stderr, "usage: fakemake [description-file]\n");
        exit(1);
    }

    /* Default input file to "fmakefile", then see if user specified a different file */
    char* file = "fmakefile";

    if(argc == 2)
        inputfile = argv[1];

	IS input = new_inputstruct(file);

	if(input == NULL)
	{
		fprintf(stderr, "fakemake: %s: No such file or directory\n", input);
		exit(1);
	}

	Dllist sourceFiles = new_dllist();
	Dllist headerFiles = new_dllist();
	char* executable;
	Dllist flags = new_dllist();
	Dllist libraries = new_dllist();

	while(get_line(input) >= 0)
	{
		if(input->NF <= 1)
			continue;

		char *type = is->fields[0];

		if(equal(type, "C"))
		{
			for(int i = 0; i < input->NF; i++)
			{
				dll_append(sourceFiles, new_jval_s(strdup(is->fields[i])));
			}
		}

	}
}
