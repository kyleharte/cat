#include <fcntl.h>
#include <stdio.h>
#include <err.h>
#include "cat.h"
#include <string.h>
int main(int argc, char *argv[]){
    
    int fd = fileno(stdin);
    ++argv;
    do {
        if(*argv) {
            if(!strcmp(*argv, "-")){ 
                fd = fileno(stdin);
            } else {
                fd = open(*argv, O_RDONLY);
            }
            if(fd < 0){err(1, "%s", *argv);}
            ++argv;
        }
        cat(fd);
    } while(*argv);
}