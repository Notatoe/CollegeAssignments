// Noah Morris
// 10/11/2021
// cosc360
// tarc.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "jrb.h"
#include "dllist.h"

//filePath struct holds both the entire directory used and the file's name in one object for convenience
typedef struct filePath
{
    char directory[256];
    char directoryEnd[256];
} filePath;

//prints the file's size and bytes
int print(char* directory, char* directoryEnd, JRB inodes)
{
    //creates a stat struct called buffer
    struct stat buffer;
    if(stat(directory, &buffer) == -1)
    {
        fprintf(stderr, "%s: No such file or directory\n", directory);
        exit(1); 
    }
    //if the directory is a link, return 1
    else if(S_ISLNK(buffer.st_mode))
    {
        return 1;
    }

    //write the file name's length
    int length = strlen(directoryEnd);
    fwrite(&length, sizeof(int), 1, stdout);
    fwrite(directoryEnd, sizeof(char), length, stdout);

    //write the file's inode
    fwrite(&buffer.st_ino, sizeof(long), 1, stdout);

    //if an inode is not already present, write the information, else return 0
    if(jrb_find_int(inodes, buffer.st_ino) == NULL)
        jrb_insert_int(inodes, buffer.st_ino, new_jval_s(directory));
    else
        return 0;
    
    //write the file's mode
    fwrite(&buffer.st_mode, sizeof(int), 1, stdout);

    //write the file's modification time
    fwrite(&buffer.st_mtime, sizeof(long), 1, stdout);

    //return 0 if the file is a directory
    if(S_ISDIR(buffer.st_mode))
        return 0;

    //creates a second buffer for holding the contents of the file
    unsigned char buffer2[buffer.st_size];
    FILE *file = fopen(directory, "r");

    //if the file does not exist, exit the program
    if(file == NULL)
        exit(1);
    
    //read the file into the buffer and close the file
    fread(&buffer2, sizeof(unsigned char), buffer.st_size, file);
    fclose(file);

    //write the size and contents of the file
    fwrite(&buffer.st_size, sizeof(long), 1, stdout);
    fwrite(&buffer2, sizeof(unsigned char), buffer.st_size, stdout);

    return 0;
}

//parses the files within the directory
void iterate(filePath* fp, JRB inodes)
{
    struct dirent *temp;
    DIR *temp2 = opendir(fp->directory);

    //check to make sure the directory exists
    if(temp2 == NULL)
    {
        fprintf(stderr, "%s: No such file or directory\n", fp->directory);
        exit(1);
    }

    Dllist directories = new_dllist();
    char directory[1000];
    char directoryEnd[1000];

    //while the directory is not empty
    while((temp = readdir(temp2)) != NULL)
    {
        //skips instances of . and ..
        if(strcmp(temp->d_name, ".") == 0 || strcmp(temp->d_name, "..") == 0)
            continue;

        //creats the file path
        sprintf(directory, "%s/%s", fp->directory, temp->d_name);
        sprintf(directoryEnd, "%s/%s", fp->directoryEnd, temp->d_name);

        //prints out the file's information
        print(directory, directoryEnd, inodes);

        struct stat buffer;
        if(stat(directory, &buffer) == -1)
            continue;

        //if the file is a directory, add it to the directories list
        if(S_ISDIR(buffer.st_mode))
        {
            filePath *fp2 = (filePath*) malloc(sizeof(filePath));
            /* Continuously append directories onto the path */
            strcpy(fp2->directory, directory);
            strcpy(fp2->directoryEnd, directoryEnd);
            dll_append(directories, new_jval_v(fp2));
        }
    }

    closedir(temp2);

    //iterates all of the directories with the inputted directory
    Dllist temp3;
    dll_traverse(temp3, directories)
    {
        filePath* fp2 = (filePath*) temp3->val.v;
        iterate(fp2, inodes);
		free(fp2);
	}

    free_dllist(directories);
}

int main(int argc, char* argv[]) 
{
    //makes sure the program is used correctly
    if(argc != 2)
    {
        fprintf(stderr, "usage: tarc directory\n");
        exit(1);
    }

    //initialize the directory
    char* directory = strdup(argv[1]);

    //creates a token string that seperates the directory by every "/"
    char* token = strtok(directory, "/");
    char* temp;

    //finds the last bit of the directory which holds the file name
    while(token != NULL)
    {
        temp = token;
        token = strtok(NULL, "/");
    }

    //sets directoryEnd to temp
    char directoryEnd[256];
    strcpy(directoryEnd, temp);

    JRB inodes = make_jrb();

    //exits the program if the directory does not exist
    if(print(argv[1], directoryEnd, inodes) == 1)
        exit(1);

    //puts the directory and directoryEnd into a single struct
    filePath *fp = (filePath*) malloc(sizeof(filePath));
    strcpy(fp->directory, argv[1]);
    strcpy(fp->directoryEnd, directoryEnd);

    //iterates the directories using recursion
    iterate(fp, inodes);

    free(directory);
    //free(token);
    //free(temp);
    jrb_free_tree(inodes);
    free(fp);

    return 0;
}
