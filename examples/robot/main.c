// serialio - demonstrate how to successfully read a line of text and
// This program takes in a serires of buffer words from you terminal
// The program then takes these words and tokenizes them, it does this in order to 
// save these words into a respected varibale, such as move or direction
// a space " " will be used to give a space in between each word.
// after these words are saved into the variable, it will then be able to have control of the Xarms movement


#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "readLine.h"

#define MAX_BUFFER 24
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 1
#define MAX_DEGREE 4
#define MAX_DIRECTION 2
#define MAX_STEPS 5
#define MAX_POSITION 4
#define MAX_AXIS 2
int main(void) {    

    init_serial();
    char input[MAX_BUFFER + 1] = {};
    char delims[MAX_DELIMS + 1] = {" "};

    puts("Serial I/O Test: readLine with tokens");
    printf("Enter text up to %i characters, or end w/ CR\n", MAX_BUFFER);
    printf("Line will be parsed into tokens\n");
    printf("Possible delimitors are (w/ ASCII code):\n ");
    printf("Format of command will be in this order: commanc of choice, arm of choice, direction to move in, and distance\n"); 
    printf("An example would be:\n");
    printf("move/joint1/positive/200");
    for (uint8_t delim=0; delim < MAX_DELIMS; delim++)
    {
        printf("'%c' 0x%x ", delims[delim], delims[delim]);
    }
    printf("\n");
    uint8_t num_char = readLine(input, MAX_BUFFER);

    printf("You entered %i characters\n", num_char);

    for (uint8_t out_char=0; out_char<num_char; out_char++)
    {
        printf("%c", input[out_char]);
    }
    printf("\n");

    // break input line into tokens
    char *tokens[MAX_TOKENS];
    uint8_t index = 0;
    tokens[index] = strtok(input, delims);
    while ( (tokens[index] != NULL) && (index < MAX_TOKENS - 1) ) {
        index++;
        tokens[index] = strtok(NULL, delims);
    }
    uint8_t tokens_found = index;

    printf("The %i tokens parsed are:\n", tokens_found);
    printf("index token\n");
    char rotate[MAX_DEGREE + 1] = {}; 
    char direction[MAX_DIRECTION + 1] = {};
    char distance[MAX_STEPS + 1] = {}; 
    char position[MAX_POSITION + 1] = {}; 
    char axis[MAX_AXIS + 1] = {}; 

    strncpy(rotate, tokens[0], strlen(tokens[MAX_DEGREE]));
    strncpy(direction, tokens[1], strlen(tokens[MAX_DIRECTION]));
    strncpy(distance, tokens[2], strlen(tokens[MAX_STEPS]));
    strncpy(position, tokens[3], strlen(tokens[MAX_POSITION]));
    strncpy(axis, tokens[4], strlen(tokens[MAX_AXIS])); 

    for (index=0; index<tokens_found; index++)
    {
        printf("%5i %s\n", index, tokens[index]);
    }
}
