FLAGS = -Wall -std=gnu99 -g

all: decode encode

decode: decode.o
	gcc ${FLAGS} -o $@ $^ -lm

encode: encode.o
	gcc ${FLAGS} -o $@ $^ -lm

%.o : %.c
	gcc ${FLAGS} -c $<

clean:
	rm *.o decode encode
