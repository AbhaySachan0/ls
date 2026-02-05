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
    
    sort_by_filename(&data);
    show_inode(data,opt);
}

