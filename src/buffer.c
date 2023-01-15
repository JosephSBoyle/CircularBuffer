/* A circular char buffer implementation. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> // TODO delete me when no longer using printf.


/* A fixed-size buffer of characters.*/
typedef struct CharacterBuffer {
    char*  buffer;
    size_t head;
    size_t tail;
    size_t length;    
} CharacterBuffer;


/* Create a circular char buffer of a given size.*/
CharacterBuffer* cbuf_create(size_t length) {
    char*            buffer      = malloc(sizeof(char) * length);
    CharacterBuffer* char_buffer = malloc(sizeof(CharacterBuffer));
    
    // exit if either malloc failed.
    if (!buffer || !char_buffer) exit(EXIT_FAILURE);

    char_buffer->buffer = buffer;
    char_buffer->head   = 0;
    char_buffer->tail   = 0;
    char_buffer->length = length;
    
    // Initialize the buffer.
    for (size_t i = 0; i < length; i++)
        char_buffer->buffer[i] = '\0';

    return char_buffer;
} 

static size_t start = 0;
static size_t end   = 0;
static int    size  = 3;


/* Put a character onto the buffer. */
void cbuf_put(CharacterBuffer* ccbuf, char c) {
    ccbuf->buffer[end] = c;
    end++;
    end %= size;
    return;
}

/* Get a character from the circular char buffer.*/
char cbuf_get(CharacterBuffer* ccbuf) {
    char c = ccbuf->buffer[start];
    ccbuf->buffer[start] = '\0';
    
    start++;
    start %= size;
    return c;
}

/* Print a circular char buffer to stdout. */
void cbuf_print(CharacterBuffer* ccbuf, size_t size) {
    for (size_t i = 0; i < size; i++)
        { printf("%c", cbuf_get(ccbuf));}
    printf("\n");
}

int main(void) {
    CharacterBuffer* ccbuf = cbuf_create(size);
    cbuf_put(ccbuf, '7');
    cbuf_put(ccbuf, '7');
    cbuf_put(ccbuf, '9');
    cbuf_put(ccbuf, '9');
    cbuf_put(ccbuf, '9');

    cbuf_print(ccbuf, size);
    return 0;
}