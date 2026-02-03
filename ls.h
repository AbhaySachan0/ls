
#include<dirent.h>

typedef struct {
    int show_all; // -a
    int show_inode; // -i
    int show_long_list; // -l
    int path_count; // check if there is path or not
    char *path; // stores path
} options;

void show_inode(const unsigned long inode[],int n) {
    
    for(int i=0;i<n;i++){
        printf("%lu\n",(unsigned long)inode[i]);
    }

}