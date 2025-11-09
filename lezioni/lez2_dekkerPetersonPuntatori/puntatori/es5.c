#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node;

Node* insert_head (Node* head, int n) {
	Node* tmp = malloc(sizeof(Node));
	tmp -> value = n;
	tmp -> next = head;
	return tmp;
}

void print_list(Node* head) {
	while (head->next != NULL) {
		printf("%d -> ",head->value);
		head = head->next;
	}
	printf("%d",head->value);
	printf("\n");
}

void free_list(Node* l) {
	if (l == NULL ) {
		return;
	}
	free_list(l->next);
	free(l);
}

int main () {
	Node * head = NULL;
	head = insert_head(head,1);
	head = insert_head(head,2);
	head = insert_head(head,3);
	head = insert_head(head,4);
	print_list(head);
	free_list(head);
	return 0;
}
