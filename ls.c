#include<stdio.h>
#include<dirent.h>
#include"ls.h"
#include<string.h>


int main(int argc, char *argv[]) {
    options opt = {0};

    for(int i=1;i<argc;i++) {
        if(argv[i][0] == '-') { // flag
            // multiple flags together
            for(int j=1;argv[i][j]!='\0';j++) {
                switch (argv[i][j]) {
                    case 'a':
                        opt.show_all = 1;
                        break;
                    case 'l':
                        opt.show_long_list= 1;
                        break;
                    case 'i':
                        opt.show_inode= 1;
                        break;
                }
                
            }
        } else { // path
            opt.path_count++;
            opt.path = argv[i];
        }  
    }

    if(opt.path_count==0) {
        opt.path = ".";
    }

    printf("-a: %d\n-l: %d\n -i: %d\n",opt.show_all,opt.show_long_list,opt.show_inode);

    printf("Path : %s\n",opt.path);

    unsigned long inode[100];
    char *file_name[100];
    
    DIR *dir = opendir(opt.path);
    struct dirent *entry;
    int i=0;
    int count = 0;
    while((entry = readdir(dir)) !=NULL) {
        inode[i] = entry->d_ino;
        file_name[i] = strdup(entry->d_name);
        i++;
        count++;
    }
    show_inode(inode,count);

}