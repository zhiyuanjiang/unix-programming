//
// Created by 86151 on 2020/3/20.
//
#include "myinstructor.h"

#define MAX_SIZE 255

char* mypwd()
{
    char *ptr;
    size_t size;
    ptr = path_alloc(&size);
    if(getcwd(ptr, size) == NULL){
        err_sys("getcwd failed");
    }
    // printf("cwd= %s\n", ptr);
    return ptr;
}

void modeToString(char *buf, mode_t st_mode)
{
    buf[10] = '\0';
    for(int i = 0; i < 10; ++i) buf[i] = '-';
    if(S_ISDIR(st_mode))  buf[0] = 'd';
    if(S_ISCHR(st_mode))  buf[0] = 'c';
    if(S_ISBLK(st_mode))  buf[0] = 'b';
    if(S_ISFIFO(st_mode)) buf[0] = 'p';
    if(S_ISLNK(st_mode))  buf[0] = 'l';
    if(S_ISSOCK(st_mode)) buf[0] = 's';
    if(st_mode & S_IROTH) buf[7] = 'r';
    if(st_mode & S_IWOTH) buf[8] = 'w';
    if(st_mode & S_IXOTH) buf[9] = 'x';
    if(st_mode & S_IRGRP) buf[4] = 'r';
    if(st_mode & S_IWGRP) buf[5] = 'w';
    if(st_mode & S_IXGRP) buf[6] = 'x';
    if(st_mode & S_IRUSR) buf[1] = 'r';
    if(st_mode & S_IWUSR) buf[2] = 'w';
    if(st_mode & S_IXUSR) buf[3] = 'x';
    if(st_mode & S_ISUID) buf[3] = 's';
    if(st_mode & S_ISGID) buf[6] = 's';
}

int mtime_cmp(struct file_info *lhs, struct file_info *rhs)
{
    return lhs->time < rhs->time;
}

int getIntLen(int val)
{
    int cnt = 0;
    while(val){
        val /= 10;
        cnt++;
    }
    return cnt;
}

void myls(int flag)
{
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
    // 获取文件个数
    int num_file = 0;
    while((mydirent = readdir(mydir)) != NULL) num_file++;

    // 重新定位到第一个文件
    seekdir(mydir, 0);

    // 存储目录下的文件信息
    struct file_info files[num_file+5];

    int len = strlen(pwd);
    char lastDir[len], filePath[len+MAX_SIZE];
    strcpy(lastDir, pwd);
    for(int i = len-1; i >= 0; --i){
        if(pwd[i] == '/'){
            lastDir[i] = '\0';
            break;
        }
    }

    // 获取文件夹内文件的信息
    int cnt = 0;
    while((mydirent = readdir(mydir)) != NULL) {

        // 获取文件的绝对路径
        if(strcmp(".", mydirent->d_name) == 0){
            strcpy(filePath, pwd);
        }else if(strcmp("..", mydirent->d_name) == 0){
            strcpy(filePath, lastDir);
        }else{
            strcpy(filePath, pwd);
            strcat(filePath, "/");
            strcat(filePath, mydirent->d_name);
        }

        // 读取文件状态信息
        struct stat buf[MAX_SIZE];
        if(lstat(filePath, buf) == -1) {
            perror("np");
            exit(-1);
        }

        char *link_name[MAX_SIZE];

        modeToString(files[cnt].file_mode, buf->st_mode);
        strcpy(files[cnt].file_name, mydirent->d_name);
        files[cnt].is_link = 0;
        // 如果是一个链接文件，获取链接到的文件名字
        if(S_ISLNK(buf->st_mode)){
            readlink(filePath, link_name, MAX_SIZE);
            // printf("test %s\n", test);
            strcpy(files[cnt].link_name, link_name);
            files[cnt].is_link = 1;
        }

        files[cnt].num_link = buf->st_nlink;
        // 获取uid 对应的名字
        strcpy(files[cnt].ur_name, getpwuid(buf->st_uid)->pw_name);
        // 获取gid 对应的名字
        strcpy(files[cnt].gr_name, getgrgid(buf->st_gid)->gr_name);
        files[cnt].file_size = buf->st_size;
        files[cnt].time = buf->st_mtim.tv_sec;
        cnt++;

    }

    qsort(files, cnt, sizeof(struct file_info), mtime_cmp);

    if(flag == 1){
        print_ls(files, cnt);
    }
    if(flag == 2){
        print_ls_l(files, cnt, 0);
    }
    if(flag == 3){
        print_ls_l_a(files, cnt);
    }

}

void print_ls(struct file_info files[], int cnt)
{
    for(int i = 0; i < cnt; ++i){
        if(files[i].file_name[0] == '.') continue;
        printf("%s  ", files[i].file_name);
    }
    printf("\n");
}

void print_ls_l(struct file_info files[], int cnt, int flag)
{
    int max_ur_name, max_gr_name, max_link, max_size, L;
    max_ur_name = max_gr_name = max_link = max_size = 0;
    for(int i = 0; i < cnt; ++i){
        L = strlen(files[i].ur_name);
        if(max_ur_name < L) max_ur_name = L;
        L = strlen(files[i].gr_name);
        if(max_gr_name < L) max_gr_name = L;
        if(max_link < files[i].num_link) max_link = files[i].num_link;
        if(max_size < files[i].file_size) max_size = files[i].file_size;
    }
    max_link = getIntLen(max_link);
    max_size = getIntLen(max_size);

    char *str_time[32];
    for(int i = 0; i < cnt; ++i){
        if(flag == 0 && files[i].file_name[0] == '.') continue;

        struct tm *ptm = gmtime(&files[i].time);
        strftime(str_time, 32, "%b %e %R", ptm);

        char filename[2*MAX_SIZE];
        strcpy(filename, files[i].file_name);
        if(files[i].is_link == 1){
            strcat(filename, " --> ");
            strcat(filename, files[i].link_name);
        }

        printf("%s %*d %*s %*s %*d %s %s\n", files[i].file_mode, max_link, files[i].num_link,
               max_ur_name, files[i].ur_name,
               max_gr_name, files[i].gr_name,
               max_size, files[i].file_size,
               str_time, filename);
    }
}

void print_ls_l_a(struct file_info files[], int cnt)
{
    print_ls_l(files, cnt, 1);
}

void test_myls(int argc, char *argv[])
{
    int flag = 0;
    if(argc == 1) flag = 1;
    if(argc == 2 && strcmp(argv[1], "-l") == 0) flag = 2;
    if(argc == 3 && strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "-a") == 0) flag = 3;
    if(flag == 0){
        print_cmd_info();
    }else{
        myls(flag);
    }
}

void print_cmd_info()
{
    printf("parameters of input is error!\n");
    printf("-l show information of files\n");
    printf("-a show files of hidden\n");
}
