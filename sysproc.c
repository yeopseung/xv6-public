#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//sys_memsize() : 호출한 프로세스의 메모리 사용량을 리턴해줌.
int sys_memsize(void)
{
    uint size;

    //proc.c 의 myproc 함수 호출
    struct proc *curproc = myproc();
    
    //struct proc 의 호출한 프로세스의 메모리 사용량을 size에 저장
    size = curproc->sz;

    // 결과 리턴
    return size;

}

//sys_trace() : 호출한 프로세스, 이후 생성되는 모든 자식 프로세스에 대한 trace mask 활성화.
int sys_trace(void)
{
    if(argint(0,&myproc()->mask)<0)
      return -1;

    return 0;
}

//sys_weightset() : 매개변수로 입력받은 값을 sdebug 명령어에 의해 생성되는 프로세스의 weight 값으로 부여.
int sys_weightset(void)
{ 
  int weight;
  //입력받은 값을 프로세스의 weight 값으로 부여
  if(argint(0,&weight)<0)
    return -1;

  if(weight == 0)
  {
    cprintf("weight error: weight 값이 0입니다.\n");
    return -1;
  }

  do_weightset(weight);
  return 0;
}