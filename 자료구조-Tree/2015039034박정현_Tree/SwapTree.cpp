
#include<IOStream>
#define true 1
#define false 0

typedef struct TreeNode
{
    int data;
    TreeNode *lNode;
    TreeNode *rNode;
}TreeNode;

void swap(TreeNode *root)
{

    if (root)
    {
        swap(root->lNode);
        swap(root->rNode);
        TreeNode *tmp = root->lNode;
        root->lNode = root->rNode;
        root->rNode = tmp;
    }
}

void inorder(TreeNode *root)
{
    if (root)
    {
        inorder(root->lNode);
        printf("%d ", root->data);
        inorder(root->rNode);
    }
}

void main()
{
	TreeNode n1 = { 7, NULL, NULL};
	TreeNode n2 = { 6, NULL, NULL};
	TreeNode n3 = { 5, NULL, NULL};
	TreeNode n4 = { 4, NULL, NULL};
	TreeNode n5 = { 3, &n2, &n1};
	TreeNode n6 = { 2, &n4, &n3};
	TreeNode n7 = { 1, &n6, &n5};

	TreeNode *root = &n7;

	n4.rNode = &n6;
	n3.rNode = &n7;
	n2.rNode = &n5;

    swap(root);

}