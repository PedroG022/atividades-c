#include <stdio.h>
#include <time.h>
#include <string.h>

// Results struct
typedef struct result {
    int cmp;
    int trc;
    float tme;
} result ;

typedef struct sort_result {
    double time;
    char name[25];
} sort_result ;

// Wheter or not the program
// should print the arrays.
// This option is needed if
// we want to use large
// arrays.
#define OUTPUT_ARRAYS 1

// System clear command
// replace if needed.
#define CLEAR "cls"

// Array display definitions
#define ARRAY_ORIGINAL 0
#define ARRAY_SORTED 1
#define NO_MESSAGE -1

// Algorithms
#define QUICK_SORT 1
#define SHELL_SORT 2
#define MERGE_SORT 3
#define HEAP_SORT 4

// Text separator
// for details
#define SEPARATOR "---------------------------"

// ---------------------------
// Algorithms start
// ---------------------------

// QuickSort
result quickSort(int* vet, int esquerda, int direita) {
    int x = vet[(esquerda+direita)/2];
	int e = esquerda;
	int d = direita;

    result res ;
    res.cmp = 0;
    res.trc = 0;

	int temp;

	while(e <= d) {
		while( vet[e] < x && e < direita) e++;

		while( vet[d] > x && d > esquerda) d--;
		
        res.cmp ++ ;
		if(e <= d) {
            res.trc ++;
            temp = vet[e];
            vet[e] = vet[d];
            vet[d] = temp;
            e++;
            d--;
        }
	}

	if(d > esquerda) {
        //quickSort(vet, esquerda, d);
        result x = quickSort(vet, esquerda, d);
        res.cmp += x.cmp;
        res.trc += x.trc;
    }

    if(e < direita) {
        //quickSort(vet, e, direita);
        result x = quickSort(vet, e, direita);
        res.cmp += x.cmp;
        res.trc += x.trc;
    }

    return res ;
}

// ShellSort
result shellSort(int* array, int array_size) {
	int i, j, h, aux;
	
	for (h = 1; h < array_size ; h = 3 * h + 1); /* h inicial . */

    result res ;
    res.cmp = 0 ;
    res.trc = 0 ;
	
	do {
		h = (h - 1) / 3; /* atualiza h. */
	
		for (i = h ; i < array_size ; i ++) {
			aux = array[i];
			j = i;
			/* Comparações entre elementos com distância h: */
            res.cmp ++ ;
			while (array[j - h] > aux ) {
                res.trc ++ ;
				array[j] = array[j - h];
				j -= h;
				if (j < h) break ;
			}
			array[j] = aux ;
		}
	} while (h != 1);
	
    return res ;
}

// ---------------------------
// MergeSort
// ---------------------------

result merge(int* vet, int p, int q, int r){
	result res ;
    res.cmp = 0 ;
    res.trc = 0 ;
	
	int n1 = q - p + 1;
	int n2 = r - q;
	int v1[n1], v2[n2];
	
	for(int i=0; i<n1; i++) v1[i] = vet[p+i];
	
	for(int j=0; j<n2; j++) v2[j] = vet[q+1+j];
	
	int i=0, j=0, k=p;
		
		while( i<n1 && j<n2) {
			
			res.cmp++;
			
			if (v1[i] <= v2[j]){
				vet[k] = v1[i];
				i++;
			} else {
				res.trc++;
				vet[k] = v2[j];
				j++;
			}
			k++;
		}
		
		while( i < n1) {
			vet[k] = v1[i];
			i++;
			k++;
		}
		
		while( j < n2) {
			vet[k] = v2[j];
			j++;
			k++;
		}
		
		return res;
}

result mergesort( int* vet, int e, int d){
	
	result res_tmp;
	result res;
	res.cmp = 0;
	res.trc = 0;
	
	if(e<d){
		int m = (e + d) / 2;
		res_tmp = mergesort(vet, e, m);
		res.cmp += res_tmp.cmp;
		res.trc += res_tmp.trc;

		res_tmp = mergesort(vet, m+1, d);
		res.cmp += res_tmp.cmp;
		res.trc += res_tmp.trc;
		
		res_tmp = merge(vet, e, m, d);
		res.cmp += res_tmp.cmp;
		res.trc += res_tmp.trc;
	}
	
	return res;
}

// ---------------------------
// HeapSort
// ---------------------------

result heap(int vet[], int n, int i) {
    result res ;

    res.cmp = 0 ;
    res.trc = 0 ;

    int pai = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    res.cmp ++ ;
    if (esquerda < n && vet[esquerda] > vet[pai])
      pai = esquerda;

    res.cmp ++ ;
    if (direita < n && vet[direita] > vet[pai])
      pai = direita;
  
    if (pai != i) {
        res.trc ++ ;
        int temp = vet[i];
        vet[i] = vet[pai];
        vet[pai] = temp;
        result resx = heap(vet, n, pai);
        res.cmp += res.cmp ;
        res.trc += res.trc ;
    }

    return res ;
}

result heapSort(int vet[], int n) {
    result res ;

    res.cmp = 0 ;
    res.trc = 0 ;

    for (int i = n / 2 - 1; i >= 0; i--) {
      result rex = heap(vet, n, i);
      res.cmp += rex.cmp ;
      res.trc += rex.trc ;
    }
      
    for (int i = n - 1; i >= 0; i--) {
        res.trc ++ ;
        int temp = vet[i];
        vet[i] = vet[0];
        vet[0] = temp;
        result rex = heap(vet, i, 0);
        res.cmp += rex.cmp ;
        res.trc += rex.trc ;
    }

    return res ;
}

