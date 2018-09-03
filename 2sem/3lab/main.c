#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 long long main()
{
    srand(time(NULL));

    unsigned long long size;
    printf("Enter size: ");
    scanf("%llu", &size);
    putchar('\n');

    int **pathes = malloc(sizeof(int*) * size);
    for (unsigned long long ijk = 0; ijk < size; ijk++){
        pathes[ijk] = malloc(sizeof(int) * size);
    }

    //  int pathes[size][size]; // матрица связей
     int min_leng[size]; // минимальное расстояние
     int passed[size]; // посещенные вершины
     int temp;
     int minindex, min;

    // Инициализация матрицы связей
    for ( int i = 0; i<size; i++){
        pathes[i][i] = 0;
        for ( int j = i + 1; j<size; j++) {
            // temp = 0;
            temp = rand() % 50 + rand() % 40;
            // for ( int ijk = 0; ijk < 99; ijk++){
                // temp += rand() % 2;
            // }
            // temp = (getchar() - '0');
            pathes[i][j] = temp;
            pathes[j][i] = temp;
        }
    }

    // Вывод матрицы связей
    // for ( int i = 0; i<size; i++){
    //     for ( int j = 0; j<size; j++){
    //         printf("\x1b[%d;1m%2lld\x1b[0m ", i == j ? 32 : 0, pathes[i][j]);
    //     }
        
    //     printf("\n");
    // }

    //Инициализация вершин и расстояний
    for ( int i = 0; i<size; i++){
        min_leng[i] = 10000;
        passed[i] = 1;
    }

    double time_start = clock();
    min_leng[0] = 0;
    // printf("dowhile\n");
    // Шаг алгоритма
    do {
        minindex = 10000;
        min = 10000;
        for ( int i = 0; i<size; i++){ // Если вершину ещё не обошли и вес меньше min
            if ((passed[i] == 1) && (min_leng[i]<min)){ // Переприсваиваем значения
                min = min_leng[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000){
            for ( int i = 0; i<size; i++){
                if (pathes[minindex][i] > 0){
                    temp = min + pathes[minindex][i];
                    if (temp < min_leng[i]){
                        min_leng[i] = temp;
                    }
                }
            }
            passed[minindex] = 0;
        }
    } while (minindex < 10000);
    double time_end = clock();

    printf("\n\ntime: %fs \n\n", (time_end-time_start) / CLOCKS_PER_SEC);


    // // Вывод кратчайших расстояний до вершин
    // printf("\nКратчайшие расстояния до вершин: \n");
    // for ( int i = 0; i<size; i++){
    //     printf("%2d:\t%2d\n", i + 1, min_leng[i]);
    // }

    // printf("\nВывод кратчайшего пути\n");

    // for ( int ijk = 1; ijk <= size; ijk++){
    // // Восстановление пути
    //      int ver[size]; // массив посещенных вершин
    //      int end = ijk - 1; // индекс конечной вершины
    //     ver[0] = end + 1; // начальный элемент - конечная вершина
    //      int k = 1; // индекс предыдущей вершины
    //      int weight = min_leng[end]; // вес конечной вершины

    //     while (end > 0){ // пока не дошли до начальной вершины
    //         for( int i=0; i<size; i++){ // просматриваем все вершины
    //             if (pathes[end][i] != 0){   // если связь есть
                
    //                  int temp = weight - pathes[end][i]; // определяем вес пути из предыдущей вершины
    //                 if (temp == min_leng[i]){ // если вес совпал с рассчитанным
    //                                 // значит из этой вершины и был переход
    //                     weight = temp; // сохраняем новый вес
    //                     end = i;       // сохраняем предыдущую вершину
    //                     ver[k] = i + 1; // и записываем ее в массив
    //                     k++;
    //                 }
    //             }
    //         }
    //     }
    //     // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
        
    //     printf("%2d:\t", ijk);
    //     putchar('-');
    //     for ( int i = k-1; i>=0; i--){
    //         printf("%d-", ver[i]);
    //     }
    //     putchar('\n');
    // }
    return 0;
}
