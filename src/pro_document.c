#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pro_document_manager(const char *path, char ch)
{
    char buf[256];

    memset(buf, 0, 256);
    
    if(ch == 'f')
    {
        sprintf(buf, "touch %s可行性分析.odt %s需求分析.odt %s概要设计.odt %s详细设计.odt %s测试计划及结果.odt %s使用手册.odt", path, path, path, path, path, path);

        return system(buf);
    }
    else if(ch == 'u')
    {
        sprintf(buf, "rm %s可行性分析.odt %s需求分析.odt %s概要设计.odt %s详细设计.odt %s测试计划及结果.odt %s使用手册.odt", path, path, path, path, path, path);

        return system(buf);
    }

    
    return 0;
}
