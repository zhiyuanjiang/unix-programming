#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <myls.h>
#include "mycp.h"
#include "exp4.h"


int main(int argc, char* argv[]) {
    
    // test_mycp(argc, argv);

    // mypwd();

    // test_myls(argc, argv);

    testCpFile(argc, argv);

    return 0;
}

