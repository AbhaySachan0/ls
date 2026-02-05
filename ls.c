#include<stdio.h>
#include"ls.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>

// for user and group name

#include<sys/stat.h> // for stat()

int main(int argc, char *argv[]) {
    options opt = {0};

    command_parse(argc,argv,&opt);

    Data data = {0};
    scan_directory(&data, opt);

    printf("total : %d\n",data.entry_count);
    // for(int i=0;i<data.entry_count;i++) {
    //     printf("%s  %lu  %s  %s  %s  %s\n",data.permission[i],data.inode[i],data.user[i],data.group[i],data.mod_time[i],data.file_name[i]);
    // }


    // struct stat st;

    // printf("%s HEllo world",ctime(&st.st_mtime));

    
    sort_by_filename(&data);
    show_inode(data,opt);
    // int show_all; // -a
    // int show_inode; // -i
    // int show_long_list; // -l
    // int path_count; // check if there is path or not
    // char *path; // stores path
}

