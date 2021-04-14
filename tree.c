#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>
#include "tree.h"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

//globally defining these variables

int count = 0;
int num_dir = 0;
int num_files = 0;

//to create new node in tree
node* create_node(char* n) {

	node* temp = (node*)malloc(sizeof(node));//allocating space
	temp->name = n;//setting the nodes name value as the n that is passed
	temp->nextDirectory = NULL;//setting next directory null
	temp->nextFile = NULL;//setting next file as null
    return temp;//returning temp node

}



//this function to create a dir tree which is called recursively
node* create_tree(char *root_name)//here root name here has the name of specified directory
{
	//DIR *opendir(const char *dirname) this opens the directory stream corresponding to the root_name returns
	//a pointer of dir type if operation is successful else NULL returned
	DIR *dir = opendir(root_name);


	//struct dirent contains various members which I have used in the code d_type,d_name etc
	struct dirent *dr = NULL;
	node *root,*temp,*temp1 ;
	root = temp = temp1 = NULL;
	char *name = (char *)malloc(sizeof(char)*MAX);//ALLOCATING SPACE FOR NAME
	

	//if error in opening the dir it points to null we print error and return null
	if(dir == NULL) {
		printf("Error\n");
		return NULL;
	}

	//While loop runs until all contents of the directory have been checked
	while((dr = readdir(dir)) != NULL) {

			/*Every directory has two directories called "." and ".." 
			which stands for present working directory and root directory
			 which cannot be parsed further*/

			if(strcmp((dr->d_name),".") != 0 && strcmp((dr->d_name),"..") != 0) {

				temp = create_node(dr->d_name);//creating node for each file/directory
			}
			else {

				temp = NULL;// otherwise if no further directories can be parsed temp is said to null
				continue;//force iteration here 
			}

			if(temp1 != NULL) {

				temp1->nextFile = temp;//keeps setting nextfile pointer as temp till temp1 is not null

			}

			else {
				root = temp;//when reaches null set value of root as temp
			}

			//Checking if it's a directory
			if((dr->d_type) == DT_DIR) {//if the dr type is directory make isdir 1 and make name root_name
				temp->isdir=1;
				strcpy(name,root_name);
				temp->nextDirectory = create_tree((strcat((strcat(name,"/")),dr->d_name)));//recurively calling create tree
				//and updating the path being passed to create_tree

			}

			else {
				temp->isdir = 0;//if it isnt a directory isdir set to 0
				temp->nextDirectory = NULL;//and nextDirectory set to NULL

			}
		

			temp1 = temp;//keep setting temp1 as temp


	}

return root;

}


void print_tree(node *start) {

		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;// if no root node exists return


		temp->level=  count;//setting level to count which initially is 0
		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");//if file then this indentation
			

		printf("%s  ",temp->name);//print name of the given dir/file
		
       
		//Checks if it's a directory
		if(temp->isdir == 1) {
			num_dir += 1;//increament by 1 as temp is a dir
			count++;//increament count 
			print_tree(temp->nextDirectory);//recursively print tree for the nextdirectory
			count--;
		}

		num_files += 1;//increament the num of files
		print_tree(temp->nextFile);//print tree recursively for next file


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

//prints without any indentation

void print_no_indentation(char *basePath) {//passing the base path taken from user
	
    char path[10000];

    struct dirent *dp;//defining dp of type struct dirent that has d_name and d_type which will be used ahead
    DIR *dir = opendir(basePath);//opening the dir of the passed path
    
    //if open dir failed control returned 
    if (!dir)
        return;

	
    //dp keeps reading dir till stream of dir is available
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {

            printf("%s\n", dp->d_name);//print d_name of dir
			//modifying the path being passed recursively to the function
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            print_no_indentation(path);
        }
    }

    closedir(dir);//close dir once job done 
}

//printing a colorful tree on basis of the extention type


void print_tree_color(node *start) {
		
		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level=count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");
		
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
		if(temp->isdir==1) {
			num_dir += 1;
			count++;
			print_tree_color(temp->nextDirectory);
			count--;
		}

		num_files += 1;
		print_tree_color(temp->nextFile);

}


//uses same logic as tree command just prints when the extensions are of type media
//using strstr

void print_tree_media(node* start){

	
		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level=count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");
		
        if(strstr(temp->name,"jpg") || strstr(temp->name,".png") || strstr(temp->name,"jpeg") ||

		strstr(temp->name,".aif") || strstr(temp->name,".cda") || strstr(temp->name,".mid") || 

		strstr(temp->name,".mp3") || strstr(temp->name,".mp4") || strstr(temp->name,".ogg") ||

		strstr(temp->name,".wav") || strstr(temp->name,".wma") || strstr(temp->name,".wpl") ) 

		{

			printf("%s%s\n",ANSI_COLOR_GREEN,temp->name);
			num_files += 1;
		}
		else{
			printf("%s",ANSI_COLOR_RED);
		}

		if(temp->isdir==1) {
			num_dir += 1;//increament number of dirs in tree
			count++;
			print_tree_media(temp->nextDirectory);
			count--;
		}

		print_tree_media(temp->nextFile);


}

