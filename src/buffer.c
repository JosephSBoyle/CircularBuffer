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

/* Put a character onto the buffer. */
void cbuf_put(CharacterBuffer* cbuf, char c) {
    cbuf->buffer[cbuf->tail] = c;
    cbuf->tail++;
    cbuf->tail %= cbuf->length;
    // printf("tail:%lu\n",ccbuf->tail );
    return;
}

/* Get a character from the circular char buffer.*/
char cbuf_get(CharacterBuffer* cbuf) {
    // Read and reset the value.
    char c = cbuf->buffer[cbuf->head];
    cbuf->buffer[cbuf->head] = '\0';
    
    cbuf->head++;
    cbuf->head %= cbuf->length;
    return c;
}

/* Print a circular char buffer to stdout. */
void cbuf_print(CharacterBuffer* cbuf) {
    for (size_t i = 0; i < cbuf->length; i++)
        printf("%c", cbuf_get(cbuf));
    printf("\n");
}

int main(void) {
    int length = 4;
    
    CharacterBuffer* cbuf = cbuf_create(length);
    cbuf_put(cbuf, '7');
    cbuf_put(cbuf, '7');
    cbuf_put(cbuf, '9');
    cbuf_put(cbuf, '9');
    cbuf_put(cbuf, '9');

    cbuf_print(cbuf);
    return 0;
}