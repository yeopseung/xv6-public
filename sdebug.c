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
    for(n=0; n<PNUM; n++)
    {
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
            if(weightset(n+1) == -1)
            {
                exit();
            }
            long start = uptime();
            long end;
            int counter = 0;
            int print_counter = PRINT_CYCLE;
            int first=1;

            while(counter <= TOTAL_COUNTER)
            {
                counter++;
                print_counter--;

                if(print_counter == 0)
                {
                    if(first)
                    {
                        end = uptime();
                        printf(1,"PID: %d, WEIGHT: %d, ",getpid(),n+1);
                        printf(1,"TIMES: %d ms\n",(end-start)*10);
                        first = 0;
                    }
                    
                    print_counter = PRINT_CYCLE;
                }
            } 
            printf(1,"PID: %d terminated\n",getpid());
            exit();
        }

       
    }

    for(; n > 0; n--)
    {
       
        //fork가 생성한 자식 프로세스가 PNUM개 이하일때
        if(wait() < 0)
        {
            printf(1, "wait stopped early\n");
            exit();
        }
    }

    //fork가 생성된 자식 프로세스가 N개 이상일때
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