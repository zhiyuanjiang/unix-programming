#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "mycp.h"


int main(int argc, char* argv[]) {

    test_mycp(argc, argv);

    return 0;
}

