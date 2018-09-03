#include "hashtabl.h"

unsigned int hashtab_hash(char *key)
{
	unsigned int hash = 0;
	char *x; 

	for (x = key; *x != '\0'; x++){
		hash = hash*73+(int)*x;
	}
	return hash % SIZE;
}


// unsigned int hashtab_hash(char *key)
// {;
//     unsigned int hash = 0;
//     // int i;
// 	char *x;

//     for (x = key; *x != '\0'; x++)
//     {
//         hash += (unsigned int)(*x);
//     }

//     return hash % SIZE;
// }

// При начальной инициализации присваиваем значения NULL;
void hashtab_init(struct listnode **hashtab)
{
	for (int i = 0; i < SIZE; i++) {
		hashtab[i] = NULL;
	}
}

void hashtab_add(struct listnode **hashtab, char *key, int value)
{
	struct listnode *node = malloc(sizeof(*node));
	// Ключ - это ячейка элемента (индекс) в таблице (список).
	unsigned int index = hashtab_hash(key);

	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
		if (node->next != NULL) {
			amount++;
		}
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
	struct listnode *node = malloc(sizeof(*node));
	int index = hashtab_hash(key);

	for (node = hashtab[index]; node != NULL; node = node->next) {
		if (strcmp(node->key, key) == 0) {
			return node;
		}
	}
	// printf("search err\n");
	return NULL;
}
