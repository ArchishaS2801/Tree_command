#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>
#include "tree.h"
#include <time.h>
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

int count = 0;
int max = 0;
int dir_in_path = 0;
int files_in_path = 0;

//to create new node in tree
node* create_node(char* n) {

	node* temp = (node*)malloc(sizeof(node));//allocating space
	temp->name = n;
	temp->nextDirectory = NULL;
	temp->nextFile = NULL;
    temp->filesize = file_size(n);
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
node* create_tree(char *root_name)//here root name gets the current directory name
{
	//DIR *opendir(const char *dirname) this opens the directory stream corresponding to the root_name returns
	//a pointer of dir type if operation is successful else NULL returned
	DIR *dir = opendir(root_name);


	//struct dirent contains various members which I have used in the code d_type,d_name etc
	struct dirent *dr = NULL;
	node *root,*temp,*temp1 ;
	root = temp = temp1 = NULL;
	char *name = (char *)malloc(sizeof(char)*1000);//ALLOCATING SPACE FOR NAME
	

	//Checks to see if directory exists if doesnt return
	if(dir == NULL)
	{
		//printf("Error in opening file");
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

return root;
}


void print_tree(node *start) {
		char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level=count;
		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
			

		printf("%s  ",temp->name);
		
       
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


void print_tree_color(node *start) {
		char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level=count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
        //Audio file format extension color = RESET
		if(strstr(temp->name,".aif") || strstr(temp->name,".cda") || strstr(temp->name,".mid") || 

		strstr(temp->name,".mp3") || strstr(temp->name,".mpa") || strstr(temp->name,".ogg") ||

		strstr(temp->name,".wav") || strstr(temp->name,".wma") || strstr(temp->name,".wpl") )	{

			printf("%s%s\n",ANSI_COLOR_RESET,temp->name);

		}

		//Compressed file extensions color = YELLOW
		else if(strstr(temp->name,".7z") || strstr(temp->name,".arj") || strstr(temp->name,".deb") || 

		strstr(temp->name,".pkg") || strstr(temp->name,".rar") || strstr(temp->name,".rpm") ||

		strstr(temp->name,".tar.gz") || strstr(temp->name,".z") || strstr(temp->name,".zip") )	{

			printf("%s%s\n",ANSI_COLOR_YELLOW,temp->name);

		}

		//Disc/media/data and database file extensions color = MAGENTA
		else if(strstr(temp->name,".csv") || strstr(temp->name,".dat") || strstr(temp->name,".db") || 

		strstr(temp->name,".sav") || strstr(temp->name,".mdb") || strstr(temp->name,".log") ||

		strstr(temp->name,".sql") || strstr(temp->name,".tar") || strstr(temp->name,".xml") || 

		strstr(temp->name,".bin") || strstr(temp->name,".dmg") || strstr(temp->name,".iso") || 

		strstr(temp->name,".toast") || strstr(temp->name,".vcd") )	{

			printf("%s%s\n",ANSI_COLOR_MAGENTA,temp->name);

		}

		//executable file extensions and programming files

		else if(strstr(temp->name,".apk") || strstr(temp->name,".bat") || strstr(temp->name,".bin") || 

		strstr(temp->name,".cgi") || strstr(temp->name,".com") || strstr(temp->name,".exe") ||

		strstr(temp->name,".msi") || strstr(temp->name,".jar") || strstr(temp->name,".gadget") || 

		strstr(temp->name,".py") || strstr(temp->name,".wsf") || strstr(temp->name,".c") || 

		strstr(temp->name,".h") || strstr(temp->name,".cpp") || strstr(temp->name,".java") 
		
		|| strstr(temp->name,".php") || strstr(temp->name,".py") || strstr(temp->name,".sh")
		
		|| strstr(temp->name,".swift") || strstr(temp->name,".vb") || strstr(temp->name,".js")
		
		|| strstr(temp->name,".ts"))	{

			printf("%s%s\n",ANSI_COLOR_RED,temp->name);

		}

		else if(strstr(temp->name,".html") || strstr(temp->name,".pdf") || strstr(temp->name,".xls") || 

		strstr(temp->name,".ods") || strstr(temp->name,".ppt") || strstr(temp->name,".pptx") ||

		strstr(temp->name,".txt") || strstr(temp->name,"jpg") || strstr(temp->name,".png") || 

		strstr(temp->name,".svg") || strstr(temp->name,".doc") || strstr(temp->name,".docx") || 

		strstr(temp->name,".class") || strstr(temp->name,".css") || strstr(temp->name,".json") 
		
		|| strstr(temp->name,".iml") || strstr(temp->name,".bash") || strstr(temp->name,".o")
		
		|| strstr(temp->name,".layout") || strstr(temp->name,".cbp") || strstr(temp->name,".depend")
		
		|| strstr(temp->name,".ts")){

			printf("%s%s\n",ANSI_COLOR_GREEN,temp->name);
		}



		else{
			printf("%s%s\n",ANSI_COLOR_BLUE,temp->name);
		}



		
		//Checks if it's a directory
		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_tree_color(temp->nextDirectory);
			count--;
		}

		files_in_path += 1;
		print_tree_color(temp->nextFile);

}


void print_color_without_indentation(char *basePath) {
	
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);


    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL )
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {

			  //Audio file format extension color = RESET
		if(strstr(dp->d_name,".aif") || strstr(dp->d_name,".cda") || strstr(dp->d_name,".mid") || 

		strstr(dp->d_name,".mp3") || strstr(dp->d_name,".mpa") || strstr(dp->d_name,".ogg") ||

		strstr(dp->d_name,".wav") || strstr(dp->d_name,".wma") || strstr(dp->d_name,".wpl") )	{

			printf("%s%s\n",ANSI_COLOR_RESET,dp->d_name);

		}

		//Compressed file extensions color = YELLOW
		else if(strstr(dp->d_name,".7z") || strstr(dp->d_name,".arj") || strstr(dp->d_name,".deb") || 

		strstr(dp->d_name,".pkg") || strstr(dp->d_name,".rar") || strstr(dp->d_name,".rpm") ||

		strstr(dp->d_name,".tar.gz") || strstr(dp->d_name,".z") || strstr(dp->d_name,".zip") )	{

			printf("%s%s\n",ANSI_COLOR_YELLOW,dp->d_name);

		}

		//Disc/media/data and database file extensions color = MAGENTA
		else if(strstr(dp->d_name,".csv") || strstr(dp->d_name,".dat") || strstr(dp->d_name,".db") || 

		strstr(dp->d_name,".sav") || strstr(dp->d_name,".mdb") || strstr(dp->d_name,".log") ||

		strstr(dp->d_name,".sql") || strstr(dp->d_name,".tar") || strstr(dp->d_name,".xml") || 

		strstr(dp->d_name,".bin") || strstr(dp->d_name,".dmg") || strstr(dp->d_name,".iso") || 

		strstr(dp->d_name,".toast") || strstr(dp->d_name,".vcd") || strstr(dp->d_name,".o") || strstr(dp->d_name,".c"))	{

			printf("%s%s\n",ANSI_COLOR_MAGENTA,dp->d_name);

		}

		//executable file extensions and programming files

		else if(strstr(dp->d_name,".apk") || strstr(dp->d_name,".bat") || strstr(dp->d_name,".bin") || 

		strstr(dp->d_name,".cgi") || strstr(dp->d_name,".com") || strstr(dp->d_name,".exe") ||

		strstr(dp->d_name,".msi") || strstr(dp->d_name,".jar") || strstr(dp->d_name,".gadget") || 

		strstr(dp->d_name,".py") || strstr(dp->d_name,".wsf") || strstr(dp->d_name,".c") || 

		strstr(dp->d_name,".h") || strstr(dp->d_name,".cpp") || strstr(dp->d_name,".java") 
		
		|| strstr(dp->d_name,".php") || strstr(dp->d_name,".py") || strstr(dp->d_name,".sh")
		
		|| strstr(dp->d_name,".swift") || strstr(dp->d_name,".vb") || strstr(dp->d_name,".js")
		
		|| strstr(dp->d_name,".ts"))	{

			printf("%s%s\n",ANSI_COLOR_RED,dp->d_name);

		}

		else if(strstr(dp->d_name,".html") || strstr(dp->d_name,".pdf") || strstr(dp->d_name,".xls") || 

		strstr(dp->d_name,".ods") || strstr(dp->d_name,".ppt") || strstr(dp->d_name,".pptx") ||

		strstr(dp->d_name,".txt") || strstr(dp->d_name,"jpg") || strstr(dp->d_name,".png") || strstr(dp->d_name,".jpeg") || 

		strstr(dp->d_name,".svg") || strstr(dp->d_name,".doc") || strstr(dp->d_name,".docx") || 

		strstr(dp->d_name,".class") || strstr(dp->d_name,".css") || strstr(dp->d_name,".json") 
		
		|| strstr(dp->d_name,".iml") || strstr(dp->d_name,".bash") || strstr(dp->d_name,".o")
		
		|| strstr(dp->d_name,".layout") || strstr(dp->d_name,".cbp") || strstr(dp->d_name,".depend")
		
		|| strstr(dp->d_name,".ts")){

			printf("%s%s\n",ANSI_COLOR_GREEN,dp->d_name);
		}



		else{
			printf("%s%s\n",ANSI_COLOR_BLUE,dp->d_name);
		}
           // printf("%s\n", dp->d_name);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            print_specified_path(path);
        }
    }

    closedir(dir);
}



