#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"
int main(int argc,char *argv[])
{
    if(argc==1) {
    node *start=create_node(".");
	start->isdir=1;
    start->nextDirectory = create_tree(getcwd(0,0));
	print_tree(start);

    }
    
	char name[100000];

    if(argc >= 2 && strcmp(argv[1],"-f") == 0){

	    printf("Enter path to list files: ");
        scanf("%s", name);
        print_specified_path(name);


    }

    if(argc >= 2 && strcmp(argv[1],"-u") == 0){

          printf("Enter path to list files: ");
          scanf("%s", name);
          get_username(name);
          printf("\n");
    }

    if(argc >= 2 && strcmp(argv[1],"-t") == 0){

          getFileCreationTime(name);

    }
    if(argc >= 2 && strcmp(argv[1],"-Ft") == 0){
          printf("Enter path to list files: ");
          scanf("%s", name);
          file_time_modified(name);
          

    }

    return 0;

  

}