// ---------------------------
// Algorithms end
// ---------------------------

// Fills an array with random unique numbers
void fillArray(int *array, int array_size, int seed) {
    srand(seed);

    for (int i = 0 ; i < array_size ; i ++ ) {
         int n = 0;
         n = rand() % (array_size * 10) ;
         array[i] = n ;
    }
}

// Shows an array
void showArray(int *array, int arraySize, int messageCode) {
    if (OUTPUT_ARRAYS) {
        if (messageCode == ARRAY_ORIGINAL)
            printf("Array original (%d): ", arraySize);
        else if (messageCode == ARRAY_SORTED)
            printf("Array ordenado (%d): ", arraySize);
        
        for (int i = 0 ; i < arraySize ; i++)
            printf("%d ", array[i]);

        printf("\n");
    }
}

// Shows the result of a sort algorithm
void showResult(result *res, int *array, int *backup, int array_size, char *algorithm_name) {
    printf("Algoritmo: %s\n", algorithm_name);
    showArray(backup, array_size, ARRAY_ORIGINAL);
    printf("Trocas: %d | ", res -> trc);
    printf("Comparacoes: %d | ", res -> cmp);
    printf("Tempo gasto: %f\n", res -> tme);
    showArray(array, array_size, ARRAY_SORTED);
}

// Do all the job regarding the use of the 
// algorithms and the time calculation.
sort_result workWithAlgorithm(int algorithm, int array_size, int seed) {
    struct timespec start, end;

    result res ;
    double time_spent ;
    char algorithm_name[30] ;

    int array[array_size];
    int array_backup[array_size];

    fillArray(array, array_size, seed);
    fillArray(array_backup, array_size, seed);

    switch (algorithm)
    {
        case QUICK_SORT:
            strcpy(algorithm_name, "Quick Sort");
            clock_gettime(CLOCK_REALTIME, &start);
            res = quickSort(array, 0, array_size - 1);
            clock_gettime(CLOCK_REALTIME, &end);
        
            time_spent = (end.tv_sec - start.tv_sec) +
                                (end.tv_nsec - start.tv_nsec) / 1e8;
            break;

        case SHELL_SORT:
            strcpy(algorithm_name, "Shell Sort");
            clock_gettime(CLOCK_REALTIME, &start);
            res = shellSort(array, array_size);
            clock_gettime(CLOCK_REALTIME, &end);
        
            time_spent = (end.tv_sec - start.tv_sec) +
                                (end.tv_nsec - start.tv_nsec) / 1e8;
            break;

        case HEAP_SORT:
            strcpy(algorithm_name, "Heap Sort");
            clock_gettime(CLOCK_REALTIME, &start);
            res = heapSort(array, array_size);
            clock_gettime(CLOCK_REALTIME, &end);
        
            time_spent = (end.tv_sec - start.tv_sec) +
                                (end.tv_nsec - start.tv_nsec) / 1e8;
            break;
            
         case MERGE_SORT:
            strcpy(algorithm_name, "Merge Sort");
            clock_gettime(CLOCK_REALTIME, &start);
            res = mergesort(array, 0, array_size-1);
            clock_gettime(CLOCK_REALTIME, &end);
        
            time_spent = (end.tv_sec - start.tv_sec) +
                                (end.tv_nsec - start.tv_nsec) / 1e8;
            break;

        default:
            break;
    }

    res.tme = time_spent ;

    showResult(&res, array, array_backup, array_size, algorithm_name);
    fillArray(array, array_size, seed);
    printf("%s\n", SEPARATOR);

    sort_result sr ;
    strcpy(sr.name, algorithm_name);
    sr.time = res.tme ;

    return sr ;
}

int main() {
    int array_size ;

    system(CLEAR);

    if (!OUTPUT_ARRAYS)
        printf("Os arrays nao vao ser exibidos!\n");

    int seed = time(NULL);

    do {
        printf("Insira o tamanho desejado do array entre 10 e 100000: ");
        scanf("%d", &array_size);
    } while (!(array_size >= 10 && array_size <= 100000));
    
    sort_result quick = workWithAlgorithm(QUICK_SORT, array_size, seed);
    sort_result shell = workWithAlgorithm(SHELL_SORT, array_size, seed);
    sort_result heap = workWithAlgorithm(HEAP_SORT, array_size, seed);
    sort_result merge = workWithAlgorithm(MERGE_SORT, array_size, seed);

    sort_result results[4] = {quick, shell, heap, merge} ;

    for (int i = 0 ; i < 4 ; i ++ ) {
        if (results[0].time > results[i].time) {
            sort_result temp = results[0];
            results[0] = results[i];
            results[i] = temp ;
        }
    }

    if (results[0].time == results[1].time)
        printf("Houve um empate entre os algoritmos %s e %s, ambos com um tempo de %fs.", results[0].name, results[1].name, results[0].time);
    else
        printf("O algoritmo %s foi o melhor algoritmo em funcao do tempo, com um tempo total de %fs.", results -> name, results[0].time);

    return 0 ;
}