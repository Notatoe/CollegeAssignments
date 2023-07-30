// Noah Morris
// 9/15/2021
// cosc360
// 12p3.c

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "jrb.h"
#include "fields.h"
#include "dllist.h"

//ip struct given with printed and key added
typedef struct
{
	unsigned char address[4];
	Dllist names;
	int printed;
	char *key;

} ip;

//constructs a default ip struct
ip *new_ip()
{
    ip *IP = malloc(sizeof(*IP));
    IP->names = new_dllist();
    IP->printed = 0;
    IP->key = "";
    return IP;
}

int main(int argc, char const *argv[])
{
	//creates and opens the file
	int file = open("converted", O_RDONLY);

	//checks to make sure the file exists
	if(file < 0)
	{
		perror("File unable to be opened");
		return 1;
	}

	//creates a bunch of variables that will be used over the course of reading in the file
	//character just holds onto on char at a time while buffer is used to hold onto the ip address
	unsigned char *character, buffer[4];
	character = malloc(1);
	//names is the number of names being used while just name holds onto a whole name to be inserted
	int names = 0;
	char *name;

	//buffer added to version 3 for increased speed
	unsigned char *bufferV3;
	bufferV3 = malloc(350000);

	//size of the inputted file
	int filesize = read(file, bufferV3, 350000);

	//IP is the an ip struct that will be inserted into the JRB tree
	ip *IP;

	//JRB tree that will be used to hold in all of the information from the file
	JRB host = make_jrb();

	//current char within the file
	int j = 0;
	//until the file has been gone all the way through
	while(j != filesize)
	{
		//sets and resets IP for every iteration of reading the file in
		IP = new_ip();

		buffer[0] = bufferV3[j];
        j++;
		buffer[1] = bufferV3[j];
        j++;
		buffer[2] = bufferV3[j];
        j++;
		buffer[3] = bufferV3[j];
        j++;

		//reads the buffer into the current IP struct
		for(int i = 0; i < 4; i++)
			IP->address[i] = buffer[i];

		//reads in the next four chars from the file which give how many names are on the current IP address
		for(int i = 0; i < 4; i++)
		{
			character = &(bufferV3[j]);
			j++;
			int char_count = *character;
			
			names = 0;
			switch(i)
			{
				case 0:
					names += char_count * 1000;
					break;
				case 1:
				case 2:
					names += char_count * 100;
					break;
				case 3:
					names += char_count;
			}
		}

		//adds the names to the current IP
		for(int i = 0; i < names; i++)
		{
			//allocates a lot of memory because it can be assumed that a name will contain less than 100 characters
			name = (char *) malloc(100);

			//current is the current number of characters in the name
			int current = 0;

			//reads in characterrs until an empty char is given
			while(1)
			{
				character = &bufferV3[j];
				j++;

				int charvalue = *character;

				//if charvalue is not a newline
				if(charvalue != 0)
				{
					//if this is the first char in the name, allocate memory for it
					if(charvalue == 46 && current == 0)
					{
						char *character2;
						character2 = (char *) malloc(100);
						memset(character2, '\0', sizeof(character2));
						strcpy(character2, name);
						dll_append(IP->names, new_jval_s(character2));
						current++;
					}
					//add the character to the word
					strncat(name, character, 1);
				}
				//if charvalue is a newline
				else
				{
					//insert the current name into the host jrb tree by allocating memory for it and break out of the loop
					strncat(name, character, 1);
					dll_append(IP->names, new_jval_s(name));
					
					//sets up the key with the current name
					IP->key = (char *) malloc(sizeof(char) *(strlen(name)));
					char *name2 = (char *) malloc(sizeof(char) *(strlen(name)));
					for(int i = 0; i < strlen(name); i++)
						name2[i] = name[i];
					strcpy(IP->key, name2);

					//inserts into the host jrb tree
					jrb_insert_str(host, IP->key, new_jval_v((void *) IP));
					break;
				}
			}
		}
	}

	//found that is set to 0 if the ip has not been found, 1 if it has
	int found = 0;
	printf("Hosts all read in\n\n");

	//input string that is used to hold the inputted value
	char *input;
	input = (char *) malloc(100);
	printf("Enter host name: ");

	//while loop that continues until the user inputs ctrl+d
	while(scanf("%s", input) != EOF)
	{
		//resets found and creates a jrb for traversing
		found = 0;
		JRB jrb;

		//traverses the whole read in host jrb tree for the inputted name
		jrb_traverse(jrb, host)
		{
			//IP struct created to hold the current node within the jrb and a dllist to traverse the current IP's dllist
			ip *IP2 = (ip *)jrb->val.v;
			Dllist list;
			
			//traverse the current IP's names list
			dll_traverse(list, IP2->names)
			{
				//compares the current name in the dllist to the inputted name as well makes sure the current name has not been used to print before
				if((!strcmp(list->val.s, input)) && (IP2->printed == 0))
				{
					//increaments found and prints the IP and names
					found++;
					printf("%d.%d.%d.%d: ", IP2->address[0], IP2->address[1], IP2->address[2], IP2->address[3]);
					Dllist list2;
					dll_traverse(list2, IP2->names)
						printf(" %s", list2->val.s);
					printf("\n\n");

					//sets printed to 1 as it has been printed
					IP2->printed = 1;
				}
			}
		}

		//if the name was not found, the key does not exist and prints reflecting that
		if(found == 0)
			printf("no key %s\n\n", input);

		//resets the search and sets all IPs to not have been printed
		printf("Enter host name:  ");
		jrb_traverse(jrb, host)
		{
			ip *IP2 = (ip *)jrb->val.v;
			IP2->printed = 0;
		}
	}
	printf("\n");
	
	//freeing memory and closing the program
	
	//FIX THIS SO IT DOESN'T BREAK THE PROGRAM
	/*ip *temp;
	JRB temp2;
	jrb_traverse(temp2, host)
	{
		temp = (ip *)temp2->val.v;
		free(temp->address);
		free_dllist(temp->names);
		free(temp->printed);
		free(temp->key);
	}
	free(temp);
	jrb_free_tree(host);*/
	free(IP);
	free(name);

	//if the closing the file doesn't return less than 0, then end as an error
	if(close(file) < 0)
		return 1;
	return 0;
}
