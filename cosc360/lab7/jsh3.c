// Noah Morris
// 11/22/2021
// cosc360
// jsh3.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fields.h"
#include "jrb.h"

//function checks for redirections and opens files accordingly
//BREAKS THE PROGRAM AS A FUNCTION SO NOW IT IS HARD CODED
//void redirection_checker(int *redirection, char **arguments, int *read, int *write, IS is, char *out)

//calls the command in the argument and exits the program
void callCommand(char **arguments)
{
	execvp(arguments[0], arguments);
	perror(arguments[0]);
	exit(1);
}

//closes and copys files if there is a redirection and exist
void closeFiles(int redirection, int *read, int *write)
{
	if(redirection == 1)
	{
		if(*read != -1)
			dup2(*read, 0);
		close(*read);

		if(*write != -1)
			dup2(*write, 1);
		close(*write);
	}
}

int main(int argc, char ** argv)
{
	//checks to make sure a valid number of arguments is used
	if(argc > 2) 
	{
		fprintf(stderr, "usage jsh3 [prompt]\n");
		exit(1);
	}

	//if argv[1] is NULL, display default jsh prompt
	if(argv[1] == NULL)
		printf("jsh: ");
	//else if argv[1] is not "-"", then print out the prompt using argv[1]
	else if(strcmp(argv[1], "-") != 0)
		printf("%s: ", argv[1]);

	//redirection is used to keep track of if there was a redirection present, 0 = none, 1 = one or more
	int redirection = 0;
	char **arguments;
	JRB ampersandTree = make_jrb();
	IS is = new_inputstruct(NULL);

	//while loop that reads in the input
	while(get_line(is) >= 0)
	{
		//reprints the prompt if needed
		if(argv[1] == NULL)
			printf("jsh: ");
		else if(strcmp(argv[1], "-") != 0)
			printf("%s: ", argv[1]);

		//ampersand is 0 as long as an ampersand is not present, opperates similarly to redirection
		int ampersand = 0;

		//file modes for when file redirection are present and a file needs to be opened to a specific mode
		int read = -1;
		int write = -1;
		char *out = NULL;

		//if a command is present
		if(is->NF > 0)
		{
			//if the command is only one word
			if(is->NF == 1)
			{
				//obtains the path and sets the begining of arguments
				char *path = is->fields[0];
				arguments = (char**) malloc(sizeof(char*)*2);
				arguments[0] = path;
				arguments[1] = NULL;
			}
			//if the command is longer than one word
			else
			{
				//check if the command line ends with a ampersand
				if(strcmp(is->fields[is->NF-1], "&") == 0)
				{
					//set ampsersand to 1 and sets arguments accordingly
					ampersand = 1;
					arguments = (char**) malloc(sizeof(char*)*is->NF);
					for(int i = 0; i < is->NF - 1; i++)
					{
						arguments[i] = is->fields[i];
					}
					arguments[is->NF - 1] = NULL;
				}
				//else the command line does not end in an ampersand
				else
				{ 
					//no ampersand accounted for, sets arguments accordingly
					arguments = (char**) malloc(sizeof(char*)*(is->NF + 1));
					for(int i = 0; i < is->NF; i++)
					{
						arguments[i] = is->fields[i];
					}
					arguments[is->NF] = NULL;
				}

				//reset redirection to 0 and initailze a temperary int that is used for adding words to arguments
				redirection = 0;

				//BROKE THE PROGRAM AS FUNCTION SO NOW IT IS HARD CODED
				//redirection_checker(&redirection, arguments, &read, &write, is, out);
				int temp = 0;

				//checks for redirections
				for(int i = 0; i < is->NF; i++)
				{	
					//if NULL, break for there is no redirection applicable
					if(arguments[i] == NULL)
						break;
	
					//if < is found
					if(strcmp(arguments[i], "<") == 0)
					{
						//open the file in read and sets the redirection and file in arguments to NULL
						read = open(arguments[i + 1], O_RDONLY);
						redirection = 1;
						arguments[i] = NULL;
						i++;
						arguments[i] = NULL;
					}
					//else if > is found
					else if(strcmp(arguments[i], ">") == 0)
					{
						//open the file in write and sets the redirection and file in arguments to NULL
						out = arguments[i + 1];

						write = open(arguments[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
						redirection = 1;
						arguments[i] = NULL;
					}
					//else if >> is found
					else if(strcmp(arguments[i], ">>") == 0)
					{
						//open the file in write, but set to append, and sets the redirection and file in arguments to NULL
						write = open(arguments[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
						redirection = 1;
						arguments[i] = NULL;
						i++;
						arguments[i] = NULL;
					}
					//else if | is found in the input struct
					else if(strcmp(arguments[i],"|") ==0)
					{
						//resets the arguments everytime pipe is called
						arguments[temp] = NULL;
						temp = 0;

						//
						int fd[2];
						if(pipe(fd) < 0)
						{
							perror("Pipe ERROR");
							exit(1);
						}
	
						//fork the child process and check if it returns 0
						int cpid = fork();
						if(cpid == 0)
						{
							//if read is open
							if(read != -1)
							{  
								//if dup2 returns 0 with read and 0, return an error and exit the program
								if(dup2(read, 0) != 0)
								{
									perror("dup2(read) ERROR");
									exit(1);	
								}
								//close read
								close(read);
								read = -1;
							}
	
							//if dup2 does not return 1 with fd[1] and 1, return an error and exit the program
							if(dup2(fd[1], 1) != 1)
							{  // redirect the stdout to command or next pipe
								perror("fd[1] ERROR");
								exit(1);
							}

							//close fd
							close(fd[0]);
							close(fd[1]);
	
							//calls the command
							callCommand(arguments);
						}
						//else, close read if open and redirect fd into read
						else
						{
							if(read != -1) 
								close(read);

							read = fd[0];
							close(fd[1]);
						}
					}
					else
					{
						//adds the argument to arguments
						arguments[temp] = is->fields[i];
						temp++;  
					}
				}
			}

			//removes last word on the command if a > redirection was present
			if(out != NULL)
			{
				int temp = 0;
				//goes down the arguments until the word at out is found
				while(arguments[temp] != out)
				{
					//if the end of arguments is reached, break to avoid infinite loop
					if(arguments[temp] == NULL)
						break;
					//else if out is reached, set it to NULL
					else if(arguments[temp] == out) 
						arguments[temp] = NULL;
						
					temp++;
				}
				//sets the word at temp to NULL
				arguments[temp] = NULL;
			}

			//if there was no ampersands
			if(ampersand == 0)
			{
				//fork the process
				int pid = fork();
				//if pid is 0
				if(pid == 0)
				{
					//if there was a redirection
					closeFiles(redirection, &read, &write);

					//calls the command
					callCommand(arguments);
				}
				//else, wait
				else
				{  
					int stat;
					int child = wait(&stat);

					//keep waiting until child == pid
					while(child != pid)
					{
						//looks for the child in the JRB tree
						JRB temp2 = jrb_find_int(ampersandTree, child);
						//if it does not exist remove it from the process
						if(temp2 != NULL)
						{
							jrb_delete_node(temp2);
						}
						child = wait(&stat);
					}
				}
			}
			//else, there is an ampersand
			else
			{ 
				//fork the process
				int pid = fork();
				if(pid == 0)
				{
					//inserts into the JRB tree
					jrb_insert_int(ampersandTree, pid, new_jval_i(1));  // add ampersand node into tree keyed on pid

					//if there were redirections
					closeFiles(redirection, &read, &write);

					//calls the command
					callCommand(arguments);
				}
			}
		}

		//resets read and write
		close(read);
		close(write);
	}	

	jettison_inputstruct(is);
	return 0;
}
