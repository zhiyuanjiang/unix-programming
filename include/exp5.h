//
// Created by 86151 on 2020/4/19.
//

#ifndef TEST_EXP5_H
#define TEST_EXP5_H

#include "exp4.h"
#include <pthread.h>

struct FilePathData{
    char *source_path, *target_path;
};

/*
 * 使用多线程复制文件
 */
void cpfile_multhread(char source_path[], char target_path[], int flag);

/*
 * 开启一个线程复制普通的文件（非文件夹）
 */
void* cpfile_thread(void *arg);

/*
 * 开启一个线程复制文件夹
 */
void* cpdir_thread(void *arg);

/*
 * 测试使用多线程复制文件
 */
void testCpFileMulthread(int argc, char *argv[]);

#endif //TEST_EXP5_H
