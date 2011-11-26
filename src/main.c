#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "handler.h"

int main(int argc, const char *argv[])
{
    if(argc < 2 || argc > 3)
    {
        printf("Using: ./app -c/-m/-d [path]\n");
        return 1; 
    }
  
#if 0
    char *pwd = NULL;
    char buf[256];
    memset(buf, 0, 256);
    
    pwd = get_current_dir_name();
    sprintf(buf, "%s/", pwd);
#endif
    
    if(2 == argc)
        argv[2] = "./"; 

    if((-1 == hens (argv[1], argv[2])))
    {
        //TODO
        printf("Invalid command -- you can use: doc -help\n");
    }

    return 0;
}
