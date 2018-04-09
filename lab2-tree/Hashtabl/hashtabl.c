#include "hashtabl.h"

unsigned int hashtab_hash(char *key)
{
	unsigned int hash = 0;
	char *x; 

	/*x = key;
    for (int i = 0; i < strlen(key); i++) { 
        hash ^= x[i]; 
    }
	return hash;*/ 

	for (x = key; *x != '\0'; x++){
		hash = hash*SIZE+(int)*x;
	}
	return hash % 73;
}

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
	int index = hashtab_hash(key);

	/*if (node->next != 0) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
		amount++;
	} else {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}*/

	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
		if (node->next != NULL) {
			amount++;
		}
	}

	/*int amount = 0;
	if (node != NULL) {  // Проверка на здравый смысл.
		node->key = key;
		node->value = value;
		if (node->next != NULL) {
			node->next = hashtab[index];
			node->prev = NULL;
			hashtab[index] = node;
			amount++;
			printf("%d\n", amount);
		} else {
			node->next = hashtab[index];
			hashtab[index] = node;
			node->prev = NULL;
		}
	}*/
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
	printf("Ошибочка вышла !\n");
	return NULL;
}

/*void hashtab_delete(struct listnode **hashtab, char *key)
{
	int index = hashtab_hash(key);
	struct listnode *x;

	for (x = hashtab[index]; x != NULL; x = x->next) {
		if (strcmp(x->key, key) == 0) {
			if(hashtab->prev == NULL) {
				hashtab[index] = x->prev;
			}
			else {
				prev->next = x->next;
			}
			free(x);
			return;
		}
		*prev = x;
	}
}*/