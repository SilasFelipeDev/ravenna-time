.PHONY: all clean

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

# ================ C++ CONFIGURAÇÕES ================
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude -Ivendor/webview/core/include

BRIDGE = src/bridge.cpp

BRIDGE_OBJ = build/bridge.o
# ================ ================== ===============

TARGET = ravenna

ifeq ($(OS), Windows_NT)
	RM = del /Q
	EXE = .exe
	OBJ_PATTERN = build\*.o
	MKDIR = if not exist build mkdir build
	WEBVIEW_INCLUDES = -Ivendor/webview2-headers
	WEBVIEW_LIBS = -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion
else
	RM = rm -f
	EXE = 
	OBJ_PATTERN = build/*.o
	MKDIR = mkdir -p build
	WEBVIEW_INCLUDES =
	WEBVIEW_LIBS = 
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