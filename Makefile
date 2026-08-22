.PHONY: all clean

.DEFAULT_GOAL := all

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

# ================ C++ CONFIGURAÇÕES ================
CXX = g++

CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude -Ivendor/webview/core/include -Ibuild

BRIDGE = src/bridge.cpp

BRIDGE_OBJ = build/bridge.o

MAIN_SRC = src/main.cpp

MAIN_OBJ = build/main.o
# ===================================================


# ================    RAVENNA-TIME    ===============
TARGET = ravenna

RAVENNA_OBJ = build/date.o $(MAIN_OBJ) $(BRIDGE_OBJ)
# ===================================================


# ================  RAVENNA-TERMINAL  ===============
TEST_OBJ = build/date.o build/terminal_test.o

TARGET_TERMINAL = ravenna-terminal
# ===================================================

# ==============   EMBED UI HTML/CSS   ==============
UI_HTML = ui/index.html

UI_CSS = ui/css/style.css

UI_HEADER = build/ui_html.h
# ===================================================

ifeq ($(OS), Windows_NT)
	RM = del /Q
	EXE = .exe
	OBJ_PATTERN = build\*.o
	UI_HEADER_CLEAN = build\ui_html.h
	MKDIR = if not exist build mkdir build
	WEBVIEW_INCLUDES = -Ivendor/webview2-headers
	WEBVIEW_LIBS = -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion
	PYTHON = python

.PHONY: ravenna-terminal
ravenna-terminal: $(TARGET_TERMINAL)$(EXE)
else
	RM = rm -f
	EXE = 
	OBJ_PATTERN = build/*.o
	UI_HEADER_CLEAN = build/ui_html.h
	MKDIR = mkdir -p build
	WEBVIEW_INCLUDES = $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.1)
	WEBVIEW_LIBS = $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.1)
	PYTHON = python3
endif 

CXXFLAGS += $(WEBVIEW_INCLUDES)

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): $(RAVENNA_OBJ)
	$(CXX) $(RAVENNA_OBJ) $(WEBVIEW_LIBS) -o $@

$(UI_HEADER): $(UI_HTML) $(UI_CSS) | build
	$(PYTHON) tools/embed_html.py $(UI_HTML) $(UI_CSS) $(UI_HEADER) INDEX_HTML

$(MAIN_OBJ): $(MAIN_SRC) $(UI_HEADER) | build
	$(CXX) $(CXXFLAGS) -c $(MAIN_SRC) -o $@

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
	$(RM) $(UI_HEADER_CLEAN)
	$(RM) $(TARGET)$(EXE)
	$(RM) $(TARGET_TERMINAL)$(EXE)

$(TARGET_TERMINAL)$(EXE): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $@