//
// Created by 86151 on 2020/3/20.
//

#ifndef TEST_MYCP_H
#define TEST_MYCP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


void mycp(const char* source_filepath, const char* target_filepath);
void mycp2(char* source_path, char* target_path);

#endif //TEST_MYCP_H
