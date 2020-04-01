//
// Created by 86151 on 2020/3/20.
//

#ifndef TEST_MYINSTRUCTOR_H
#define TEST_MYINSTRUCTOR_H

#include "apue.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

/*
 * 文件信息
 */
struct file_info{
    char file_mode[12];
    int num_link;
    char gr_name[255];
    char ur_name[255];
    int file_size;
    char file_name[255];
    char link_name[255];  //链接文件的名字
    int is_link;
    time_t time;
};

/*
 * 根据文件最后的修改时间从晚到早排序
 */
int mtime_cmp(struct file_info *lhs, struct file_info *rhs);

/*
 * 获取一个整形的长度
 */
int getIntLen(int val);

/*
 * mypwd:获取当前所在路径
 * return:
 *      - 返回指向当前目录地址字符串的指针
 */
char* mypwd();

/*
 * myls: ls命令
 * params:
 *      flag - 0:打印详细命令信息, 1: ls, 2: ls -l, 3: ls -l -a
 */
void myls(int flag);

/*
 * 输入参数
 */
void test_myls(int argc, char *argv[]);

/*
 * ls 打印
 */
void print_ls(struct file_info files[], int cnt);

/*
 * ls -l 打印
 * params:
 *      flag - 0:不打印隐藏文件, 1:打印隐藏文件
 */
void print_ls_l(struct file_info files[], int cnt, int flag);

/*
 * ls -l -a 打印
 */
void print_ls_l_a(struct file_info files[], int cnt);

/*
 * 打印输入参数信息
 */
void print_cmd_info();

/*
 * stmodeToString: 将st_mode --> -rwx--x--x
 * params:
 *      buf - 转换后的字符串
 *      mode_t - 文件类型和权限
 */
void modeToString(char *buf, mode_t st_mode);

#endif //TEST_MYSTDIO_H
