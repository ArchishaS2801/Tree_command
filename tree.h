#define MAX 1000
typedef struct node{
    char* name;
    int isdir;
    struct node *nextDirectory;
    struct node *nextFile;
    int level;
}node;


node* create_node(char* n);
node* create_tree(char *root);
void print_tree(node *start);
void get_username(char* path);
void print_specified_path(char *basePath);
void print_tree_color(node *start);
void print_tree_media(node *start);
void print_tree_compressed(node *start);
void print_tree_programs(node *start);
void print_match_pattern(node *start,char *pattern);
void print_does_not_match_pattern(node *start,char *pattern);
void print_directories(node *start);




