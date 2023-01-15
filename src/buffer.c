/* A circular char buffer implementation. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> // TODO delete me when no longer using printf.

/* Create a circular char buffer of a given size.*/
int* ccbuf_create(size_t size) {
    int* ccbuf = malloc(size * sizeof(char));

    // exit if malloc failed.
    if (!ccbuf) { exit(EXIT_FAILURE); }

    // Initialize the buffer.
    for (size_t i = 0; i < size; i++) { ccbuf[i] = '\0'; }
    return ccbuf;
} 

static size_t start = 0;
static size_t end   = 0;
static int    size  = 3;


/* Put a character onto the buffer. */
void ccbuf_put(int* ccbuf, char c) {
    ccbuf[end] = c;
    end++;
    end %= size;
    return;
}

/* Get a character from the circular char buffer.*/
char ccbuf_get(int* ccbuf) {
    char c = ccbuf[start];
    ccbuf[start] = '\0';
    
    start++;
    start %= size;
    return c;
}

/* Print a circular char buffer to stdout. */
void ccbuf_print(int* ccbuf, size_t size) {
    for (size_t i = 0; i < size; i++)
        { printf("%c", ccbuf_get(ccbuf));}
    printf("\n");
}

int main(void) {
    int* ccbuf = ccbuf_create(size);
    ccbuf_put(ccbuf, '7');
    ccbuf_put(ccbuf, '7');
    ccbuf_put(ccbuf, '9');

    ccbuf_print(ccbuf, size);
    return 0;
}