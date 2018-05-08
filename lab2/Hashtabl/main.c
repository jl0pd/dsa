#include "hashtabl.h"
#include <time.h>

int main (void)
{
	int i;
	// struct listnode *node;
	srand (time(NULL));
	double start, stop;
	
	
	//ADD

	hashtab_init(hashtab); // Инициализация самой таблицы.
	
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) return 0;

	char words[SIZE][40];

	start = clock();
	for (i = 0; i < SIZE; i++) {
		fscanf(file, "%s", words[i]);
		hashtab_add(hashtab, words[i], i);
	}
	stop = clock();
	printf("adding time: %.10fsec\n", difftime(stop, start) / CLOCKS_PER_SEC);

	fclose(file);

	//LOOKUP
	
	start = clock();
	
	char *randkey;
	double loctime = 0;

	for (int i = 0; i < SIZE - 1; i++){
		randkey = words[rand() % (SIZE - 0 + 1) + 0];

		hashtab_lookup(hashtab, randkey);
		// node = hashtab_lookup(hashtab, randkey);
		// printf("Node: %s, %d\n", node->key, node->value+1);

		stop = clock();

		loctime += difftime(stop, start);
	}

	printf("average time of %d: %.10fsec\n", SIZE, (loctime / SIZE) / CLOCKS_PER_SEC);

	printf("COLIZE: [%d]\n", SIZE - amount);
	return 0;
}