//uses same logic as tree command just prints when the extensions are of type zip
//using strstr

void print_tree_compressed(node *start){

	
		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level = count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");
		
      if(strstr(temp->name,".7z") || strstr(temp->name,".arj") || strstr(temp->name,".deb") || 

		strstr(temp->name,".pkg") || strstr(temp->name,".rar") || strstr(temp->name,".rpm") ||

		strstr(temp->name,".tar.gz") || strstr(temp->name,".z") || strstr(temp->name,".zip") )	{

			printf("%s%s\n",ANSI_COLOR_YELLOW,temp->name);
			num_files += 1;

		}
		else{
			printf("%s",ANSI_COLOR_MAGENTA);
		}

		if(temp->isdir==1) {
			num_dir += 1;//increament number of dirs in tree
	    	count++;
			print_tree_compressed(temp->nextDirectory);
			count--;
		}

		print_tree_compressed(temp->nextFile);



}

//uses same logic as tree command just prints when the extensions are of type program 
//using strstr


void print_tree_programs(node *start){

	
		node *temp = start;//start is the root node from where tree is to be printed 
		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level=count;


		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");
		
      if(strstr(temp->name,".class") || strstr(temp->name,".css") || strstr(temp->name,".json") 
		
		|| strstr(temp->name,".iml") || strstr(temp->name,".bash") || strstr(temp->name,".o")
		
		|| strstr(temp->name,".layout") || strstr(temp->name,".cbp") || strstr(temp->name,".depend")
		
		|| strstr(temp->name,".ts") || strstr(temp->name,".c") || strstr(temp->name,".h") || 
		
		strstr(temp->name,".cpp") || strstr(temp->name,".java") || strstr(temp->name,".php") ||
		
		strstr(temp->name,".py") || strstr(temp->name,".sh") || strstr(temp->name,".swift") || 
		
		strstr(temp->name,".vb") || strstr(temp->name,".js" )){

			printf("%s%s",ANSI_COLOR_RESET,temp->name);
			num_files += 1;
			

		}
		else {
			printf("%s\n",ANSI_COLOR_BLUE);
		}

		if(temp->isdir==1) {
            num_dir += 1;//increament number of dirs in tree
			count++;
			print_tree_programs(temp->nextDirectory);
			count--;
		}

		print_tree_programs(temp->nextFile);



}


void print_match_pattern(node *start,char *pattern){

	
		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level = count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");//if file provide this indentation
			
		
      if(strstr(temp->name,pattern ) )	{//if the name of the node matches pattern print the name

			printf("%s%s\n",ANSI_COLOR_RESET,temp->name);
			    

		}
		else{//else dont print node 
			printf("%s",ANSI_COLOR_MAGENTA);//added color for differentiation
		}

		if(temp->isdir==1) {
			num_dir += 1;//increament the number of directories by one
			count++;
			print_match_pattern(temp->nextDirectory,pattern);//recursively calling for next node dir
			count--;
		}

		num_files += 1;
		print_match_pattern(temp->nextFile,pattern);//recursively calling for next node file




}


void print_does_not_match_pattern(node *start,char *pattern){

	
		node *temp = start;//start is the root node from where tree is to be printed 
		if(start == NULL)
			return;// if no root node exists return

        //setting level to count which initially is 0
		temp->level = count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");//if file then provide this indentation
		
      if(!strstr(temp->name,pattern ))	{// if the name of dir d.n match pattern then print

			printf("%s%s\n",ANSI_COLOR_RESET,temp->name);

		}
		else{
			printf("%s",ANSI_COLOR_MAGENTA);
		}

		if(temp->isdir==1) {
			num_dir += 1;//increament number of directories in the tree
			count++;
			print_does_not_match_pattern(temp->nextDirectory,pattern);//recursively call for nextDirectory node
			count--;
		}

		num_files += 1;//increament number of files in tree
		print_does_not_match_pattern(temp->nextFile,pattern);//recursively call this function for next file node
	



}

//prints all the directories
void print_directories(node *start){

	
		node *temp = start;//start is the root node from where tree is to be printed 

		if(start == NULL)
			return;

        //setting level to count which initially is 0
		temp->level = count;

		printf("\n");

		for(int i = 0;i < count-1;i++)
			printf("|   ");// if directory this indentation provided

		if(count > 0)
			printf("|_____");//if file this indentation provided
		
      if(temp->isdir) {

			printf("%s \n",temp->name);//if it is a directory then only name is printed

		}

		if(temp->isdir==1) {

			num_dir += 1;//increament number of dirs in tree
			count++;
			print_directories(temp->nextDirectory);//recursively keep calling this function if temp is dir
			count--;
		}

		num_files += 1;//increament number of dirs in tree
		print_directories(temp->nextFile);//recursively call for next file



}
//function to print number of dirs and files in the tree printed

void num_dir_files(){


	printf("\nThe number of directories : %d \n",num_dir);
	printf("The number of files : %d \n",num_files);
	     
}


