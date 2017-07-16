#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100

struct data_p {
	int start;
	int end;
	int *arr;
};

void *find_max(void *);
int *array();

int main() {
	int *data = array();

	struct data_p *data_1 = (struct data_p *) malloc(sizeof(struct data_p));	
	struct data_p *data_2 = (struct data_p *) malloc(sizeof(struct data_p));
	data_1->start = 0;          data_1->end = SIZE/2; data_1->arr = data;
	data_2->start = SIZE/2 + 1; data_2->end = SIZE; data_2->arr = data;
		
	pthread_t t1, t2;
	assert(!pthread_create(&t1, NULL, find_max, (void *) data_1));
	assert(!pthread_create(&t2, NULL, find_max, (void *) data_2));

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

void *find_max(void *arg) {
	struct data_p *data = (struct data_p *) arg;
    int i = data->start, *max = (int *) malloc(sizeof(int));
    *max = 0;
	for (i < data->end-1; i++;) {
		if (*max < data->arr[i]) {
            *max = data->arr[i];
        }
	}

    return max;
}

int *array(int *arr) {
	int data[SIZE] = {}, i;
	srand(0);
	for (i = 0; i < SIZE; i++) {
		data[i] = rand() % SIZE;
        printf("%d, ", data[i]);
	}
    printf("\n");
	arr = data;
	return arr;
}





