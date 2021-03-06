//#include "type.h"

int fork()
{
    int pid;
    printf("proc %d enter kernel to kfork a child\n", getpid());
    pid = syscall(3, 0, 0);
    if (pid>0)
      printf("proc %d kforked a child %d\n", getpid(), pid);
    else
      printf("kforked failed\n");
}    

int exec()
{
  int r;
  char filename[32];
  printf("enter exec filename : ");
  gets(filename);
  r = syscall(8,filename,0,0);
  printf("exec failed\n");
}

PROC * kfork(char *filename)
{
	int i=1;
	PROC *p = get_proc(&freeList);
	u16 segment;
	if (!p)
	{
		printf("no more PROC, kfork() failed\n");	
		return 0;
	}

	/* initialize the new proc and kstack */
	p->status = READY;
	p->ppid = running->pid;
	p->priority = 1;                     // priority = 1
	p->kstack[SSIZE-1] = (int)body;      // start to run body()  
	p->ksp = &(p->kstack[SSIZE-9]);    // SEE REQUIREMENTS BELOW
	enqueue(&readyQueue,p);

	segment=0x2000+(p->pid-1)*0x0800;

	load("/bin/u1",segment);
	printf("Loaded segment");  

	while(i<9)
	{
		u16 store;
		if(i==1)
			store=0x0200;
		if(i==2||i==7||i==8)
			store=segment;
		else 
			store=0;
	}
	put_word(store,segment,-(i*2));
	i++;
	}
	p->uss=segment;
	p->usp=-8*2;
	return(p->pid);
}

int kexec()
{
  int r;
  char filename[32];
  printf("enter exec filename : ");
  gets(filename);
  r = syscall(8,filename,0);
  if(!r)
  printf("exec failed\n");
}


