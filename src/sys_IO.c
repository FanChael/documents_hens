#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#include "common.h"

static void init (char *array, int size)
{
    memset(array, 0, size);
}

static void mv_file (char d_name[], char f_name[])
{
    pid_t pid = fork();
    if(pid < 0) {
        perror("fork");
        exit(1);
    }
    if(pid > 0){ /*child*/
        if(!(execlp("mv", "mv", f_name, d_name, NULL)))
        {
            return; 
        }
    } 

    /* parent */
    wait(NULL);
} 

static int make_dir (char d_name[])
{
    char buf[256];
    init(buf, 256);

    sprintf(buf, "mkdir %s", d_name);

    if(system(buf))
    {
        return -1;
    }

    return 0;
}

int document_handle (const char* path, int mode)
{
    char d_name[256];
    char f_name[256];

    struct dirent *drt;

    DIR *dir = opendir(path);
    if(dir == NULL)
    {
        perror("open failed");
        return -1;
    }
   
    int count = 0;
    char *save_ptr;
    
    while((drt = readdir(dir)) != NULL)
    {
        init(d_name, 256); 
        init(f_name, 256); 

        if(0 == strcmp(drt->d_name, ".")\
                || 0 == strcmp(drt->d_name, "..")) continue;

        if(drt->d_type == DT_REG)
        {
            /*****split joint file's name*****/
            sprintf(f_name, "%s%s", path, drt->d_name);
            save_ptr = strtok(drt->d_name, ".");

            /***split joint path's name***/
            sprintf(d_name, "%s%s", path, save_ptr);

            save_ptr = strtok (NULL, ".");
            if(save_ptr == NULL){ //attention: if not do, wrong!
                save_ptr = f_name;    
            }

            switch(mode)
            {
                case MOVIE_MODE:
                    if(0 == strcmp(save_ptr, "mp4") || 
                            0 == strcmp (save_ptr, "rmvb"))
                    {
                        if(0 == make_dir (d_name))
                        {
                            mv_file (d_name, f_name);
                        }
                    }
                    break;
                case FILE_MODE:
                    if(0 == strcmp (save_ptr, "c"))
                    {
                        if(0 == make_dir (d_name))
                        {
                            mv_file (d_name, f_name);
                        }
                    }
                    break;
                default:
                    break;
            }
            count++; //file counts;
        }
    }

    closedir (dir);

    return count;
}
