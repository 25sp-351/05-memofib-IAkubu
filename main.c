#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMOIZED 100
#define NO_VALUE_YET -1LL 

// Function pointer type
typedef long long (*long_long_func_ptr)(int param);

// Function pointer for caching Fibonacci
long_long_func_ptr fibonacci_provider;

// Cache array
long long memo[MAX_MEMOIZED + 1];

// Fibonacci function
long long fibonacci(int n) {
    // Base cases
    if (n < 2) return n;

    // Compute and store in cache
    memo[n] = (*fibonacci_provider)(n - 1) + (*fibonacci_provider)(n - 2);
    return memo[n];
}

// Cache function
long long cache_func(int n) {
    // Check if it's in the cache
    if (n < 0 || n > MAX_MEMOIZED) {
        return fibonacci(n); // Compute directly if out of range
    }

    if (memo[n] == NO_VALUE_YET) {
        memo[n] = fibonacci(n); // Compute and cache it
    }

    return memo[n]; // Return cached value
}

// Initialize the cache
long_long_func_ptr init_cache(long_long_func_ptr fibonacci_calculator) {
    for (int i = 0; i <= MAX_MEMOIZED; i++) {
        memo[i] = NO_VALUE_YET; // Initialize cache
    }

    return cache_func;
}

// Main function
int main(int argc, char *argv[]) {
    int input;

    if (argc < 2 || sscanf(argv[1], "%d", &input) != 1 || input < 0) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    // Initialize cache
    fibonacci_provider = init_cache(fibonacci);

    // Compute Fibonacci numbers
    for (int i = 0; i <= input; i++) {
        if (i == input) {
          printf("Fibonacci(%d) = %lld\n", i, (*fibonacci_provider)(i));
        }
    }

    return 0;
}
