#define MAX 100000

//This is the adt of the node 
typedef struct node{

    //name of the given file/folder
    char* name;
    //this is for checking if it is a directory or not
    int isdir;
    //pointer to the next directory of type node
    struct node *nextDirectory;
    //pointer to the next file of type node
    struct node *nextFile;
    //stores level of the tree
    int level;

}node;

//function to create node once path is passed
node* create_node(char* n);
//creates a tree from the root onwards
node* create_tree(char *root);
//prints tree once the start node is passed
void print_tree(node *start);
//gets the user details of the path specified (username, group id,user id)
void get_username(char* path);
//prints all the files and folder names recursively without indentation 
void print_no_indentation(char *basePath);
//prints tree from the start node with indentation and color
void print_tree_color(node *start);
//prints tree from the start node with indentation and of type media files
void print_tree_media(node *start);
//prints tree from the start node with indentation and of type compressed files
void print_tree_compressed(node *start);
//prints tree from the start node with indentation and of type program files
void print_tree_programs(node *start);
//prints tree from the start node with indentation and matches the pattern specified 
void print_match_pattern(node *start,char *pattern);
//prints tree from the start node with indentation and does not match the pattern specified 
void print_does_not_match_pattern(node *start,char *pattern);
//prints tree from the start node with indentation only of type dir
void print_directories(node *start);
//prints all the number of files and directories
void num_dir_files();




