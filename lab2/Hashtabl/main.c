#include "hashtabl.h"
#include <time.h>

int main (void)
{
	int i;
	struct listnode *node;
	srand (time(NULL));
	double start, stop;
	
	
	//ADD

	hashtab_init(hashtab); // Инициализация самой таблицы.
	
	FILE *file = fopen("dictionary.txt", "r");	

	char words[SIZE][40];
	for (i = 0; i < SIZE; i++) {
		fscanf(file, "%s", words[i]);
		hashtab_add(hashtab, words[i], i);
	}
	fclose(file);
	//printf("COLIZE: [%d]\n", amount);

		
	//LOOKUP
	
	start = clock();
	
	node = hashtab_lookup(hashtab, "вырезалась");
	printf("Node: %s, %d\n", node->key, node->value+1);

	stop = clock();
	printf("Time: %.10fsec\n", (stop - start) / CLOCKS_PER_SEC);

	//DELETE

	/*hashtab_delete(hashtab, "adieux"); // удаление.

	node = hashtab_lookup(hashtab, "adieux"); // Проверка (можно удалить).
	if (node != NULL) {
		printf("Node: %s, %d\n", node->key, node->value);
	} else {
		printf("Успешное удаление.\n");
	}*/
	printf("COLIZE: [%d]\n", SIZE - amount);
	return 0;
}