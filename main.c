#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"
int main()
{
    node *start=create_node(".");
	start->isdir=1;
    start->nextDirectory = create_tree(getcwd(0,0));
	print_tree(start);
	char name[100000];
	printf("Enter path to list files: ");
    scanf("%s", name);
    print_specified_path(name);
    get_username(name);
    printf("\n");
    getFileCreationTime(name);
    return 0;

}