void print_tree_media(node* start){

	char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level=count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
        if(strstr(temp->name,"jpg") || strstr(temp->name,".png") || strstr(temp->name,"jpeg") ||

		strstr(temp->name,".aif") || strstr(temp->name,".cda") || strstr(temp->name,".mid") || 

		strstr(temp->name,".mp3") || strstr(temp->name,".mp4") || strstr(temp->name,".ogg") ||

		strstr(temp->name,".wav") || strstr(temp->name,".wma") || strstr(temp->name,".wpl") ) 

		{

			printf("%s%s\n",ANSI_COLOR_GREEN,temp->name);
		}
		else{
			printf("%s",ANSI_COLOR_RED);
		}

		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_tree_media(temp->nextDirectory);
			count--;
		}

		files_in_path += 1;
		print_tree_media(temp->nextFile);


}



void print_tree_compressed(node *start){

	char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level = count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
      if(strstr(temp->name,".7z") || strstr(temp->name,".arj") || strstr(temp->name,".deb") || 

		strstr(temp->name,".pkg") || strstr(temp->name,".rar") || strstr(temp->name,".rpm") ||

		strstr(temp->name,".tar.gz") || strstr(temp->name,".z") || strstr(temp->name,".zip") )	{

			printf("%s%s\n",ANSI_COLOR_YELLOW,temp->name);

		}
		else{
			printf("%s",ANSI_COLOR_MAGENTA);
		}

		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_tree_compressed(temp->nextDirectory);
			count--;
		}

		files_in_path += 1;
		print_tree_compressed(temp->nextFile);



}


