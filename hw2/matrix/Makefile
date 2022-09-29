CC=g++ -std=c++0x
CFLAGS=-c -Wall
LDFLAGS=
IMPR=
SOURCES=main.cpp matrix.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(IMPR) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm *.o main