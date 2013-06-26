TARGET=fecencode
CFLAGS=-c -Wall -Werror
SOURCES=main.c fecencode.c
OBJECTS=$(SOURCES:.c=.o)
TEST=
CC=clang

all: $(SOURCES) $(TARGET)
	
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET) 
