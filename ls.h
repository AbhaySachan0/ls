
#include<dirent.h>
#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h> // for stat()

#include<string.h>
#define MAX_ENTRY 100

typedef struct {
    int show_all; // -a
    int show_inode; // -i
    int show_long_list; // -l
    int path_count; // check if there is path or not
    char *path; // stores path
} options;

typedef struct {
    unsigned long inode[MAX_ENTRY];
    char *file_name[MAX_ENTRY];
    char *permission[MAX_ENTRY];
    char *user[MAX_ENTRY];
    char *group[MAX_ENTRY];
    unsigned int userID[MAX_ENTRY]; 

    char *mod_time[MAX_ENTRY];
    int entry_count;
}Data;


void sort_by_filename(Data *data) {
    for(int i=0;i<data->entry_count-1;i++){
        for(int j=i+1;j<data->entry_count;j++) {
            if(strcmp(data->file_name[i],data->file_name[j]) > 0) { // swap every entry

                // inode
                unsigned long temp_inode = data->inode[i];
                data->inode[i] = data->inode[j];
                data->inode[j] = temp_inode;
                
                //file name
                char *temp = data->file_name[i];
                data->file_name[i] = data->file_name[j];
                data->file_name[j] = temp;
            }   
        }
    }
}

void permission(mode_t mode, char *perm) {

    if(S_ISDIR(mode)) {
        perm[0] = 'd';
    } else {
        perm[0] = '-';
    }

    // if((mode & S_IRUSR)) {
    //     perm[1] = 'r';
    // } else {
    //     perm[1] = '-';
    // }

    perm[1] = (mode & S_IRUSR)?'r':'-';
    perm[2] = (mode & S_IWUSR)?'w':'-';
    perm[3] = (mode & S_IXUSR)?'x':'-';
 
    perm[4] = (mode & S_IRUSR)?'r':'-';
    perm[5] = (mode & S_IWUSR)?'w':'-';
    perm[6] = (mode & S_IXGRP)?'x':'-';
 
    perm[7] = (mode & S_IROTH)?'r':'-';
    perm[8] = (mode & S_IWOTH)?'w':'-';
    perm[9] = (mode & S_IXOTH)?'x':'-';
    perm[10] = '\0';
}



void show_inode(const Data data, options *opt) {
    
    for(int i=0;i<data.entry_count;i++){
        char *name = data.file_name[i];
        
        if(!(opt->show_all) && name[0]=='.') continue;
        printf("%lu  %s\n",data.inode[i],data.file_name[i]);
    }

}