#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <myls.h>
#include "mycp.h"


int main(int argc, char* argv[]) {

    test_mycp(argc, argv);

    // mypwd();

    // test_myls(argc, argv);

    return 0;

    // 当前路径
    char* pwd = mypwd();

    // 打开文件夹
    DIR* mydir = opendir(pwd);
    if(mydir == NULL){
        printf("open %s failed\n", pwd);
        perror("mycp:");
        exit(-1);
    }
    struct dirent* mydirent = NULL;

    int len = strlen(pwd);
    char lastDir[len], filePath[len+255];
    strcpy(lastDir, pwd);
    for(int i = len-1; i >= 0; --i){
        if(pwd[i] == '/'){
            lastDir[i] = '\0';
            break;
        }
    }

    while((mydirent = readdir(mydir)) != NULL){
        if(strcmp(mydirent->d_name, ".") == 0 || strcmp(mydirent->d_name, "..") == 0)
            continue;

        strcpy(filePath, pwd);
        strcat(filePath, "/");
        strcat(filePath, mydirent->d_name);

        struct stat buf[255];
        if(lstat(filePath, buf) == -1) {
            perror("np");
            exit(-1);
        }

        // 文件夹不需要复制
        if(S_ISDIR(buf->st_mode))
            continue;

        int pid = fork();
        if(pid == 0){
            execl("/bin/cp", filePath, "/home/yuan/test/cmake-build-debug/fuck/", NULL);
            exit(0);
        }

        int re_pid = 0;
        while(re_pid == 0){
            re_pid = waitpid(pid, NULL, WNOHANG);
            printf("%s wait copy ending\n", filePath);
            sleep(1);
        }

        if(re_pid == pid){
            printf("copy success\n");
        }
    }

    printf("success\n");

    return 0;
}

