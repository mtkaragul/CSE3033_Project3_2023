#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

#define MAX_THREADS 32

long long int a, b;
int c, d;
double global_sqrt_sum = 0.0;
pthread_mutex_t mutex;

void* method1_thread(void* arg) {
    long long int start = *(long long int*)arg;
    long long int chunk_size = (b - a + 1) / c; // Divide the range equally among threads

    // Calculate the local sum for the thread's assigned range
    double local_sqrt_sum = 0.0;
    long long int x;
    for (x = start; x <= start + chunk_size; x++) {
        global_sqrt_sum += sqrt(x);
    }

    return NULL;
}

void* method2_thread(void* arg) {
    long long int start = *(long long int*)arg;
    long long int chunk_size = (b - a + 1) / c; // Divide the range equally among threads

    // Calculate the local sum for the thread's assigned range
    double local_sqrt_sum = 0.0;
    long long int x;
    for (x = start; x <= start + chunk_size; x++) {
        // Acquire the mutex before updating global_sqrt_sum
    pthread_mutex_lock(&mutex);
    global_sqrt_sum += sqrt(x);
    pthread_mutex_unlock(&mutex); // Release the mutex
    }
    
    return NULL;
}

void* method3_thread(void* arg) {
    long long int start = *(long long int*)arg;
    long long int chunk_size = (b - a + 1) / c; // Divide the range equally among threads

    // Calculate the local sum for the thread's assigned range
    double local_sqrt_sum = 0.0;
    long long int x;
    for (x = start; x <= start + chunk_size; x++) {
        local_sqrt_sum += sqrt(x);
    }

    // Acquire the mutex before updating global_sqrt_sum
    pthread_mutex_lock(&mutex);
    global_sqrt_sum += local_sqrt_sum;
    pthread_mutex_unlock(&mutex); // Release the mutex

    return NULL;
}

void run_threads(int num_threads, void* (*thread_func)(void*)) {
    pthread_t threads[MAX_THREADS];
    long long int thread_starts[MAX_THREADS];

    // Create and run threads
    for (int i = 0; i < num_threads; i++) {
        thread_starts[i] = a + (i * ((b - a + 1) / num_threads));
        
        if (pthread_create(&threads[i], NULL, thread_func, &thread_starts[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <a> <b> <c> <d>\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = atoll(argv[1]);
    b = atoll(argv[2]);
    c = atoi(argv[3]);
    d = atoi(argv[4]);

    pthread_mutex_init(&mutex, NULL);

    switch (d) {
        case 1:
            run_threads(c, method1_thread);
            break;
        case 2:
            run_threads(c, method2_thread);
            break;
        case 3:
            run_threads(c, method3_thread);
            break;
        default:
            fprintf(stderr, "Invalid value for d\n");
            return EXIT_FAILURE;
    }

    printf("Sum: %e\n", global_sqrt_sum);

    // Additional: Print information about CPU cores
    printf("CPU Core Information:\n");
    system("lscpu");

    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
