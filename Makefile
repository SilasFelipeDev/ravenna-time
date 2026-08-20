.PHONY: all clean

.DEFAULT_GOAL := all

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

# ================ C++ CONFIGURAÇÕES ================
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude -Ivendor/webview/core/include

BRIDGE = src/bridge.cpp

BRIDGE_OBJ = build/bridge.o
# ===================================================


# ================    RAVENNA-TIME    ===============
TARGET = ravenna
# ===================================================


# ================  RAVENNA-TERMINAL  ===============
TEST_OBJ = build/date.o build/terminal_test.o

TARGET_TERMINAL = ravenna-terminal
# ===================================================

ifeq ($(OS), Windows_NT)
	RM = del /Q
	EXE = .exe
	OBJ_PATTERN = build\*.o
	MKDIR = if not exist build mkdir build
	WEBVIEW_INCLUDES = -Ivendor/webview2-headers
	WEBVIEW_LIBS = -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion

.PHONY: ravenna-terminal
ravenna-terminal: $(TARGET_TERMINAL)$(EXE)
else
	RM = rm -f
	EXE = 
	OBJ_PATTERN = build/*.o
	MKDIR = mkdir -p build
	WEBVIEW_INCLUDES = $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.1)
	WEBVIEW_LIBS = $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.1)
endif 

CXXFLAGS += $(WEBVIEW_INCLUDES)

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): $(OBJ) $(BRIDGE_OBJ)
	$(CXX) $(OBJ) $(BRIDGE_OBJ) $(WEBVIEW_LIBS) -o $@

build:
	$(MKDIR)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# C++ BUILD BRIDGE.CPP
build/bridge.o: $(BRIDGE) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@
# ====================

clean:
	$(RM) $(OBJ_PATTERN)
	$(RM) $(TARGET)$(EXE)
	$(RM) $(TARGET_TERMINAL)$(EXE)

$(TARGET_TERMINAL)$(EXE): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $@