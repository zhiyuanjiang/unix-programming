#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "mycp.h"

const int MAX_SIZE = 255;


int main(int argc, char* argv[]) {

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
    return 0;
}

