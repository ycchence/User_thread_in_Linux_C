#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>


int uthread_init(void);
int uthread_create(void(*func)(int), int val, int pri);
int uthread_yield(void);
void uthread_exit(void *retval);

struct uthread{
	ucontext_t *ucp;
	int pri;
	int id;
	struct uthread *next;	
};
struct uthread *head=NULL, *que=NULL;
int counter=0, s=0;

int uthread_init()
{
	head=(struct uthread *)malloc(sizeof(struct uthread));
	head->ucp=(ucontext_t *)malloc(sizeof(ucontext_t));
	if (head==0)
		return 0;
	else
		return -1;
	counter=0;
	if (getcontext(head->ucp)!=0)
		return -1;
}


int uthread_create(void(*func)(int), int val, int pri)
{
	struct uthread *ut;
	ut=(struct uthread *)malloc(sizeof(struct uthread));
	ut->ucp=(ucontext_t *)malloc(sizeof(ucontext_t));
	getcontext(ut->ucp); 
	ut->ucp->uc_stack.ss_sp=(void *)malloc(1000000);
	ut->ucp->uc_stack.ss_size=1000000;
	makecontext(ut->ucp, (void (*)()) func, val); 
	ut->pri=pri;
	ut->id=counter;
	

	if(counter == 0){
		que = ut;
		head = ut;		
	}
	else
	{
		while(que -> next != 0)
                    que = que -> next;
		que -> next = ut;
	}	
	counter++;
	return 0;
	
}

void uthread_exit(void *retval)
{
	
	struct uthread *ut;

	ut=head;
	head=head->next;
	setcontext(ut->ucp);
	return;
}

int uthread_yield()
{
	struct uthread *ut1; 
	ut1=(struct uthread *)malloc(sizeof(struct uthread)); 
	ut1->ucp=(ucontext_t *)malloc(sizeof(ucontext_t));  
	while(que -> next != 0)    
		que = que -> next;
	que -> next = ut1;
	struct uthread *ut2;	
	ut2=head;
	head=head->next;
	swapcontext(ut1->ucp, ut2->ucp);
	
	return 0;
}
