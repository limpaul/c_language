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
void add(Node **head, Node **tail, int data);
void deleteNode(Node **head, Node **tail, int data);
void printNode(Node *n);


void add(Node **head, Node **tail,  int data){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = temp; // point to self 
	if(*head == NULL && *tail == NULL){ // if n is null
		*head = *tail = temp;
	}else{ // if n is not null
		temp->next = *head; // temp -> node
		*head = temp; // node -> temp
		(*tail)->next = *head;
	}
}
Node* findNode(Node *n, int data){ // return find node memory address
	Node *temp = n;
	do{
		if(temp->data == data){
			return temp;
		}	
		temp = temp->next;
	}while(n != temp);
	return NULL;
}
Node* beforePointNode(Node *n, int data){
	Node *temp = n;
	do{
		if(temp->next->data == data)
			return temp;
		temp = temp->next;
	}while(temp != n);
	return NULL; // could not find data
}
void deleteNode(Node **head, Node**tail, int data){
	// if data is exist first node
	Node *temp = *head;
	Node *tail_temp = *tail;
	Node *removeNode = findNode(*head, data);
	if(removeNode == NULL){ // if node address is null.. could not find node
		 	printf("could not find node...");
		 	return;
	}
	if(*head == removeNode){ // if find node memory address same start node
		*head = (*head)->next; // move next node
		(*tail)->next = *head;
		free(temp);
		 
	}
	else if(*tail == removeNode){
		Node *before = beforePointNode(tail_temp, data);
		before->next = *head;
		free(*tail);
		*tail = before;
	}
	else{
		Node *before = beforePointNode(temp, data);
		before->next = removeNode->next;
		free(removeNode);
	}
	
}

void printNode(Node *n){
	int i;
	Node *temp = n;
	do{
		printf("%d ", n->data); // start -> next -> next ...
		n = n->next; // ex) 3 -> 2 -> 1 -> 5 -> 4
	}while(n != temp);
	printf("\n");
}

int main()
{
	Node *head = NULL;
	Node *tail = NULL;
	int i;
	for(i = 0 ; i < 5 ; i++){
		add(&head, &tail, (i+1)); // add n [ 1, 2, 3, 4, 5 ]
	}
	printNode(head);
	Node* start3 = findNode(head, 3); // when start head is 3 ...  3 -> 2 -> 1 -> 5 -> 4
	printNode(start3); // start node3 
	deleteNode(&head, &tail, 5); // remove first node
	printNode(head);
	deleteNode(&head, &tail, 3); // remove middle node
	printNode(head);
	deleteNode(&head, &tail, 1); // remove tail node
	printNode(head);
}
