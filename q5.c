#include <stdio.h>
#include <stdlib.h>

struct node
{
    int pid;
    int cpu_time;
    struct node *next;
};

int quantum;

void printList(struct node *head)
{
    while (head != NULL)
    {
        printf("%d %d\n", head->pid, head->cpu_time);
        head = head->next;
    }
}

void deleteNode(struct node **head_ref, int pid)
{
    struct node *temp = *head_ref, *prev;

    if (temp != NULL && temp->pid == pid)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->pid != pid)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp);
}

void push(struct node **head_ref, int pid, int cpu_time)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->pid = pid;
    temp->cpu_time = cpu_time;
    temp->next = (*head_ref);
    (*head_ref) = temp;
}

void append(struct node **head_ref, int pid, int cpu_time)
{
    struct node *temp = *head_ref;
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->pid = pid;
    new_node->cpu_time = cpu_time;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;
    return;
}

int main()
{
    struct node *head = NULL;
    int pid, cpu_time, choice;

    printf("Enter the quantum time: ");
    scanf("%d", &quantum);

    while (1)
    {
        printf("\nEnter your choice:\n");
        printf("1. Enter a process\n2. Run a process\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the process ID: ");
            scanf("%d", &pid);
            printf("Enter the CPU time: ");
            scanf("%d", &cpu_time);
            append(&head, pid, cpu_time);
            break;

        case 2:
            if (head == NULL)
            {
                printf("No processes to run!\n");
            }
            else
            {
                printf("Enter the process ID to run: ");
                scanf("%d", &pid);
                head->pid = pid;
                head->cpu_time -= quantum;
                printf("Process %d is running for %d units of time\n", pid, quantum);

                if (head->cpu_time <= 0)
                {
                    printf("Process %d has completed!\n", pid);
                    deleteNode(&head, pid);
                }
                else
                {
                    append(&head, pid, head->cpu_time);
                    deleteNode(&head, pid);
                }
            }
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("Invalid choice!\n");
        }

        printf("Processes in the queue: ");
        printList(head);
    }
}