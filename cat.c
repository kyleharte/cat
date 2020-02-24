#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
void cat(int rfd)
{
    int wfd = fileno(stdout), offset = 0;
    static char *buf;
    static size_t bsize;
    ssize_t nr, nw;
    struct stat sbuf;

    if (fstat(wfd, &sbuf)) {
        err(1, "stdout");
    }
    bsize = sbuf.st_blksize;
    buf = malloc(bsize);
    if(!buf){ err(1,0);}

    nr = read(rfd, buf, bsize);
    while(nr > 0){
        for(offset = 0; nr > 0; nr -= nw, offset += nw){
            nw = write(wfd, buf+offset, nr);
            if(nw < 0 ){err(1, "stdout");}

        }
        nr = read(rfd, buf, bsize);
    }
}