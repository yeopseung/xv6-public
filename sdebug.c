#include "types.h"
#include "stat.h"
#include "user.h"

//fork()로 생성할 프로세스의 개수
#define PNUM 5
//fork()로 생성된 프로세스 중 실행 중인 프로세스 정보를 출력하는 주기
#define PRINT_CYCLE 10000000
//fork()로 생성된 이후부터 소모할 수 있는 시간
#define TOTAL_COUNTER 500000000

void sdebug_func(void)
{
    int n, pid;

    printf(1,"start sdebug command\n");

    //PNUM 만큼 프로세스 생성
    for(n=0; n<PNUM; n++){

        //프로세스 생성
        pid = fork();
        
        //fork 실패 시 반복문 탈출
        if(pid < 0)
        {
            printf(1,"fork failed\n");
            break;
        }

        //자식 프로세스일 경우
        if(pid == 0)
        {
            unsigned long start = uptime();
            unsigned long counter;
            weightset();
            while(1)
            {
                counter = uptime();

                if(counter == PRINT_CYCLE)
                {
                    //printf(1,"PID: %d, WEIGHT: %d, TIMES: %d\n",myproc().pid,myproc().weight,(uptime()-start)*10);
                }

                //
                if(counter == TOTAL_COUNTER)
                    exit();
            }
            
        }
    }

    for(; n > 0; n--)
    {
        if(wait() < 0)
        {
            printf(1, "wait stopped early\n");
            exit();
        }
    }

    if(wait() != -1)
    {
        printf(1, "wait got too many\n");
        exit();
    }


    printf(1,"end of sdebug command\n");
    return;
}

int main(void)
{
    sdebug_func();
    exit();
}