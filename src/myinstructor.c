//
// Created by 86151 on 2020/3/20.
//
#include "myinstructor.h"

void mypwd()
{
    char *ptr;
    size_t size;
    ptr = path_alloc(&size);
    if(getcwd(ptr, size) == NULL){
        err_sys("getcwd failed");
    }
    printf("cwd= %s\n", ptr);
}