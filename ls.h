
#include<stdio.h>
#include<string.h>

#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h> // for stat()
#include<unistd.h>

#include <time.h>

#include<pwd.h>
#include<grp.h>
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



void permission(mode_t mode, char *perm) {

    if(S_ISDIR(mode)) {
        perm[0] = 'd';
    } else {
        perm[0] = '-';
    }

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


void scan_directory(Data *data, options opt) {
    
    DIR *dir = opendir(opt.path);
    struct dirent *entry;

    int i=0;
    while((entry = readdir(dir)) !=NULL) {
        struct stat st;
        // stat(entry->d_name,&st);
        if (stat(entry->d_name, &st) == -1) {
            perror("stat");
            continue;
        }
        struct passwd *pw = getpwuid(st.st_uid);
        struct group  *gr = getgrgid(st.st_gid);
        
        data->file_name[i] = strdup(entry->d_name);
        data->inode[i] = entry->d_ino;


        data->group[i] = strdup(gr->gr_name); 
        data->user[i] = strdup(pw->pw_name); 
        data->userID[i] = st.st_uid;

        data->mod_time[i] = strdup(ctime(&st.st_mtime));
        char *t = strdup(ctime(&st.st_mtime));
        t[strcspn(t, "\n")] = '\0';
        data->mod_time[i] = t;
        // working on permission
        char perm[11];
        permission(st.st_mode,perm);
        data->permission[i] = strdup(perm);
        
        i++;
        data->entry_count++;
    }
}


void command_parse(int no_of_arguments, char* command[], options *opt) {
    
    for(int i=1;i<no_of_arguments;i++) {
        if(command[i][0] == '-') { // flag
            // multiple flags together
            for(int j=1;command[i][j]!='\0';j++) {
                switch (command[i][j]) {
                    case 'a':
                        opt->show_all = 1;
                        break;
                    case 'l':
                        opt->show_long_list= 1;
                        break;
                    case 'i':
                        opt->show_inode= 1;
                        break;
                }
                
            }
        } else { // path
            opt->path_count++;
            opt->path = command[i];
        }  
    }

    if(opt->path_count==0) {
        opt->path = ".";
    }
}


void sort_by_filename(Data *data) {
    for(int i=0;i<data->entry_count-1;i++){
        for(int j=i+1;j<data->entry_count;j++) {
            if(strcmp(data->file_name[i],data->file_name[j]) > 0) { // swap every entry

                // inode
                unsigned long temp_inode = data->inode[i];
                data->inode[i] = data->inode[j];
                data->inode[j] = temp_inode;
                
                //file name
                char *temp_name = data->file_name[i];
                data->file_name[i] = data->file_name[j];
                data->file_name[j] = temp_name;
                
                //permisison
                 char *temp_perm = data->permission[i];
                data->permission[i] = data->permission[j];
                data->permission[j] = temp_perm;
                
                //user
                 char *temp_usr = data->user[i];
                data->user[i] = data->user[j];
                data->user[j] = temp_usr;
                
                //group
                char *temp_grp = data->group[i];
                data->group[i] = data->group[j];
                data->group[j] = temp_grp;

                //modification time

                char *temp_time = data->mod_time[i];
                data->mod_time[i] = data->mod_time[j];
                data->mod_time[j] = temp_time;
                
                //user id (unsigned int)
                unsigned int temp_usrId = data->userID[i];
                data->userID[i] = data->userID[j];
                data->userID[j] = temp_usrId;
            }   
        }
    }
}


void show_inode(const Data data, options opt) {
    
    for(int i=0;i<data.entry_count;i++){
        char *name = data.file_name[i];
        

        if(!(opt.show_all) && name[0]=='.') continue;
        if(opt.show_long_list){
            if(!(opt.show_all) && name[0]=='.') continue;
            if(opt.show_inode) {

                printf("%s  %lu  %s  %s  %s  %s\n",data.permission[i],data.inode[i],data.user[i],data.group[i],data.mod_time[i],data.file_name[i]);
                continue;
            }
            printf("%s  %lu  %s  %s  %s  %s\n",data.permission[i],data.inode[i],data.user[i],data.group[i],data.mod_time[i],data.file_name[i]);
        } else {
            if(!(opt.show_all) && name[0]=='.') continue;
            if(opt.show_inode) {

                printf("%lu  %s\n",data.inode[i],data.file_name[i]);
                continue;
            }
            printf("%s\n",data.file_name[i]);
        }
    }
}