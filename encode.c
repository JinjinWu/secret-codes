#include <stdio.h>
#include <stdlib.h>

#include <string.h>  // Only used for strlen
#include <stdbool.h>

#define MAXLINE 256

// Error messages
#define USAGE "Usage: encode chunksize textfile msg\n"
#define ENCODE_FAILED "Could not encode message.\n"

// checks if the text_line matches the chunk from 2nd character in chunk
bool chunk_match(char *text_line, char *chunk, int chunk_size) {
    for (int i = 1; i < chunk_size; i++) {
	if (text_line[i] == '\0' || text_line[i] != chunk[i]) {
	    return false;
	}
    }
    return true;
}

int main(int argc, char *argv[]) {
    // Check to make sure the user entered the correct number of arguments
    if(argc != 4) {
        fprintf(stderr, USAGE);
        exit(1);
        // The argument of 1 is a convention indicating the program failed
    }

    FILE *tf; // File pointer for the text document

    // determine message chunks size
    int chunk_size = strtol(argv[1], NULL, 0);
    if(chunk_size == 0) {
        fprintf(stderr, "Invalid chunk size\n");
        exit(1);
    }

    // check for empty text file
    if((tf = fopen(argv[2], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    // The message to encode is in argv[3].  We will use a pointer to char
    // to give it a better name.
    char *message = argv[3];
    int msg_length = strlen(message);  // only allowed use of string functions

    // Complete the implmentation below
    int line_num = 0;
    char *current_chunk = message;
    char text_line[MAXLINE];
    int num_chunks = msg_length / chunk_size;
    int last_chunk_size = msg_length % chunk_size;

    // loop through text file
    while(fgets(text_line, MAXLINE, tf) != NULL) {

	// increment through the characters of the current line
	for (int i = 0; text_line[i] != '\0'; i++) {

            // first character of chunk matches a character in text_line
	    if (text_line[i] == current_chunk[0]) {

		// change chunk_size to last_chunk_size to handle leftover chunk size case
		if ((current_chunk - message) == num_chunks * chunk_size) {
                    chunk_size = last_chunk_size;
		}

		// call to helper function returns bool
		if (chunk_match(&text_line[i], current_chunk, chunk_size)) {
		    printf("%d %d %d\n", line_num, i, chunk_size);
		    current_chunk = current_chunk + chunk_size;
		    break; // found a chunk on a line, go to the next line
		}
	    }
	}
	line_num++;
	// stop reading through text file, done encoding message
	if (*current_chunk == '\0') {
	    break;
	}
    }

    // check that entire message was encoded
    if (*current_chunk != '\0') {
	fprintf(stderr, ENCODE_FAILED);
	exit(1);
    }

    return 0;
}
