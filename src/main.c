/*
 * main.c
 *
 *  Created on: 14.03.2013
 *      Author: victor
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "filestruc.h"


int i;
filestruc files_mas[10000];

void fsize(char *);
int sort_file_mas();

int main (int argc, char **argv)
{
	int j;

	i = 0;

	if (argc == 1)
	    fsize("/tmp/biz");
	else
	    while (--argc > 0)
	        fsize(*++argv);

	for (j=0; j<i; j++)
	{
		printf("name: %s size: %8ld \n",files_mas[j].name, files_mas[j].size);
	}


	printf(" \n Stat: SUM of equal = %d \n", sort_file_mas());

	return 0;




//		GOOD CODE
/*
    DIR *dir;
    struct dirent *ent;
    struct stat stbuf;

    //char name[MAX_PATH_LENGTH];

    dir = opendir("/tmp/biz");

    if (dir != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
        	sprintf(files_mas[i].name, "/tmp/biz/%s", ent->d_name); // полный путь к файлу
        	stat(files_mas[i].name, &stbuf); // заполняем stbuf

        	if ((stbuf.st_mode & S_IFMT) != S_IFDIR ) // не католог
            {

            	files_mas[i].size = stbuf.st_size;
            	i++;
            	printf("file %3d> %s\n", i, ent->d_name);
            }
        	else
        	{
        	    printf("dir> %s\n", ent->d_name);
        	}
        }
        closedir(dir);
    }
    else
    {
        printf("Failed to read directory ");
    }
    return 0;
*/

}

void dirwalk(char *, void (*fcn) (char *));

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1)
    {
        printf("fsize: can't access %s \n",name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);

    sprintf(files_mas[i].name, "%s", name);
    files_mas[i].size = stbuf.st_size;
    i++;
    //printf ("%8ld %s\n", stbuf.st_size, name);
}


void dirwalk(char *dir, void (*fcn) (char *))
{
    char name[MAX_PATH_LENGTH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL)
    {
        printf("dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        sprintf(name, "%s/%s",dir, dp->d_name);
        (*fcn)(name);

    }
    closedir(dfd);
}

int sort_file_mas()
{
	int j, a;
	int sum = 0;

	for (j=0; j<i-1; j++ )
	{
		for (a=j+1; a<i; a++)
		{
			if (files_mas[j].size == files_mas[a].size)
			{
				sum++;
				printf("find equal> *** %s *** | *** %s *** \n", files_mas[a].name, files_mas[j].name);
			}
		}
	}

	return sum;
}
