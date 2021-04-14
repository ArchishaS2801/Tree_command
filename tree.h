#define MAX 1000
typedef struct node{
    char* name;
    int isdir;
    struct node *nextDirectory;
    struct node *nextFile;
    int level;
    long filesize;
}node;

typedef node tree;


node* create_node(char* n);
tree* create_tree(char *root);
void print_tree(node *start);
void get_username(char* path);
void print_specified_path(char *basePath);
void print_tree_color(node *start);
void print_color_without_indentation(char *basePath);
void print_tree_media(node *start);
void print_tree_compressed(node *start);
void print_tree_programs(node *start);
long file_size(char* path);
void print_file_size(char *basePath);
void print_match_pattern(node *start,char *pattern);
void print_does_not_match_pattern(node *start,char *pattern);




