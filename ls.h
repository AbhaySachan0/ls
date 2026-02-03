
#include<dirent.h>

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


void show_inode(const Data data, options *opt) {
    
    for(int i=0;i<data.entry_count;i++){
        char *name = data.file_name[i];
        
        if(!(opt->show_all) && name[0]=='.') continue;
        printf("%lu  %s\n",data.inode[i],data.file_name[i]);
    }

}