TARGET=fector
CFLAGS=-c -Wall -Werror
SOURCES= main fector
OBJECTS= $(SOURCES:.c=.o)


CC=gcc

all: $(SOURCES) $(TARGET)
	
$(TARGET):
	$(CC) $(OBJECTS) -o $@ 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o fector
