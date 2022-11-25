#include<stdio.h>
#include<stdlib.h>
#define size 5
int items[4][size];
void insert(int x,int*front,int*rear,int q)
{
	if(*front == (*rear+1)%size){
		printf("Deque is full!");
		exit(0);
	}
	else{
		*rear = (*rear+1)%size;
		if(*front == -1) *front = 0;
		items[q-1][*rear] = x;
	}
}
void deletion(int *front, int *rear, int q)
{
	int element;
    if (*front == -1) 
	{
		printf("\n Queue is empty !! \n");
    } 
    else 
    {  
		element = items[q-1][*front];
		if(*front == *rear)
			*front = *rear = -1; 
		else
			*front = (*front+1) % size;
		printf("Deleted element: %d", element);
  	}
}
int display(int*front,int*rear, int q)
{
	int i;
    if (*front<0)
	    printf(" \n Empty Queue\n");
    else 
	{
	    printf("\n Front -> %d ", *front);
	    printf("\n Rear -> %d \n", *rear);
	    printf("\n Items -> ");
	    for (i = *front; i != *rear; i = (i+1)%size) 
		{

	      printf("%d ", items[q-1][i]);
	    }
	    printf("%d ", items[q-1][i]);
	    
    }
}

int main()
{
	int ch,x;
	int f1,f2,f3,f4,r1,r2,r3,r4;
	f1 = f2 = f3 = f4 = r1 = r2 = r3 = r4 = -1;
	
	
	printf("\t\t 4-queue\n");
	printf("-------------------------------------------------\n");
	while(1)
	{
		printf("\n1.insert queue1\n2.insert queue2\n3.insert queue3\n4.insert queue4\n5.delete\n6.display\n7.exit\nyour choice :");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("enter the value of element to inseertin 1st queue :");
				scanf("%d",&x);
				insert(x,&f1,&r1,1);
				break;
			case 2:
				printf("enter the value of element to inseert in 2nd queue:");
				scanf("%d",&x);
				insert(x,&f2,&r2,2);
				break;
			case 3:
				printf("enter the value of element to inseert in 3rd queue:");
				scanf("%d",&x);
				insert(x,&f3,&r3,3);
				break;
			case 4:
				printf("enter the value of element to inseert in 4th queue:");
				scanf("%d",&x);
				insert(x,&f4,&r4,4);
				break;
			case 5:
				printf("enter the queue to delete:");
				scanf("%d",&x);
				if(x==1)
					deletion(&f1,&r1,1);
				if(x==2)
					deletion(&f2,&r2,2);
				if(x==3)
					deletion(&f3,&r3,3);
				if(x==4)
					deletion(&f4,&r4,4);
				break;
			case 6:
				printf("queue1: ");
				display(&f1,&r1,1);
				printf("\nqueue2: ");
				display(&f2,&r2,2);
				printf("\nqueue3: ");
				display(&f3,&r3,3);
				printf("\nqueue4: ");
				display(&f4,&r4,4);
				break;
			case 7:
				exit(0);
		}
	}
}
