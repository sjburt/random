TARGET=spmatrix
CFLAGS=-Wall -Werror
LD_FLAGS=
MAIN=main.c
SOURCES=spmatrix.c
TEST=spmatrix_test.cpp
C_OBJECTS=$(SOURCES:.c=.o)
MAIN_OBJECT=$(MAIN:.c=.o)
TEST_OBJECTS=$(TEST:.cpp=.o)
CC=clang
CXX=clang++
TEST_TARGET=$(TEST:.cpp=)

all: $(SOURCES) $(TARGET)

$(TARGET): $(C_OBJECTS) $(MAIN_OBJECT)
	$(CC) $(LD_FLAGS) $(MAIN_OBJECT) $(C_OBJECTS) -o $@ 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CXX) $(CPPFLAGS) -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(C_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CPPFLAGS) $(C_OBJECTS) $(TEST_OBJECTS) -o $@

clean:
	rm -rf *.o $(TARGET) $(TEST_TARGET)
