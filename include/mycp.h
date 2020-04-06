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
/*
 * mycp:复制一个文件到另一个地址
 *
 * :params
 *      source_filepath:源文件地址
 *      target_filepath:目标文件地址
 *
 */
void mycp(const char* source_filepath, const char* target_filepath);
/*
 * mycp2:复制一个文件夹到另一个地址, 每次都要创建新的文件夹
 *
 * :params
 *      source_path:源文件夹地址
 *      target_path:目标文件夹地址
 */
void mycp2(char* source_path, char* target_path);

/*
 * test_mycp:测试cp指令
 *
 * :params
 *      argc:参数个数
 *      argv:参数
 *      -r - 文件夹复制
 */
void test_mycp(int argc, char*argv[]);

/*
 * 填充路径，对于最后一位为'/'的target_path进行填充，buf指向新的文件地址
 * params:
 *      buf - 指向填充后的文件地址
 *      source_path - 源文件地址
 *      target_path - 目标文件地址
 */
void pad_path(char buf[], char *source_path, char *target_path);

#endif //TEST_MYCP_H
