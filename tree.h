#define MAX 1000
typedef struct node{
    char* name;
    int isdir;
    struct node *nextDirectory;
    struct node *nextFile;
    int level;
    char *username;
}node;

typedef node tree;


node* create_node(char* n);
tree* create_tree(char *root);
void print_tree(node *start);
void get_username(char* path);
void print_specified_path(char *basePath);
void getFileCreationTime(char *path);
void file_time_modified(char *basePath);
long file_size(char* path);
void print_file_size(char *path);
//void print_tree_indentation()
int count;
int max;
int dir_in_path;
int files_in_path;
