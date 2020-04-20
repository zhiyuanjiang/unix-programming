#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <myls.h>
#include "mycp.h"
#include "exp4.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "exp5.h"
#include "exp6.h"

//struct BufferPool  {  char Buffer[5][100]; int Index[5]; };

//void* childthread(void *arg)
//{
//    for(int i = 0; i < 10; ++i){
//        printf("child thread message is : %s\n", (char*)arg);
//        // printf("hello world");
//        sleep(1);
//    }
//    return 0;
//}

int main(int argc, char* argv[]) {
    
    // test_mycp(argc, argv);

    // mypwd();

    // test_myls(argc, argv);

    // testCpFile(argc, argv);

    // testCpFileMulthread(argc, argv);

    testPhilosopherProblem();
//    pthread_t ptd;
//    char str[] = "hello world!";
//    printf("create child thread\n");
//    pthread_create(&ptd, NULL, (void*)childthread, str);
//    pthread_join(ptd, NULL);
//    printf("child thread exit\n");

//    int running = 1;
//    void *shm = NULL;
//    struct BufferPool *shared;
//    int shmid; int index;
//    shmid = shmget((key_t)1234, sizeof(struct BufferPool), 0666|IPC_CREAT);
//    if(shmid == -1){
//        exit(EXIT_FAILURE);
//    }
//    shm = shmat(shmid, 0, 0);
//    if(shm == (void*)-1){  exit(EXIT_FAILURE);}
//    shared = (struct BufferPool*)shm;
//    while(running){
//        index=0;
//        if(shared->Index[index]==1){
//            printf("consume buffer: %s", shared->Buffer[index]);
//            shared->Index[index] = 0; sleep(rand() % 3);
//            if(strncmp(shared->Buffer[index], "end", 3) == 0)
//                running = 0;
//        } else{
//            sleep(1);
//            index++ ;
//        }
//    }
//    if(shmdt(shm) == -1){exit(EXIT_FAILURE);}
//    if(shmctl(shmid, IPC_RMID, 0) == -1){
//        exit(EXIT_FAILURE);
//    }
//    exit(EXIT_SUCCESS);

//    int running = 1;
//    void *shm = NULL;
//    struct BufferPool *shared;
//    char buffer[100];
//    int shmid;
//    int index;
//    shmid = shmget((key_t)1234, sizeof(struct BufferPool), 0666|IPC_CREAT);
//    if(shmid == -1){  exit(EXIT_FAILURE);}
//    shm = shmat(shmid, (void*)0, 0);
//    if(shm == (void*)-1){  exit(EXIT_FAILURE);}
//    printf("Memory attached at %X\n", (int)shm);
//    shared = (struct BufferPool*)shm;
//    while(running){
//        index = 0;
//        if(shared->Index[index]==1){
//            sleep(1) ; index++; }
//        else{
//            printf("Enter some text: ");
//            fgets(buffer, 100, stdin);
//            strncpy(shared->Buffer[index], buffer,100);
//            shared->Index[index] = 1;
//            if(strncmp(buffer, "end", 3) == 0)
//                running = 0;
//        }
//    }
//    if(shmdt(shm) == -1) {exit(EXIT_FAILURE);}
//    if(shmctl(shmid, IPC_RMID, 0) == -1) {exit(EXIT_FAILURE);}
//    exit(EXIT_SUCCESS);
    return 0;
}

