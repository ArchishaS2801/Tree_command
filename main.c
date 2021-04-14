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

    if(argc >= 2 && strcmp(argv[1],"-noIndentation") == 0){

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



    if(argc >=2 && strcmp(argv[1],"-help") == 0){

        printf("\nThis is the help section: \n");
        printf("\nWithout flags it prints all the files/folders in current directory\n");
        printf("\nThe various flags are : \n");
        printf("\n-i : Prints all the files and folders recursively in tree format\n");
        printf("\n-noIndentation : prints all files and folders recursively with no indentation\n");
        printf("\n-v : prints the version of the tree\n");
        printf("\n-help : prints the help section\n\n");
        printf("\n-c : Prints all files and directories in tree format with colors according to extension\n");
        printf("\n-mediaFiles : Prints all the media files in a tree hierchial format\n");
        printf("\n-compressedFiles : Print all the compressed files in hierchial manner\n");
        printf("\n-programFiles : Prints all the program files in tree hierchial structure\n");
        printf("\n-matchpattern : This prints all the files/folders if name contains the pattern passed\n");
        printf("\n-Ipattern : This prints all the files/folders whose name doesn't conatain the passed pattern\n");
        printf("\n-d : This prints all the folders in a given directory\n");


    }

    if(argc >= 2 && strcmp(argv[1],"-v") == 0){

          printf("\ntree 1.12.1 \n");
          printf("\nCOPYRIGHT 2021 -----ARCHISHA SHUKLA \n");
          printf("\nTree is a free software with no warranty\n\n");
          

    }


    if(argc >=2 && strcmp(argv[1],"-c") == 0){
         
          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter path to list files: ");
          scanf("%s", name);
          start->nextDirectory = create_tree(name);
	    print_tree_color(start);
    }


    if(argc >=2 && strcmp(argv[1],"-mediaFiles") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          start->nextDirectory = create_tree(name);
	    print_tree_media(start);
          
    }

    if(argc >=2 && strcmp(argv[1],"-compressedFiles") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          start->nextDirectory = create_tree(name);
	    print_tree_compressed(start);
          
    }

    if(argc >=2 && strcmp(argv[1],"-programFiles") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          start->nextDirectory = create_tree(name);
	    print_tree_programs(start);
          
    }

     if(argc >=2 && strcmp(argv[1],"-matchpattern") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          char *pattern = argv[2];
          start->nextDirectory = create_tree(name);
	    print_match_pattern(start,pattern);
          
    }

    if(argc >=2 && strcmp(argv[1],"-Ipattern") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          char *pattern = argv[2];
          start->nextDirectory = create_tree(name);
	    print_does_not_match_pattern(start,pattern);
          
    }

    if(argc >=2 && strcmp(argv[1],"-d") == 0){

          node *start=create_node(".");
	    start->isdir=1;
          printf("Enter the path to list all files : ");
          scanf("%s", name);
          start->nextDirectory = create_tree(name);
	    print_directories(start);
          
    }

   

    return 0;

  

}