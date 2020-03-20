//
// Created by 86151 on 2020/3/20.
//
# include "mycp.h"

#define MAX_SIZE 255

void mycp(const char* source_filepath, const char* target_filepath)
{
    int fd1 = open(source_filepath, O_RDWR);
    int fd2 = open(target_filepath, O_WRONLY|O_CREAT|O_TRUNC);

    if(fd1 == -1){
        printf("mycp: open %s failed", source_filepath);
        exit(-1);
    }
    if(fd2 == -1){
        printf("mycp: open %s failed", target_filepath);
        exit(-1);
    }

    char buf[256];
    int num = 0;
    while((num = read(fd1, buf, 256)) != 0){
        write(fd2, buf, num);
    }

    close(fd1);
    close(fd2);
}

void mycp2(char* source_path, char* target_path)
{
    int len1 = strlen(source_path), len2 = strlen(target_path);
    char path1[len1+MAX_SIZE+1], path2[len2+MAX_SIZE+1];

    // 打开文件夹
    DIR* mydir = opendir(source_path);
    if(mydir == NULL){
        printf("open %s failed\n", source_path);
        perror("mycp:");
        exit(-1);
    }

    dirent* mydirent = NULL;
    // 获取文件夹内文件的信息
    while((mydirent = readdir(mydir)) != NULL){

        if(strcmp(".", mydirent->d_name) == 0 || strcmp("..", mydirent->d_name) == 0)
            continue;

        strcpy(path1, source_path);
        strcpy(path2, target_path);
        strcat(path1, "/");
        strcat(path1, mydirent->d_name);
        strcat(path2, "/");
        strcat(path2, mydirent->d_name);

        if(mydirent->d_type == 4){
            // 为什么是775
            if(mkdir(path2, 0775) == -1){
                printf("target_path: %s create failed", target_path);
                perror("mycp");
                exit(-1);
            }
            mycp2(path1, path2);
        }else{
            mycp(path1, path2);
            struct stat buf[MAX_SIZE];
            if(stat(path1, buf) == -1) {
                perror("np");
                exit(-1);
            }
            printf("%s %d\n", path2, buf->st_mode);
            //修改文件权限
            if(chmod(path2, buf->st_mode) == -1){
                perror("np");
                exit(-1);
            }
        }
    }

    closedir(mydir);
}

void test_mycp(int argc, char*argv[])
{
    if(argc == 3){
        char* source_filepath = argv[1];
        char* target_filepath = argv[2];

        mycp(source_filepath, target_filepath);
    }

    if(argc == 4 && strcmp("-r", argv[1]) == 0){
        char* source_filedir_path = argv[2];
        char* target_filedir_path = argv[3];

        int len1 = strlen(source_filedir_path);
        int len2 = strlen(target_filedir_path);
        char name[len2+MAX_SIZE];

        if(target_filedir_path[len2-1] == '/'){
            // 补全target_filedir_path
            int pos = 0;
            for(int i = len1-1; i >= 0; --i){
                if(source_filedir_path[i] == '/'){
                    pos = i+1; break;
                }
            }
            strcpy(name, target_filedir_path);
            for(int i = 0; i < len1-pos+1; ++i) {
                // 最后一个字符要是'\0'
                name[len2 + i] = source_filedir_path[pos + i];
            }
            target_filedir_path = name;
        }
        // printf("%s\n", target_filedir_path);
        if(mkdir(target_filedir_path, 0775) == -1){
            perror("mycp");
            exit(-1);
        }
        mycp2(source_filedir_path, target_filedir_path);
        printf("%d\n", (mode_t)0775);
    }
}
