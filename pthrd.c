#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 10

struct data_p {
	int start;
	int end;
	int *arr;
};

void *find_max1(void *);
void *find_max2(void *);
int *array();

int main() {
    int *arr;
	int *data = array(arr);

	struct data_p *data_1 = (struct data_p *) malloc(sizeof(struct data_p));	
	struct data_p *data_2 = (struct data_p *) malloc(sizeof(struct data_p));
	data_1->start = 0;     	data_1->end = SIZE/2;   data_1->arr = data;
	data_2->start = SIZE/2; data_2->end = SIZE;     data_2->arr = data;
		
	pthread_t t1, t2;
	assert(!pthread_create(&t1, NULL, find_max1, (void *) data_1));
	assert(!pthread_create(&t2, NULL, find_max2, (void *) data_2));

	void **ret1, **ret2;
	pthread_join(t1, ret1);
	pthread_join(t2, ret2);
	printf("ret1 = %d\n", **((int **)ret1)); printf("ret2 = %d\n", **((int **)ret2));

	return 0;
}

void *find_max1(void *arg) {
    printf("1fm\n");
	struct data_p *data = (struct data_p *) arg;
    printf("1data ok\n");
    int i, *max;
    printf("1i = %d de = %d\n", i, data->end);
    *max = 0;
	for (i = data->start; i < data->end-1; i++) {
		if (i < 100) {printf("1i = %d\n", i);}

		if (*max < data->arr[i]) {
            *max = data->arr[i];
        }
	}
	printf("1enf fm\n");
    return max;
}

void *find_max2(void *arg) {
	printf("2fm\n");
	struct data_p *data = (struct data_p *) arg;
	printf("2data ok\n");
	int i, *max;
	printf("2i = %d de = %d\n", i, data->end);
	*max = 0;
	for (i = data->start; i < data->end-1; i++) {
		if (i < 100) {printf("2i = %d\n", i);}

		if (*max < data->arr[i]) {
			*max = data->arr[i];
		}
	}
	printf("2enf fm\n");
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





