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
struct node {
	int val;
	struct node *left, *right;
};

/*
 * Print by the inorder visit* the Tree.         * Inorder visit: before i visit the left child then parent and then the 
 * from the lower to the higher.                 * right child and so on.
*/
void print_inorder(struct node *root) {
	if (root == NULL) {
		return;
	}
	print_inorder(root->left);
	printf("%d ", root->val);
	print_inorder(root->right);
}

/*
 * Return the height of the Node. 
 * leaf have heght -0-, parent of leaf have height = 1, ect...
 * height of the root is the height of the Treee.
*/
int height(struct node *root) {
	if (root == NULL) {
		return -1; // L'altezza di un albero vuoto è -1.
	}
	// Restituisce l'altezza del sottoalbero più alto + 1 (per il nodo corrente).
	int left_height = height(root->left);
	int right_height = height(root->right);
	return (left_height > right_height ? left_height : right_height) + 1;
}

/*
 * I create space in the memory -size of(strunct node*)-
 * If the new node is smaller than root AND root hasn't a left child then it  replace the left leaf with the new node;
 * else i continue to compare the new node with the root.
 * if the new node is bigger than root AND root hasn't a left child then it will replace with the new node.
 * Root will be upgrade every time with the new node.
*/
struct node *add(struct node *root, int val) {
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL) {
		printf("<ERROR> Memory allocation error.\n");
		exit(1);
	}
	new_node->val = val;
	new_node->left = new_node->right = NULL;

	if (root == NULL) {
		return new_node;
	}

	struct node *current = root;
	while (1) {
		if (val < current->val) {
			if (current->left == NULL) {
				current->left = new_node;
				return root;
			}
			current = current->left;
		} else {
			if (current->right == NULL) {
				current->right = new_node;
				return root;
			}
			current = current->right;
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
 * If node == NULL return
 * Write in the tree.dot, the binary tree in text format
 * I found this algorithm on YouTube (https://www.youtube.com/watch?v=R-RtvJKffq0&t=8s)
 */
void print_rec(FILE *file, struct node *node) {
	// Caso base: se il nodo è NULL, torna indietro.
	if (node == NULL) {
		return;
	}

	fprintf(file, "  A%p[label=\"%d\"]\n", (void*)node, node->val);

	if (node->left != NULL) {
		fprintf(file, "  A%p -> A%p\n", (void*)node, (void*)node->left);
		print_rec(file, node->left);
	}

	if (node->right != NULL) {
		fprintf(file, "  A%p -> A%p\n", (void*)node, (void*)node->right);
		print_rec(file, node->right);
	}
}

/*
 * Create the tree.dot file and the SVG image of the tree.
 */
void print_tree(struct node* root) {
	FILE *file;
	file = fopen("./tree.dot", "w");
	if (!file) {
		printf("ERRORE, impossibile aprire il file\n");
		return;
	}
	fprintf(file, "digraph G {\n");
	fprintf(file, "  node [shape=circle, fontname=\"Helvetica\", fontsize=12];\n");
	fprintf(file, "  edge [fontname=\"Helvetica\", fontsize=10];\n");
	print_rec(file, root);
	fprintf(file, "}\n");
	fclose(file);
	
	printf("Creating binary Tree in out.svg...\n");
	system("dot -Tsvg tree.dot -o out.svg");
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
void print_tree_t(struct node* root, int space) {
    
    if (root == NULL)
        return;    
    space += 8;  
    print_tree_t(root->right, space);    
    printf("\n");
    for (int i = 8; i < space; i++)
        printf(" ");
    printf("%3d\n", root->val);

    print_tree_t(root->left, space);
}

int main(void) {
	struct node *root = NULL;

	root = add(root, 100);
	add(root, 50);
	add(root, 200);
	add(root, 150);
	add(root, 330);
	add(root, 80);
	add(root, 20);
	add(root, 60);
	add(root, 333);
	add(root, 500);
	add(root, 12);
	add(root, 58);

	printf("Visita in-order: ");
	print_inorder(root);
	printf("\n\n");
	
	print_tree_t(root, 0);
	print_tree(root);
	free_tree(root);
	return 0;
}

