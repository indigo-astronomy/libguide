TARGET = guider_test
LIBS = -lm
CC = gcc
#CFLAGS = -I./ -Wall -DDEBUG
CFLAGS = -I./ -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

dist:
	mkdir donuts_guide
	cp *.c donuts_guide/
	cp *.h donuts_guide/
	cp Makefile donuts_guide/
	tar -zcf donuts_guide.tgz donuts_guide/
	rm -rf donuts_guide/

clean:
	-rm -f *.o
	-rm -f $(TARGET)
