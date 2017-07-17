#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int ret[3] = {0, 0, 0};
int v = 0;

void  *thread(void *arg) {
    int i = 0;
    for (; i < 2; i++) {
        printf("thread id = %li\n", *((long *) arg));
    }

    ret[v++] = i;
    pthread_exit((void *) &i);
}

int main() {
    pthread_t t1, t2, t3;
    assert(!pthread_create(&t1, NULL, thread, (void *) &t1));
    assert(!pthread_create(&t2, NULL, thread, (void *) &t2));
    assert(!pthread_create(&t3, NULL, thread, (void *) &t3));

    int *x, *y, *z;
    pthread_join(t1, (void *) &x);
    pthread_join(t2, (void *) &y);
    pthread_join(t3, (void *) &z);

//    pthread_join(t1, NULL);
//    pthread_join(t2, NULL);
//    pthread_join(t3, NULL);

    printf("%d, %d, %d\n", *x, *y, *z);
    printf("%d, %d, %d\n", ret[0], ret[1], ret[2]);

    return 0;
}