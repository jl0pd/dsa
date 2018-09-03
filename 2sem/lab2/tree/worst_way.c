#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

int main(){
	FILE *f = fopen("worst_way.txt", "wb+");
	for (unsigned int i = 50000; i > 0; i--){
		fprintf(f,"%u\n", i);
	}
	fclose(f);

	srand(time(NULL));

	FILE *s = fopen("aver_way.txt", "w+");
	for (int i = 50000; i > 0; i--){
		fprintf(f,"%d\n", rand() % INT_MAX);
	}
	fclose(f);


}
