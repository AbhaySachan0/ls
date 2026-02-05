#include<stdio.h>
#include<dirent.h>
#include"ls.h"
#include<string.h>
#include<stdlib.h>

// for user and group name
#include<pwd.h>
#include<grp.h>

#include <time.h>


#include<unistd.h>
#include<sys/stat.h> // for stat()

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

    printf("Hello\n");

    // printf("-a: %d\n-l: %d\n -i: %d\n",opt.show_all,opt.show_long_list,opt.show_inode);
    // printf("Path : %s\n",opt.path);

    // opening and reading the directory 

    Data data = {0};
    
    DIR *dir = opendir(opt.path);
    struct dirent *entry;

    int i=0;
    while((entry = readdir(dir)) !=NULL) {
        data.file_name[i] = strdup(entry->d_name);
        i++;
        data.entry_count++;
    }

    // sort_by_filename(&data);
    // show_inode(data, &opt);


    i=0;
    while(i<data.entry_count) {
        struct stat st;
        stat(data.file_name[i],&st);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group  *gr = getgrgid(st.st_gid);

        data.group[i] = strdup(gr->gr_name); 
        data.user[i] = strdup(pw->pw_name); 
        data.userID[i] = st.st_uid;
        data.mod_time[i] = strdup(ctime(&st.st_mtime));
        
        // working on permission
        char perm[11];
        permission(st.st_mode,perm);
        data.permission[i] = strdup(perm);

        
        
        // printing
        printf("%s\n",data.permission[i]);
        // printf("Modified: %s", ctime(&st.st_mtime));
        // printf("%d\n",data.userID[i]);
        // printf("%s\n",data.group[i]);
        i++;
    }
}

