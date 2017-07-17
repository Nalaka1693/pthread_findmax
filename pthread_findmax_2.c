#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100000000

typedef struct {
	int start;
	int end;
} info_t;

int *data;

void *find_max(void *);
int *array();

int main() {
    data = array();

	info_t *data_1 = (info_t *) malloc(sizeof(info_t));
	info_t *data_2 = (info_t *) malloc(sizeof(info_t));
	data_1->start = 0;     	data_1->end = SIZE/2;
	data_2->start = SIZE/2; data_2->end = SIZE;

	pthread_t t1, t2;
	assert(!pthread_create(&t1, NULL, find_max, (void *) data_1));
	assert(!pthread_create(&t2, NULL, find_max, (void *) data_2));

	int *ret1, *ret2;
	pthread_join(t1, (void *) &ret1);
	pthread_join(t2, (void *) &ret2);

	printf("ret1 = %d ret2 = %d\n", *ret1, *ret2);
    printf("max = %d\n", (*ret1 < *ret2) ? *ret2 : *ret1);

	return 0;
}

void *find_max(void *arg) {
    int i = ((info_t *) arg)->start;
    int e = ((info_t *) arg)->end;
    int *max = (int *) malloc(sizeof(int)); //var max remain in the heap even after end of func call
    *max = data[i];

	for (; i < e; i++) {
		if (*max < data[i]) {
            *max = data[i];
        }
	}

    pthread_exit((void *) max);
}

int *array() {
    srand(time(NULL));
    long i = 0; int *arr = (int *) malloc(sizeof(int) * SIZE);
    for (; i < SIZE; i++) {
        arr[i] = rand() % (rand());
//        printf("%d, ", arr[i]);
    }
    printf("\n");
    return arr;
}




