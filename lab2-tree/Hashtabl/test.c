#include "hashtabl.h"

#define SIZE 2

int main (void)
{
	int i;
	struct listnode *node;
	
	hashtab_init(hashtab);
	
	//FILE
	
	FILE *file = fopen("dictionary.txt", "r");	

	char words[SIZE][40];
	for (i = 0; i < SIZE; i++) {
		fscanf(file, "%s", words[i]);
		hashtab_add(hashtab, words[i], i);		
	}

	fclose(file);

	//LOOKUP
	
	node = hashtab_lookup(hashtab, "1000");
	printf("Node: %s, %d\n", node->key, node->value+1);

	return 0;
}