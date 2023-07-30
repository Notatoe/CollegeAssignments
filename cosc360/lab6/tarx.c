// Noah Morris
// 10/11/2021
// cosc360
// tarx.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "jrb.h"
#include "dllist.h"
#include <utime.h>
#include <unistd.h>

//fileInfo struct holds information on a file
typedef struct fileInfo 
{
	int length, mode;
    long inode, mtime, size;
    char filename[256];
    struct fileInfo *link;
    unsigned char* contents;
} fileInfo;

//eads the next file from the tarc file given via stdin
int nextFile(fileInfo *info, JRB inodes) {
    // Read name length
    int length;

    //if the length is nonexistant, the end of file has been reached and return -1
    if(fread(&length, sizeof(int), 1, stdin) != 1) 
        return -1;
    info->length = length;

    //makes sure the length is positive or else memory can't be allocated for it
    if(length <= 0) 
    {
        fprintf(stderr, "ERROR: File name size is %d, which can not be allocated.\n", length);
        exit(1);
    }

    //reads in the file name, returns an error if the name is not the same length as length
    char filename[256];
    if(fread(&filename, sizeof(char), length, stdin) != length) 
    {
        fprintf(stderr, "ERROR: incorrect file name length\n");
        exit(1);
    }
    filename[length] = '\0';
    strcpy(info->filename, filename);

    //reads in the inode and returns an error if it could not be read in
    long inode;
    if(fread(&inode, sizeof(long), 1, stdin) != 1) 
    {
        fprintf(stderr, "ERROR: in tarc file, %s. Could not read inode\n", info->filename);
        exit(1);
    }
    info->inode = inode;

    //looks for the inode in inodes to see if it has already been processed, if so set the link pointer and return 0
    JRB found = jrb_find_int(inodes, inode);
    if(found != NULL) 
    {
        info->link = (fileInfo*) jrb_val(found).v;
        return 0;
    }

    //insert the inode with no link
    info->link = NULL;
    jrb_insert_int(inodes, inode, new_jval_v(info));

    //read in the mode, if it could not be found return an error
    int mode;
    if(fread(&mode, sizeof(int), 1, stdin) != 1)
    {
        fprintf(stderr, "ERROR: in tarc file, %s. Could not read mode\n", info->filename);
        exit(1);
    }
    info->mode = mode;

    //read in the mtime, if it could not be found return an error
    long mtime;
    if(fread(&mtime, sizeof(long), 1, stdin) != 1)
    {
        fprintf(stderr, "ERROR: in tarc file for %s. Could not read mtime\n", info->filename);
        exit(1);
    }
    info->mtime = mtime;

    //if the file is a directory, return 0
    if(S_ISDIR(mode))
        return 0;

    //reads in the file size, if it could not be found return an error
    long size;
    if(fread(&size, sizeof(long), 1, stdin) != 1)
    {
        fprintf(stderr, "ERROR: in tarc file, %s. Could not read size\n", info->filename);
        exit(1);
    }
    info->size = size;

    //read in the file of the given size, if the size does not match return an error
    unsigned char buf[size];
    if(fread(&buf, sizeof(unsigned char), size, stdin) != size) 
    {
        fprintf(stderr, "ERROR: in tarc file, %s. Non-matching size\n", info->filename);
        exit(1);
    }

    //inputs the file contents
    info->contents = (unsigned char*) malloc(sizeof(unsigned char) * size);
    memcpy(info->contents, buf, size);

    return 0;
}

//creates the directories, files, and modes and frees the contents
void create(Dllist directories, Dllist files)
{
    //creates a temperary dllist that is used to traverse the other dllist
    Dllist temp;

    //creates the directories
    dll_traverse(temp, directories)
    {
        fileInfo* info = (fileInfo*) temp->val.v;
        mkdir(info->filename, S_IRWXU | S_IRWXG | S_IRWXO);
	}

    //create the files with the correct links
    dll_traverse(temp, files)
    {
        fileInfo* info = (fileInfo*) temp->val.v;

        //checks if the file has already been linked to an inode, if so create a hard link
        if (info->link != NULL)
        {
            link(info->link->filename, info->filename);
            continue;
        }

        //writes the contents of the file
        FILE *file = fopen(info->filename, "wb");
        fwrite(info->contents, sizeof(unsigned char), info->size, file);
        fclose(file);

        //sets the file mode as well as the modification time
        chmod(info->filename, info->mode);
        struct utimbuf times;
        times.modtime = info->mtime;
        times.actime = info->mtime;
        utime(info->filename, &times);
    }

    //frees the memory within the files dllist
    dll_traverse(temp, files)
    {
        fileInfo* info = (fileInfo*) temp->val.v;
        free(info->contents);
        free(info);
    }
    
    //sets the modes and the new modification time
    dll_traverse(temp, directories)
    {
        fileInfo* info = (fileInfo*) temp->val.v;
        chmod(info->filename, info->mode);

        struct utimbuf time;
        time.modtime = info->mtime;
        time.actime = info->mtime;
        utime(info->filename, &time);

        free(info);
    }
}

int main()
{
    //creates the double linked lists for directories and files as well as a jrb for the inodes
    Dllist directories = new_dllist();
    Dllist files = new_dllist();
    JRB inodes = make_jrb();

    //reads in all of the files and adds them to their respective dllist
    fileInfo *info;
    while(1) 
    {
        info = (fileInfo*) malloc(sizeof(fileInfo));

        int temp = nextFile(info, inodes);

        //if temp != 0, the end of file has been reached and no more files can be read in
        if(temp != 0) 
        {
            free(info);
            break;
        }

        //check if the mode is a directory, if so add it to the directories list
        if(S_ISDIR(info->mode))
            dll_append(directories, new_jval_v(info));
        //otherwise, add it to the files list
        else
            dll_append(files, new_jval_v(info));
    }

    //create the directories as well as its files and modes, then empties the two lists
    create(directories, files);

    free_dllist(files);
    free_dllist(directories);
    jrb_free_tree(inodes);
}
