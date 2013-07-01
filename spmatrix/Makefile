#Makefile with boost test support
#The sources and any mocks must be C
#Boost is C++ obviously.

#any file example_test.cpp must have an accompanying example.c
#when "make test" is run, will compile example.c and any mocks
#using the c compiler, and example_test.cpp using the cpp compiler
#then it links them all, and runs the test.
#Note: not working for multiple test files in one dir yet :(
TARGET=spmatrix
MAIN=main.c
SOURCES=spmatrix.c

CFLAGS=-Wall -Werror -std=c99
CPPFLAGS=-Wall -Werror
LD_FLAGS=
INCLUDE_DIRS=
LIBS=

TESTCFLAGS=--coverage
TEST_LD_FLAGS=-static --coverage
TEST_LIBS=-lboost_unit_test_framework
TESTS=$(wildcard *_test.cpp)
TEST_TARGET=$(TESTS:.cpp=)
CC=gcc
CPP=g++

TESTER_OBJ = $(TESTS:.cpp=.o)
TARGET_OBJ=$(TESTS:_test.cpp=_t.o)
MOCK_OBJ  =$(MOCKS:.c=_t.o)
$(MOCK_OBJ): $(MOCKS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_OBJ): $(TESTS:_test.cpp=.c)
	$(CC) $(TESTCFLAGS) $(CFLAGS) -c $< -o $@

$(TESTER_OBJ): $(TESTS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TEST_TARGET): $(TESTER_OBJ) $(TARGET_OBJ) $(MOCK_OBJ)
	$(CPP) $(TEST_LD_FLAGS) -o $@ $(TESTER_OBJ) $(TARGET_OBJ) $(MOCK_OBJ) $(TEST_LIBS)

tests: $(TEST_TARGET)
test: tests
	./$(TEST_TARGET)
	gcov $(TARGET_OBJ)
clean:
	rm -rf *.o *.gcno *.gcda *.gcov $(TARGET) $(TEST_TARGET)
	
all: $(SOURCES) $(TARGET)

C_OBJECTS = $(SOURCES:.c=.o)
MAIN_OBJECT=$(MAIN:.c=.o)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(C_OBJECTS) $(MAIN_OBJECT)
	$(CC) $(LD_FLAGS) -o $@ $(MAIN_OBJECT) $(C_OBJECTS) 
