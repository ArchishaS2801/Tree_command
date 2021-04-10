#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>
#include "tree.h"
#include <time.h>

//to create new node in tree
node* create_node(char* n) {
	node* temp = (node*)malloc(sizeof(node));//allocating space
	temp->name = n;
	temp->nextDirectory = NULL;
	temp->nextFile = NULL;
    return temp;
}

/*Function to create the directory tree, which is called recursively.
  Opens the directory specified, checks iteratively if contents are files
  or directories : if directory found, recursively calls the function to
  parse through the directory files.
  Argument(s):
  	root_name(char): contains name of specified directory
  Returns: Root of created directory tree
*/
tree* create_tree(char *root_name)//here root name gets the current directory name
{
	//DIR *opendir(const char *dirname) this opens the directory stream corresponding to the root_name returns
	//a pointer of dir type if operation is successful else NULL returned
	DIR *dir = opendir(root_name);


	//struct dirent contains various members which I have used in the code d_type,d_name etc
	struct dirent *dr = NULL;
	tree *root,*temp,*temp1 ;
	root = temp = temp1 = NULL;
	char *name = (char *)malloc(sizeof(char)*MAX);//ALLOCATING SPACE FOR NAME

	//Checks to see if directory exists if doesnt return
	if(dir == NULL)
	{
		printf("Error in opening file");
		return NULL;
	}

	//While loop runs until all contents of the directory have been checked
	while((dr = readdir(dir)) != NULL){
			//Every directory has two directories called "." and "..", which stand
			//for present working directory and root directory which cannot be parsed further
			if(strcmp((dr->d_name),".")!=0 && strcmp((dr->d_name),"..") != 0) {
				temp = create_node(dr->d_name);
			}
			else {
				temp=NULL;
				continue;
			}

			if(temp1!=NULL) {
				temp1->nextFile = temp;

			}

			else	{
				root = temp;
			}

			//Checking if it's a directory
			if((dr->d_type) == DT_DIR){//if the dr type is directory make isdir 1 and make name root_name
				temp->isdir=1;
				strcpy(name,root_name);
				temp->nextDirectory = create_tree((strcat((strcat(name,"/")),dr->d_name)));

			}

			else{
				temp->isdir = 0;
				temp->nextDirectory = NULL;

			}

			temp1 = temp;


	}

return (root);
}


void print_tree(node *start) {
		char *s="|    ",*s1="|----";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level=count;
		if(count > max)
			max=count;
		printf("\n");
		for(int i = 0;i<(count-1);i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);

		printf("level:%d  %s",temp->level,temp->name);

		//Checks if it's a directory
		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_tree(temp->nextDirectory);
			count--;
		}

		files_in_path += 1;
		print_tree(temp->nextFile);

}
//function to get the username for the u flag

void get_username(char* path) {
	struct stat stats;//retrive info about the file pointed by the path name
	stat(path, &stats);//reads all props and dumps it into string buffer stats
	struct passwd *pwuser;
	pwuser = getpwuid(stats.st_uid);
	printf("USER ID = %u\n",pwuser->pw_uid);
	printf("Group ID = %u\n",pwuser->pw_gid);
	printf("USERNAME : %s\n",pwuser->pw_name);
}

void print_specified_path(char *basePath) {
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);


    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s\n", dp->d_name);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            print_specified_path(path);
        }
    }

    closedir(dir);
}

void file_time_modified(char *basePath) {
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);


    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s - ", dp->d_name);
            strcpy(path, basePath);
			getFileCreationTime(path);
			printf("\n");
            strcat(path, "/");
            strcat(path, dp->d_name);

            print_specified_path(path);
        }
    }

    closedir(dir);
}

void getFileCreationTime(char *path) {
    struct stat attr;
    stat(path, &attr);
    printf("Last modified time: %s", ctime(&attr.st_mtime));
}

