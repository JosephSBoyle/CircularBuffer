/* A circular char buffer implementation. 

  Copyright (c) [2023] [Joseph S. Boyle]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>  // only necessary if running the example in `main`.


/* A fixed-size character buffer.
 *
 * Contains member variables representing the
 * read / write positions and the length of the
 * buffer. Intended for use as a circular buffer.
 */
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
    // basic usage example.
    int length = 4;
    
    CharacterBuffer* cbuf = cbuf_create(length);
    cbuf_put(cbuf, '7');
    cbuf_put(cbuf, '7');
    cbuf_put(cbuf, '9');
    cbuf_put(cbuf, '9');
    cbuf_put(cbuf, '9');

    // prints: '9799'
    cbuf_print(cbuf);
}
