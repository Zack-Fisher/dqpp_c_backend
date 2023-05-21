CC=gcc
CFLAGS=-I./include -Wall -Wextra -g
LINKERFLAGS=-lsqlite3 -lpthread -lcjson -g
SRCDIR=src
OBJDIR=obj
BINDIR=bin
SOURCES=$(shell find $(SRCDIR) -name '*.c')
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET=$(BINDIR)/program

all: directories $(TARGET)

test:
	make all
	./bin/program &
	cd test_client
	make -f Makefile
	cd ..
	./test_client/client localhost 8090

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LINKERFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all directories clean test
