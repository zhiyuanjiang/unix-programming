//
// Created by 86151 on 2020/4/20.
//

#ifndef TEST_EXP6_H
#define TEST_EXP6_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


/*
 * 模拟哲学家拿起一只筷子。
 * number - 某只筷子编号
 */
int takechopstick(int number, int flag);

/*
 * 模拟哲学家放下一只筷子
 */
int putchopstick(int number);

/*
 * 模拟一个哲学家
 * number - 哲学家编号
 */
void philosopher(int number);

/*
 * 使用trylock避免死锁
 */
void philosopher2(int number);

/*
 * 使用奇偶号哲学家拿筷子的顺序不同，避免死锁
 */
void philosopher3(int number);


/*
 * 创建一个哲学家线程
 */
void *createPhilosopherThread(void*);


void testPhilosopherProblem();

#endif //TEST_EXP6_H
