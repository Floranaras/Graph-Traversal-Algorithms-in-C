# Makefile for Social Network Graph Project
# File structure: include/graph.h, src/*.c, src/*.txt

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99
INCLUDEDIR = include
SRCDIR = src

# Source files
MAIN_SOURCES = $(SRCDIR)/main.c $(SRCDIR)/graph.c
BONUS_SOURCES = $(SRCDIR)/01-BONUS.c $(SRCDIR)/graph.c

# Executable names
MAIN_EXEC = $(SRCDIR)/main
BONUS_EXEC = $(SRCDIR)/bonus

# Default target
all: $(MAIN_EXEC)

# Build main program
$(MAIN_EXEC): $(MAIN_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(MAIN_SOURCES) -o $(MAIN_EXEC)

# Build bonus program
bonus: $(BONUS_EXEC)

$(BONUS_EXEC): $(BONUS_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(BONUS_SOURCES) -o $(BONUS_EXEC)

# Run main program
run: $(MAIN_EXEC)
	cd $(SRCDIR) && ./main

# Run bonus program
run-bonus: $(BONUS_EXEC)
	cd $(SRCDIR) && ./bonus

# Clean compiled files and output files
clean:
	rm -f $(MAIN_EXEC) $(BONUS_EXEC)
	rm -f $(SRCDIR)/*.exe
	rm -f $(SRCDIR)/*-SET.TXT
	rm -f $(SRCDIR)/*-DEGREE.TXT
	rm -f $(SRCDIR)/*-LIST.TXT
	rm -f $(SRCDIR)/*-MATRIX.TXT
	rm -f $(SRCDIR)/*-BFS.TXT
	rm -f $(SRCDIR)/*-DFS.TXT
	rm -f $(SRCDIR)/*-SUBGRAPH.TXT

# Clean only output files (keep executables)
clean-output:
	rm -f $(SRCDIR)/*-SET.TXT
	rm -f $(SRCDIR)/*-DEGREE.TXT
	rm -f $(SRCDIR)/*-LIST.TXT
	rm -f $(SRCDIR)/*-MATRIX.TXT
	rm -f $(SRCDIR)/*-BFS.TXT
	rm -f $(SRCDIR)/*-DFS.TXT
	rm -f $(SRCDIR)/*-SUBGRAPH.TXT

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build main program (default)"
	@echo "  bonus      - Build bonus program"
	@echo "  run        - Build and run main program"
	@echo "  run-bonus  - Build and run bonus program"
	@echo "  clean      - Remove all compiled files and output files"
	@echo "  clean-output - Remove only output files"
	@echo "  help       - Show this help message"

# Declare phony targets
.PHONY: all bonus run run-bonus clean clean-output help