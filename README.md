# secret-codes
Construct and decode secret messages using books/text as the key.
Use C library function calls to open and read a text file.
Process data as it's being read using fseek() for efficiency to avoid loading large files into a program.
Parse strings in C.
Written using nano in UNIX environment.

Usage: 
- Type command "make" on command line to compile code.
- > ./decode [text_file] [code_file]
- e.g. > ./decode knuth knuth_code
- > ./encode [chunk size (int)] [text_file] [message]
- e.g. > ./encode 3 a_tale_of_two_cities.txt "Good judgement comes from experience, and experience comes from bad judgement."
