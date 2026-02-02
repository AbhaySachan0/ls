#include<stdio.h>
#include<dirent.h>

typedef struct Options {
    int show_all; // -a
    int show_inode; // -i
    int long_list; // -l
    int path_count;
    char path[100]; // stores path
} options;

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
                        opt.long_list= 1;
                        break;
                    case 'i':
                        opt.show_inode= 1;
                        break;
                }
            }
        } 
        /* else { // path

        } */ 
    }

    printf("-a: %d\n-l: %d\n -i: %d\n",opt.show_all,opt.long_list,opt.show_inode);
    
}