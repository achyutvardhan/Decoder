#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int *arr;
    int size;
    int f;
    int r;
    struct queue * prev;
    struct queue *next;
};

int isFull(struct queue *line)
{
    int count = 0;
    while (line != NULL)
    {
        if (line->r == line->size - 1)
        {
            count++;
        }
        line = line->next;
    }
    if (count == 3)
    {
        return 1;
    }
    else
        return 0;
}
int isEmpty(struct queue *line)
{
    int count = 0;
    while (line != NULL)
    {
        if (line->r == line->f)
        {
            count++;
        }
        line = line->next;
    }
    if (count == 3)
    {
        return 1;
    }
    else
        return 0;
}

void insertion(struct queue *line, int value)
{

    if (isFull(line))
    {
        printf("person cannot be added in the queue");
        return;
    }

    while (line != NULL && line->r == line->size - 1)
    {
        line = line->next;
    }
    line->arr[++line->r] = value;
}

void insert(struct queue *line , int val){

  line->arr[line->r]  =  val;
}

int deletion(struct queue *line)
{
    if (isEmpty(line))
    {
        printf("queue is empty cannot deleted");
        return -1;
    }
    int del = line->arr[0];
    while (line!=NULL)
    {
      for(int i = 0;i<line->size;i++ ){
           line->arr[i] = line->arr[i+1];
      }
      line = line->next;
      if (line!=NULL)
      {
      int temp_val = line->arr[0];
      insert(line->prev,temp_val);
      }else{
        line->prev->r--;
      }
      
    }

    return del;
}

void traverse(struct queue *line)
{
    while (line != NULL)
    {
        if (line->r != -1)
        {
            int i = line->f + 1;
            for (; i <= line->r; i++)
            {
                printf("%d ", line->arr[i]);
            }
        }
        line = line->next;
    }
}

int main()
{
    struct queue *line1 = (struct queue *)malloc(sizeof(struct queue));
    struct queue *line2 = (struct queue *)malloc(sizeof(struct queue));
    struct queue *line3 = (struct queue *)malloc(sizeof(struct queue));
    printf("enter the size of boxes\n");
    int size;
    scanf("%d", &size);
    line1->size = line2->size = line3->size = size;
    line1->arr = (int *)malloc(size * sizeof(int));
    line2->arr = (int *)malloc(size * sizeof(int));
    line3->arr = (int *)malloc(size * sizeof(int));
    line1->next = line2;
    line2->next = line3;
    line3->next = NULL;
    line1->prev = NULL;
    line2->prev = line1;
    line3->prev = line2;
    line1->f = line2->f = line3->f = -1;
    line1->r = line2->r = line3->r = -1;
    int val;
    printf("enter your choice \n 1. insert \n 2. delete \n 3. traverse \n 4. Exit");
    int a;
    while (a != 4)
    {
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            printf("enter value \n ");
            scanf("%d", &val);
            insertion(line1, val);
            break;
        case 2:
            printf("person exited %d", deletion(line1));
            break;
        case 3:
            traverse(line1);
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("invalid input");
            break;
        }
    }

    return 0;
}
