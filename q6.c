#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};

struct tree *create(int value)
{
    struct tree *node = (struct tree *)malloc(sizeof(struct tree));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct tree *build_tree(int *pre, int *ino, int begin, int end, int *j, struct tree *root)
{
    if (begin == end)
    {
        return NULL;
    }

    int preIndex = pre[(*j)];
    int inIndex = 0;
    int count = 0;
    for (int i = begin; i < end; i++)
    {
        if (ino[i] == preIndex)
        {
            count++;
            int inIndex = i;
            break;
        }
    }
    if (count == 0)
    {
        return NULL;
    }
    else
        (*j)++;

    struct tree *new = create(preIndex);
    if (root == NULL)
    {
        root = new;
    }
    root->left = build_tree(pre, ino, begin, inIndex, j, root->left);
    root->right = build_tree(pre, ino, inIndex, end, j, root->right);

    return root;
}

void inorderTraversal(struct tree *root)
{
    if (root == NULL)
    {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
int main()
{
    int preorder[] = {1, 2, 4, 3, 5, 7, 8, 6};
    int inorder[] = {4, 2, 1, 7, 5, 8, 3, 6};
    int size = sizeof(inorder) / sizeof(int);
    struct tree *root = NULL;
    int j = 0;
    root = build_tree(preorder, inorder, 0, size, &j, root);
    inorderTraversal(root);
    return 0;
}
