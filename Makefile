MY_NAME=main
MY_CC=mpicc
MY_SYMBS=-DKEEP_FILES
MY_CFLAGS=-Wall -O3 -std=gnu99
MY_INCS=-I./cJSON/
MY_LIBS=-L./cJSON/
MY_LINKS=-lcjson

all: main_JSON.c 
	$(MY_CC) $(MY_CFLAGS) $(MY_SYMBS) $(MY_INCS) -o $(MY_NAME) $^ $(MY_LIBS) $(MY_LINKS)
lib:
	$(MY_CC) $(MY_CFLAGS) $(MY_SYMBS) $(MY_INCS)
	ar rcs lib$(MY_NAME).a 

clean:
	rm *.o
