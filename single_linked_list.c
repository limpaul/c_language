#include<stdio.h>
#include<malloc.h>

/*
	@since 2021-12-26
	@author baoluo
*/
typedef struct node{
	int data;
	struct node *next;
}Node;

Node* findNode(Node *n, int data);
void add(Node **n, int data);
void deleteNode(Node **n, int data);
void printNode(Node *n);


void add(Node **n, int data){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	if(*n == NULL){ // if n is null
		*n = temp;
	}else{ // if n is not null
		temp->next = *n; // temp -> node
		*n = temp; // node -> temp
	}
}
Node* findNode(Node *n, int data){ // return find node memory address
	while(n){
		if(n->data == data)
			return n;
		if(n == NULL)
			return n;
		n = n->next;
	}
	return NULL;
}
void deleteNode(Node **n, int data){
	// if data is exist first node
	Node *temp = *n;
	Node *removeNode = findNode(*n, data);
	if(removeNode == NULL){ // if node address is null.. could not find node
		 	printf("could not find node...");
		 	return;
	}
	if(temp == removeNode){ // if find node memory address same first node
		*n = (*n)->next; // move next node
		free(temp); 
	}else{
		 while(temp){
		 	if(temp->next == removeNode)
		 		break;
		 	temp = temp->next;
		 }
		 
		 temp->next = removeNode->next;
		 free(removeNode);
	}
	
}

void printNode(Node *n){
	int i;
	while(n){
		printf("%d ", n->data);
		n = n->next;
	}
	printf("\n");
}

int main()
{
	Node *n = NULL;
	int i;
	for(i = 0 ; i < 5 ; i++){
		add(&n, (i+1)); // add n [ 1, 2, 3, 4, 5 ]
	}
	printNode(n);
	deleteNode(&n, 5); // remove first node
	printNode(n);
	deleteNode(&n, 3); // remove middle node
	printNode(n);
}
