.PHONY: all clean

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

TARGET = ravenna

ifeq ($(OS), Windows_NT)
	RM = del /Q
	EXE = .exe
	OBJ_PATTERN = build\*.o
	MKDIR = if not exist build mkdir build
else
	RM = rm -f
	EXE = 
	OBJ_PATTERN = build/*.o
	MKDIR = mkdir -p build
endif 

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

build:
	$(MKDIR)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_PATTERN)
	$(RM) $(TARGET)$(EXE)