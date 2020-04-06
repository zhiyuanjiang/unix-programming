//
// Created by 86151 on 2020/4/5.
//

#include "exp4.h"


void cpfile(char source_path[], int flag, char target_path[])
{
    // 当前路径
    char* pwd;
    if(flag == 0)
        pwd = mypwd();
    else
        pwd = source_path;

    int len1 = strlen(pwd);
    int len2 = strlen(target_path);

    char tmp_path[len2+256];
    pad_path(tmp_path, pwd, target_path);
    target_path = tmp_path;
    len2 = strlen(target_path);

    if(mkdir(target_path, 0775) == -1){
        printf("create dir %s failed\n", target_path);
        exit(-1);
    }

    // 打开文件夹
    DIR* mydir = opendir(pwd);
    if(mydir == NULL){
        printf("open %s failed\n", pwd);
        perror("mycp:");
        exit(-1);
    }
    struct dirent* mydirent = NULL;

    char filePath[len1+256], target_path2[len2+256];

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

        strcpy(target_path2, target_path);
        strcat(target_path2, "/");
        strcat(target_path2, mydirent->d_name);

        // 文件夹不需要复制

        int pid = fork();
        if(pid == 0){
            // 一定要传入arg0
            if(S_ISDIR(buf->st_mode))
                // exit(0);
                execl("./test", "./test", filePath, target_path2, NULL);
            else
                execl("/home/yuan/bin/mycp", "/home/yuan/bin/mycp", filePath, target_path2, NULL);
            printf("execl error");
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
}


void testCpFile(int argc, char*argv[])
{
    if(argc == 2)
        cpfile(NULL, 0, argv[1]);

    if(argc == 3)
        cpfile(argv[1], 1, argv[2]);
}