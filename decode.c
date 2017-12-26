#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

// Error messages
#define USAGE "Usage: decode textfile codefile\n"
#define INVALID_LINE "Invalid line number\n"
#define EMPTY "Document is empty\n"
#define INVALID_POSITION "Invalid character position for this line\n"
#define LENGTH "Invalid chunk size"


int main(int argc, char *argv[]) {
    // If the user did not enter the correct number of arguments then exit
    if(argc != 3) {
        fprintf(stderr, USAGE);
        exit(1);
        // The argument of 1 is a convention indicating the program failed
    }

    FILE *tf; // File pointer for the text document
    FILE *cf; // File pointer for the code file

    /* Open both files for reading. Terminate if there is any problem
     * opening the files */
    if((tf = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    if((cf = fopen(argv[2], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    // We will assume that lines read from the text file and the code file
    // will never exceed MAXLINE-1 characters.
    char code_line[MAXLINE];
    char text_line[MAXLINE];

    char *leftover;
    char *leftover2;
    int prev_line_num = 0;
    int current_line_num;
    int char_pos;
    int chunk_len;

    // Add your implmeentation below.

    // exit if file is empty, and stores first line into text_line otherwise
    if (fgets(text_line, MAXLINE, tf) == NULL) {
	fprintf(stderr, EMPTY);
	exit(1);
    }

    // loop to read through lines of code to be decoded
    while (fgets(code_line, MAXLINE, cf) != NULL) {
	current_line_num = strtol(code_line, &leftover, 10);
	char_pos = strtol(leftover, &leftover2, 10);
	chunk_len = strtol(leftover2, NULL, 10);

	// iterate to next line index from code file
	for (int i = prev_line_num; i < current_line_num; i++) {
	    // checks if the line number is valid
	    if(fgets(text_line, MAXLINE, tf) == NULL) {
		fprintf(stderr, INVALID_LINE);
		exit(1);
	    }
	}

        // check if char_pos is within line
        for (int j = 0; j < char_pos; j++) {
            if (text_line[j] == '\0') {
                fprintf(stderr, INVALID_POSITION);
                exit(1);
            }
        }

	// loop through chunk length to be printed
	for (int i = 0; i < chunk_len; i++) {
	    // check if chunk_len is within lin
	    if (text_line[char_pos + i] == '\0') {
		fprintf(stderr, LENGTH);
		exit(1);
	    } else {
		printf("%c", text_line[char_pos + i]);
	    }
	}
	prev_line_num = current_line_num;
    }

    // Print a newline after the end of the message so the prompt appears on
    // the next line.
    printf("\n");
    return 0;
}
