#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
int flag = 1;
struct node *create()
{
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    int x;
    printf("Enter value (-1 for null value) ");
    scanf("%d", &x);
    if (x == -1)
    {
        return NULL;
    }
    new_node->data = x;
    printf("Enter left node data for %d \n", new_node->data);
    new_node->left = create();

    printf("Enter right node data for %d \n", new_node->data);
    new_node->right = create();

    return new_node;
}
void traverse(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
}

void traversecheck(struct node *root_1, struct node *root_2)
{
    if (root_1 == NULL && root_2 == NULL)
    {
        return;
    }
    if (root_1->data != root_2->data)
    {
        flag = 0;
        return;
    }
    traversecheck(root_1->left, root_2->right);
    traversecheck(root_1->right, root_2->left);
}

int main()
{
    struct node *root;
    root = create();
    printf("Traverse inorder \n");
    traverse(root);
    traversecheck(root->left, root->right);
    if (flag)
    {
        printf("\nMirror \n");
    }
    else
    {
        printf("\nNot mirror\n");
    }
}