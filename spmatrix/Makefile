#Makefile with boost test support
#The sources and any mocks must be C
#Boost is C++ obviously.

#any file example_test.cpp must have an accompanying example.c
#when "make test" is run, will compile example.c and any mocks
#using the c compiler, and example_test.cpp using the cpp compiler
#then it links them all, and runs the test.
TARGET=spmatrix
MAIN=main.c
SOURCES=spmatrix.c set.c

UNAME := $(shell sh -c 'uname')

ifeq ($(UNAME), Linux)
	CC=gcc
	CPP=g++
endif
ifeq ($(UNAME), Darwin)
	CC=clang
	CPP=clang++
endif

CFLAGS=-Wall -Werror -std=c99
CPPFLAGS=-Wall -Werror -DBOOST_TEST_DYN_LINK=1
LD_FLAGS=
INCLUDE_DIRS=
LIBS=


TESTCFLAGS=-fprofile-arcs -ftest-coverage
TEST_LD_FLAGS=-fprofile-arcs -ftest-coverage
TEST_LIBS=-lboost_unit_test_framework
TESTS=$(wildcard *_test.cpp)
TEST_TARGET=$(TESTS:.cpp=)
MOCKS=set.c

TESTER_OBJ = $(TESTS:.cpp=.o)
TARGET_OBJ = $(TESTS:_test.cpp=_t.o)
MOCK_OBJ  =$(MOCKS:.c=_t.o)

all: $(SOURCES) $(TARGET)

$(MOCK_OBJ): $(MOCKS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_OBJ): %_t.o : %_test.cpp %.c
	$(CC) $(TESTCFLAGS) $(CFLAGS) -c $(<:_test.cpp=.c) -o $@

$(TESTER_OBJ): %_test.o : %_test.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TEST_TARGET): %_test : %_test.o %_t.o $(MOCK_OBJ) 
	$(CPP) $(LD_FLAGS) $(TEST_LD_FLAGS) -o $@ $< $(<:_test.o=_t.o) $(filter-out $(<:_test.o=_t.o),$(MOCK_OBJ)) $(TEST_LIBS)

RAN_TESTS = $(TESTS:_test.cpp=.c.gcov)

.PHONY: always
$(RAN_TESTS) : %.c.gcov : %_test 
	./$<
	gcov $(@:.c.gcov=_t.o)
.PHONY: run_tests
run_tests: $(RAN_TESTS)

tests: $(TEST_TARGET)
.PHONY: test
test: tests run_tests  
	@cowsay "Nominal"

C_OBJECTS = $(SOURCES:.c=.o)
MAIN_OBJECT=$(MAIN:.c=.o)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(C_OBJECTS) $(MAIN_OBJECT)
	$(CC) $(LD_FLAGS) -o $@ $(MAIN_OBJECT) $(C_OBJECTS) 

.PHONY: clean
clean:
	rm -rf *.o *.gcno *.gcda *.gcov $(TARGET) $(TEST_TARGET)
	
