#include<stdio.h>
#include<malloc.h>

/*
	@since 2021-12-26
	@author baoluo
*/
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
}Node;

Node* findNode(Node *n, int data);
void leftAdd(Node **left, Node **right, int data);
void rightAdd(Node **left, Node **right, int data);
void deleteNode(Node **left, Node **right, int data);
void printRightNode(Node *n);
void printLeftNode(Node *n);

void leftAdd(Node **left, Node **right, int data){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->left = temp->right = NULL;
	if(*left == NULL && *right == NULL){ // if n is null
		*left = *right = temp;
	}else{ // if n is not null
		temp->right = *left; // temp -> node
		(*left)->left = temp;
		*left = temp; // node -> temp
	}
}

void rightAdd(Node **left, Node **right, int data){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->left = temp->right = NULL;
	if(*left == NULL && *right == NULL){ // if n is null
		*left = *right = temp;
	}else{ // if n is not null
		temp->left = *right; // temp -> node
		(*right)->right = temp; // node -> temp
		*right = temp;
	}
}

Node* findNode(Node *n, int data){ // return find node memory address
	while(n){
		if(n->data == data)
			return n;
		if(n == NULL)
			return n;
		n = n->right;
	}
	return NULL;
}
void deleteNode(Node **left, Node** right, int data){
	// if data is exist first node
	Node *tempLeftNode = *left;
	Node *tempRightNode = *right;
	Node *removeNode = findNode(tempLeftNode, data);
	if(removeNode == NULL){ // if node address is null.. could not find node
		 	printf("could not find node...");
		 	return;
	}
	if(tempLeftNode == removeNode){ // if find node memory address same first node
		*left = (*left)->right; // move next node
		free(tempLeftNode); 
	}else{
		 while(tempLeftNode){
		 	if(tempLeftNode->right == removeNode)
		 		break;
		 	tempLeftNode = tempLeftNode->right;
		 }
		 
		 tempLeftNode->right = removeNode->right;
		 free(removeNode);
	}
	
}

void printRightNode(Node *n){
	int i;
	while(n){
		printf("%d ", n->data);
		n = n->right;
	}
	printf("\n");
}
void printLeftNode(Node *n){
	int i;
	while(n){
		printf("%d ", n->data);
		n = n->left;
	}
	printf("\n");
}


int main()
{
	Node *left = NULL;
	Node *right = NULL;
	int i;
	
	
	
	for(i = 0 ; i < 5 ; i++){
		 leftAdd(&left, &right, (i+1)); // add n [ 1, 2, 3, 4, 5 ]
	}
	printf("left add..\n");
	printRightNode(left);
	for(i = 0 ; i < 5; i++){
		rightAdd(&left, &right, (6+i));
	}
	printf("right add..\n");
	printRightNode(left);
	
	printf("print reverse use right node...\n");
	printLeftNode(right);	

	printf("remove 5 node\n");
	deleteNode(&left, &right, 5); // remove first node
	printRightNode(left);
	printf("remove 3 node\n");
	deleteNode(&left, &right, 3); // remove middle node
	printRightNode(left);
}
