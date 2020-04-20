//
// Created by 86151 on 2020/4/5.
//

#ifndef TEST_EXP4_H
#define TEST_EXP4_H

#include "myls.h"
#include <sys/wait.h>
#include "mycp.h"

/*
 * 创建子进程调用mycp，只复制普通的文件，不复制目录
 */
void cpfile(char source_path[], int flag, char target_path[]);

void testCpFile(int argc, char*argv[]);

#endif //TEST_EXP4_H
