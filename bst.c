/*
 * Primitive struct of a Node; A simple print then print the Tree on the terminal, and the inorder visit
 * Is was created just for practice writing some basic node and tree algorithms for university course(Data and Algorithms).
*/
#include <stdio.h>
#include <stdlib.h>

/*
 * Define the struct of Node 
 * 
 *          node   ---> if it is the first added node it is the root 
 *          /  \
 *         rx  lx  ---> if all the child of a node are NULL it means than the node 
 *         /\  /\       is a leaf.
*/
struct node{
	int val;
	struct node *left, *right;
};


/*
 * Print by the inorder visit* the Tree.         * Inorder visit: before i visit the left child then parent and then the 
 * from the lower to the higher.                 * right child and so on.
*/
void print_inorder(struct node *root){
	if(root == NULL) return;
	if(root->left != NULL) print_inorder(root->left);
	printf("%d ", root->val);
	if(root->right != NULL) print_inorder(root->right);
}

/*
 * Return the height of the Node. 
 * leaf have heght -0-, parent of leaf have height = 1, ect...
 * height of the root is the height of the Treee.
*/
int height(struct node *root){
	if(root == NULL) return 0;
	return (height(root->left) > height(root->right) ?
		height(root->left) : height(root->right)) + 1;
}

/*
 * I create space in the memory -size of(strunct node*)-
 * If the new node is smaller than root AND root hasn't a left child then it  replace the left leaf with the new node;
 * else i continue to compare the new node with the root.
 * if the new node is bigger than root AND root hasn't a left child then it will replace with the new node.
 * Root will be upgrade every time with the new node.
*/
struct node *add(struct node *root, int val){
	struct node *saved_root = root; 
	struct node *new = malloc(sizeof(*new));
	if(new == NULL){ 
		printf("Erore allocazione memoria\n");
		exit(1);	
	}
	new->val = val;
	new->left = new->right = NULL;
	while(1){
		if(root == NULL) return new;
		if(val < root->val){
			if(root->left == NULL){
				root->left = new; 
				return saved_root; 
			}
			root = root->left;
		}else{
			if(root->right == NULL){ 
				root->right = new; 	
				return saved_root;
			}
			root = root->right;
		}
	}

}
/*
 * functoin to free the memory.
 * this prevent memory leaks deallocating all the memory
 * of the nodes
*/
void free_tree(struct node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/*
 * I can print whatever subTrees I want,
 * 1.  by recursive call I can arrive on the node in the right of the 
 *  Tree, then i pritn it.
 * 2. Continue to do it with the parent and then with the left child.
 * 3. and so on, until I approach to the root.
 * every time i dont find the leaf i increment 8 on the space; I can edit 
 * the space if I want a larger of Smaller Tree. 
*/
void print_tree(struct node* root, int space) {
    
    if (root == NULL)
        return;    
    space += 8;  
    print_tree(root->right, space);    
    printf("\n");
    for (int i = 8; i < space; i++)
        printf(" ");
    printf("%3d\n", root->val);

    print_tree(root->left, space);
}

int main(void){
	struct node *root = NULL;
	struct node *node = NULL;
	
	root = add(root, 100);
	node = add(root, 50);
	node = add(root, 200);
	node = add(root, 150);
	node = add(root, 330);
	node = add(root, 80);
	node = add(root, 20);
	node = add(root, 60);
	node = add(root, 333);
	node = add(root, 500);
	node = add(root, 12);
	node = add(root, 58);

	print_inorder(root); printf("\n");
	print_tree(root, 0);
	return 0;
}