void print_tree_programs(node *start){

	char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level=count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
      if(strstr(temp->name,".class") || strstr(temp->name,".css") || strstr(temp->name,".json") 
		
		|| strstr(temp->name,".iml") || strstr(temp->name,".bash") || strstr(temp->name,".o")
		
		|| strstr(temp->name,".layout") || strstr(temp->name,".cbp") || strstr(temp->name,".depend")
		
		|| strstr(temp->name,".ts") || strstr(temp->name,".c") || strstr(temp->name,".h") || 
		
		strstr(temp->name,".cpp") || strstr(temp->name,".java") || strstr(temp->name,".php") ||
		
		strstr(temp->name,".py") || strstr(temp->name,".sh") || strstr(temp->name,".swift") || 
		
		strstr(temp->name,".vb") || strstr(temp->name,".js" )){

			printf("%s%s",ANSI_COLOR_RESET,temp->name);
			

		}
		else{
			printf("%s\n",ANSI_COLOR_BLUE);
		}

		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_tree_programs(temp->nextDirectory);
			count--;
		}

		files_in_path += 1;
		print_tree_programs(temp->nextFile);



}

long file_size(char* path) {

        struct stat stats;
        stat(path, &stats);
        return stats.st_size;
}


void print_file_size(char *basePath) {
	
    char path[10000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);


    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s%s ", ANSI_COLOR_RESET,dp->d_name);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
			if(dp->d_type == DT_REG){
				
				printf(": %s%ld bytes  ",ANSI_COLOR_BLUE,file_size(path));
			}
			else{
				printf(" ");
			}
			printf("\n");

            print_file_size(path);
        }
    }

    closedir(dir);
}


void print_match_pattern(node *start,char *pattern){

	char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level = count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
      if(strstr(temp->name,pattern ))	{

			printf("%s%s\n",ANSI_COLOR_RESET,temp->name);

		}
		else{
			printf("%s",ANSI_COLOR_MAGENTA);
		}

		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_match_pattern(temp->nextDirectory,pattern);
			count--;
		}

		files_in_path += 1;
		print_match_pattern(temp->nextFile,pattern);



}


void print_does_not_match_pattern(node *start,char *pattern){

	char *s="|    ",*s1="|_____";
		node *temp = start;
		if(start == NULL)
			return;


		temp->level = count;

		if(count > max)
			max = count;
		printf("\n");
		for(int i = 0;i < count-1;i++)
			printf("%s",s);
		if(count > 0)
			printf("%s",s1);
		
      if(!strstr(temp->name,pattern ))	{

			printf("%s%s\n",ANSI_COLOR_RESET,temp->name);

		}
		else{
			printf("%s",ANSI_COLOR_MAGENTA);
		}

		if(temp->isdir==1)
		{
			dir_in_path += 1;
			count++;
			print_does_not_match_pattern(temp->nextDirectory,pattern);
			count--;
		}

		files_in_path += 1;
		print_does_not_match_pattern(temp->nextFile,pattern);



}

