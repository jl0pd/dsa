#ifndef HASHTABL
#define HASHTABL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

struct listnode {
	char *key;
	int value;
	struct listnode *next;
	struct listnode *prev;
} listnode;

int amount;
struct listnode *hashtab[SIZE];

unsigned int hashtab_hash(char *key);

void hashtab_init(struct listnode **hashtab);

void hashtab_add(struct listnode **hashtab, char *key, int value);

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);

void hashtab_delete(struct listnode **hashtab, char *key);

#endif