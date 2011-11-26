#include <stdio.h>
#include <string.h>

#include "sys_IO.h"
#include "pro_document.h"
#include "common.h"

static void help_tip(void)
{
    FILE *fd;
    char buf[1024];
    int n;

    memset(buf, 0, 1024);

    fd = fopen(HELP_DOC_PATH, "r");
    if(fd == NULL)
    {
        perror("open doc_help failed!");
        return;
    }

    while((n = fread(buf, 1, 1024, fd))){
        printf("%s", buf);
        memset(buf, 0, 1024);
    }

    fclose(fd);
}

int hens (const char *arg, const char *path)
{
    volatile int mode = 0;

    if(0 == strcmp(arg, "-c"))
    {
        mode = FILE_MODE;
    }
    else if(0 == strcmp(arg, "-m"))
    {
        mode = MOVIE_MODE;
    }
    else if(0 == strcmp(arg, "-d"))
    {
        //special handler
        if(-1 == pro_document_manager(path, 'f'))
        {
            fprintf(stdout, "%s\n", "failed to create project document");
            return 1; 
        }

        return 0;
    }
    else if(0 == strcmp(arg, "-ud"))
    {
        //special handler
        if(-1 == pro_document_manager(path, 'u'))
        {
            fprintf(stdout, "%s\n", "failed to clean project document");
            return 1; 
        }

        return 0;
    }
    else if(0 == strcmp(arg, "-help"))
    {
        help_tip();
    }
    else{ /*invalid argument*/
        return -1; 
    }

    document_handle (path, mode);

    return 0;
}
