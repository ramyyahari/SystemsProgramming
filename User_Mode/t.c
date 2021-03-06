
/**************************************************
  I/O , queue functions and load() are in mtxlib
**************************************************/
#include "wait.c"          // YOUR OWN wait.c file:
#include "kernel.c"        // YOUR OWN kernel.c file
#include "int.c"           // YOUR OWN int.c file
#include "type.h"
#include "queue.c"
int procSize = sizeof(PROC);

int body();
char *pname[]={"A", "B", "C", "D",  "E", "F","G", "H", "I","J", "K","L","M","N","O","P" };

int init()
{
    PROC *p; int i;
    printf("init ....");
    for (i=0; i < NPROC; i++){   // initialize all procs
        p = &proc[i];
        p->pid = i;
        p->status = FREE;
        p->priority = 0;  
        strcpy(proc[i].name, pname[i]);
   
        p->next = &proc[i+1];
    }
    freeList = &proc[0];      // all procs are in freeList
    proc[NPROC-1].next = 0;
    readyQueue = sleepList = 0;

    /**** create P0 as running ******/
    p = get_proc(&freeList);
    p->status = READY;
    p->ppid   = 0;
    p->parent = p;
    running = p;
    printf("done\n");
} 

int scheduler()
{
    if (running->status == READY){
        enqueue(&readyQueue, running);
    }
    running = dequeue(&readyQueue);
}

int int80h();

int set_vec(u16 vector, u16 handler)
{
  // put_word(word, segment, offset) in mtxlib
     put_word(handler, 0, vector<<2);
     put_word(0x1000,  0, (vector<<2) + 2);
}
            
main()
{
    printf("MTX starts in main()\n");
    init();      // initialize and create P0 as running
    set_vec(80, int80h);

    kfork("/bin/u1");     // P0 kfork() P1

    while(1){
      printf("P0 running\n");
      while(!readyQueue);
      printf("P0 switch process\n");
      tswitch();   // P0 switch to run P1
   }
}
=================================================================
