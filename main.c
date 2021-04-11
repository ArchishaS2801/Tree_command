#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"
int main(int argc,char *argv[])
{
    char name[100000];
    if(argc==1) {
    node *start=create_node(".");
	start->isdir=1;
    start->nextDirectory = create_tree(getcwd(0,0));
	print_tree(start);
    

    }

    if(argc >= 2 && strcmp(argv[1],"-f") == 0){

	    printf("Enter path to list files: ");
        scanf("%s", name);
        print_specified_path(name);


    }
    
    if(argc >=2 && strcmp(argv[1],"-i") == 0){

    node *start=create_node(".");
	start->isdir=1;
    printf("Enter path to list files: ");
    scanf("%s", name);
    start->nextDirectory = create_tree(name);
	print_tree(start);
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

    if(argc >=2 && strcmp(argv[1],"-help") == 0){

        printf("\nThis is the help section: \n");
        printf("\nWithout flags it prints all the files/folders in current directory\n");
        printf("\nThe various flags are : \n");
        printf("\n-f : prints all files in given path recursively\n");
        printf("\n-Ft : all the files and folders in the path specified along with last modified date and time \n");
        printf("\n-t : prints the last modified of the current path \n");
        printf("\n-v : prints the version of the tree\n");
        printf("\n-help : prints the help section\n\n");


    }

    if(argc >= 2 && strcmp(argv[1],"-v") == 0){

          printf("\ntree 1.12.1 \n");
          printf("\nCOPYRIGHT 2021 -----ARCHISHA SHUKLA \n");
          printf("\nTree is a free software with no warranty\n\n");
          

    }

    if(argc >= 2 && strcmp(argv[1],"-s") == 0){

          printf("Enter path to list files: ");
          scanf("%s", name);
          print_file_size(name);
          

    }

    return 0;

  

}
