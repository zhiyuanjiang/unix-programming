//
// Created by 86151 on 2020/4/19.
//

#include "exp5.h"

void* cpfile_thread(void *arg)
{
    struct FilePathData* pathData = (struct FilePathData*)arg;
    mycp(pathData->source_path, pathData->target_path);
    printf("copy file %s success\n", pathData->source_path);
    return 0;
}

void* cpdir_thread(void *arg)
{
    struct FilePathData *pathData = (struct FilePathData*)arg;
    cpfile_multhread(pathData->source_path, pathData->target_path, 1);
    return 0;
}

void cpfile_multhread(char source_path[], char target_path[], int flag)
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

    int cnt = 0;
    while((mydirent = readdir(mydir)) != NULL) cnt++; // 获取一个dir中file的个数
    pthread_t myptd[cnt+2];
    char new_source_path[cnt+2][len1+256], new_target_path[cnt+2][len2+256];
    seekdir(mydir, 0); // 重新定位到文件头
    cnt = 0;

    while((mydirent = readdir(mydir)) != NULL){
        if(strcmp(mydirent->d_name, ".") == 0 || strcmp(mydirent->d_name, "..") == 0)
            continue;

        // get new source file path
        strcpy(new_source_path[cnt], pwd);
        strcat(new_source_path[cnt], "/");
        strcat(new_source_path[cnt], mydirent->d_name);

        struct stat buf[255];
        if(lstat(new_source_path[cnt], buf) == -1) {
            perror("np");
            exit(-1);
        }

        // get new target file path
        strcpy(new_target_path[cnt], target_path);
        strcat(new_target_path[cnt], "/");
        strcat(new_target_path[cnt], mydirent->d_name);

        // 结构体指针要初始化，指针太鸡贼了
        // 因为我在这里没有初始化，然后就对结构体内部变量进行复制，所以就一直出错，段错误
        struct FilePathData *pathData = (struct FilePathData*)malloc(sizeof(struct FilePathData));
        pathData->source_path = new_source_path[cnt];
        pathData->target_path = new_target_path[cnt];

        // 在这里test是一个exe文件, 因为复制的是当前可执行文件的目录, 不能复制自己。
        if(strcmp(mydirent->d_name, "test") == 0)
            continue;

        // use multiply thread
        if(S_ISDIR(buf->st_mode)){
            // 文件夹处理
            printf("create a thread to copy dir, dir name is : %s!\n", new_source_path[cnt]);
            pthread_create(&myptd[cnt], NULL, (void*)cpdir_thread, pathData);
            // pthread_join(ptd, NULL);
            // printf("copy dir thread exit\n");
        }else{
            printf("create a thread to copy file, file name is : %s!\n", new_source_path[cnt]);
            pthread_create(&myptd[cnt], NULL, (void*)cpfile_thread, pathData);
            // pthread_join(ptd, NULL);
            // printf("copy file thread exit\n");
        }
        cnt++;
    }

    // 阻塞主线程，不然主线程运行完了，子线程还没运行完
    for(int i = 0; i < cnt; ++i)
        pthread_join(myptd[i], NULL);
    printf("copy dir: %s success\n", pwd);
}

void testCpFileMulthread(int argc, char *argv[])
{
    if(argc == 2)
        cpfile_multhread(NULL, argv[1], 0);

    if(argc == 3)
        cpfile_multhread(argv[1], argv[2], 1);
}
