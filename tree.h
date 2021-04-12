#define MAX 1000
typedef struct node{
    char* name;
    int isdir;
    struct node *nextDirectory;
    struct node *nextFile;
    int level;
    char *username;
    unsigned long filesize;
    char *timeModified;
}node;

typedef node tree;


node* create_node(char* n);
tree* create_tree(char *root);
void print_tree(node *start);
void get_username(char* path);
void print_specified_path(char *basePath);
char *getFileCreationTime(char *path);
void file_time_modified(char *basePath);
long file_size(char* path);
void print_file_size(char *path);
void printTreeWithFileSize(node *start);
void printTreeWithLastModified(node *start);
void printDirectories(node *start);
void printDirectoriesWithoutIndentation(char *basePath);
void listdir(node *start, int indent);
void print_tree_color(node *start);
void print_color_without_indentation(char *basePath);
void print_tree_media(node *start);
void print_tree_compressed(node *start);
void print_tree_programs(node *start);