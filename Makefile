FLAGS = -Wall -std=gnu99 -g

all: copy image_filter

copy: copy.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

image_filter: image_filter.o
	gcc ${FLAGS} -o $@ $^ -lm

%.o: %.c bitmap.h
	gcc ${FLAGS} -c $<

clean:
	rm *.o image_filter copy

test:
	mkdir images -p
	./copy < dog.bmp > images/dog_copy.bmp
