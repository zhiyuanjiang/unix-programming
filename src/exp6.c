//
// Created by 86151 on 2020/4/20.
//

#include "exp6.h"

#define PHI_NUM 2
pthread_mutex_t phi_mutex[PHI_NUM];

int takechopstick(int number, int flag)
{
    if(flag == 0)
        return pthread_mutex_lock(&phi_mutex[number]);
    if(flag == 1)
        return pthread_mutex_trylock(&phi_mutex[number]);
}

int putchopstick(int number)
{
    return pthread_mutex_unlock(&phi_mutex[number]);
}

void philosopher(int number)
{
    while(1){
        printf("philosopher %d is thinking\n", number);
        // sleep(1);
        takechopstick(number, 0);
        takechopstick((number+1)%PHI_NUM, 0);
        printf("philosopher %d is eating\n", number);
        // sleep(2);
        putchopstick(number);
        putchopstick((number+1)%PHI_NUM);
    }
}

void philosopher2(int number)
{
    while(1){
        printf("philosopher %d is thinking\n", number);
        // sleep(1);
        if(takechopstick(number, 1) == 0) {
            if (takechopstick((number + 1) % PHI_NUM, 1) == 0) {
                printf("philosopher %d is eating\n", number);
                // sleep(2);
                putchopstick(number);
                putchopstick((number + 1) % PHI_NUM);
            }else{
                putchopstick(number);
                // sleep(1);
            }
        }else{
            // sleep(1);
        }
    }
}

void philosopher3(int number)
{
    while(1){
        printf("philosopher %d is thinking\n", number);
        // sleep(1);
        if(number%2 == 0){
            takechopstick(number, 0);
            takechopstick((number+1)%PHI_NUM, 0);
        }else{
            takechopstick((number+1)%PHI_NUM, 0);
            takechopstick(number, 0);
        }

        printf("philosopher %d is eating\n", number);
        // sleep(2);
        if(number%2 == 0){
            putchopstick(number);
            putchopstick((number+1)%PHI_NUM);
        }else{
            putchopstick((number+1)%PHI_NUM);
            putchopstick(number);
        }
    }
}


void *createPhilosopherThread(void *arg)
{
    int *number = (int*)arg;
    philosopher2(*number);
}

void testPhilosopherProblem()
{
    for(int i = 0; i < PHI_NUM; ++i){
        pthread_mutex_init(&phi_mutex[i], NULL);
    }

    pthread_t ptd[PHI_NUM];
    int number[PHI_NUM];
    for(int i = 0; i < PHI_NUM; ++i) number[i] = i;
    for(int i = 0; i < PHI_NUM; ++i){
        printf("thread %d start\n", i);
        // 好几次忘记传入指针了。
        pthread_create(&ptd[i], NULL, createPhilosopherThread, &number[i]);
    }

    while(1);
}