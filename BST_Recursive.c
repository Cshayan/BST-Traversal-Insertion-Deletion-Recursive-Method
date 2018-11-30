#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *left;
    int data;
    struct node *right;
};
struct node* insert(struct node *node,int item)
{
    if(node == NULL)
    {
        node=(struct node*)malloc(sizeof(struct node));
        node->data=item;
        node->left=NULL;
        node->right=NULL;
        return node;
    }
    else if(item < node->data)
    {
        node->left= insert(node->left,item);
        return node;
    }
    else if(item > node->data)
    {
        node->right= insert(node->right,item);
        return node;
    }
    else
    {
        printf("\nDuplicate values not allowed\n");
        exit(0);
    }
}
void preorder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d\t",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \t", root->data);
        inorder(root->right);
    }
}
void postorder(struct node *root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\t",root->data);
    }
}
struct node *search(struct node *node,int item)
{
  if(node == NULL || node->data == item)
        return node;
  else if(item < node->data)
        return search(node->left, item);
  else
        return search(node->right, item);
}
struct node *minNodeVal(struct node *temp)
{
   struct node *curr=temp;
   while(curr->left!=NULL)
        curr=curr->left;

   return curr;
}

struct node *delNode(struct node *node, int item)
{
    if(node==NULL)
    {
        return node;
    }
     //go to left if value to be deleted is less than root
    if(item < node->data)
    {
        node->left= delNode(node->left, item);
    }
    // go to right if value to be deleted is more than root
    else if(item > node->data)
    {
        node->right= delNode(node->right, item);
    }
    // when the value to be deleted is found
    else
    {
        //when the node has no child or only one child
        if(node->left==NULL)
        {
            struct node *temp=node->right;
            free(node);
            return temp;
        }
        else if(node->right==NULL)
        {
            struct node *temp=node->left;
            free(node);
            return temp;
        }

         //when the node has two child, find the min value in its right subtree and store it in temp
        struct node *temp=minNodeVal(node->right);
        //copy the minimum value in node to be returned
        node->data=temp->data;
        //delete the in-order successor or minimum value form right subtree
        node->right=delNode(node->right,temp->data);
    }
    return node;
}
int height(struct node *root)
{
    if(root==NULL)
        return -1;
    if(root->left == NULL && root->right == NULL)
        return 0;

    int leftHeight= height(root->left);
    int rightHeight=height(root->right);

    if(leftHeight<rightHeight)
        return (rightHeight + 1);
    else
        return (leftHeight + 1);
}
int main()
{
    int tot;
    struct node *root=NULL;
    printf("\nEnter the total no of nodes to be inserted in BST:- ");
    scanf("%d",&tot);
    int i,item;
    printf("\nEnter the elements:-\n");
    for(i=0;i<tot;i++)
    {
        scanf("%d",&item);
        root=insert(root,item);
    }
    printf("\nThe In-order Traversal is:-\n");
    inorder(root);
    printf("\nThe Pre-order Traversal is:-\n");
    preorder(root);
    printf("\nThe Post-order Traversal is:-\n");
    postorder(root);

    printf("\nEnter a value to be searched in the tree:- ");
    scanf("%d",&item);
    if(search(root, item) != NULL)
    {
        printf("\nValue found in the tree\n");
    }
    else
    {
        printf("\nValue is not present in the list\n");
    }
    printf("\nThe height of the tree:- ");
    printf("%d",height(root));

    printf("\nEnter the number of nodes to delete:- ");
    scanf("%d",&tot);

    for(i=0;i<tot;i++)
    {
        printf("\nEnter the element:- \n");
        printf("\n");
        scanf("%d",&item);
        root=delNode(root,item);
        printf("\nAfter deletion in-order traversal:-\n");
        inorder(root);
    }


    return 0;
}
