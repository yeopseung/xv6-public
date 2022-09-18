#include "types.h"
#include "user.h"
#include "stat.h"

#define SIZE 2048

int main(void)
{

    //현재 프로세스의 메모리 사용량
    int msize = memsize();
    printf(1,"The process is using %dB\n",msize);

    //2048Byte 메모리 할당
    char *tmp = (char*) malloc(SIZE * sizeof(char));

    //메모리 할당 후의 메모리 사용량
    printf(1,"Allocating more memory\n");
    msize = memsize();
    printf(1,"The process is using %dB\n",msize);

    //2048Byte의 메모리 해제
    free(tmp);
    printf(1,"Freeing memory\n");

    //메모리 해제 후의 메모리 사용량
    msize = memsize();
    printf(1,"The process is using %dB\n",msize);

    exit();
}