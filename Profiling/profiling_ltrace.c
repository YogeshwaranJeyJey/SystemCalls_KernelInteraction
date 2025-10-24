#include <stdio.h>
#include <stdlib.h>
 
int main() {
    printf("Hello, World! %d\n", 5);
    int *arr = malloc(5 * sizeof(int));
    free(arr);
    return 0;
}
