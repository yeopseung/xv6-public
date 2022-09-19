#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char* argv[])
{
    int mask = atoi(argv[1]);
    


    //[COMMAND]의 argv 생성
    char *params[argc-2];
    int k=0;
    for(int i=2; i<argc;i++)
    {
        params[k] = argv[i];
        k++;
    }

    //부모프로세스는 자식프로세스 생성
    int pid = fork();
    if(pid<0)
    {
        printf(1,"fork failed\n");
        exit();
    }
    
    //자식프로세스일 경우
    if(pid==0)
    {
        //[COMMAND] 실행
        trace(mask);
        exec(argv[2],params);
        exit();
    }
    
    //부모프로세스는 자식이 종료할 때까지 대기
    if(pid>0)
    {
        wait();
    }

    exit();
}