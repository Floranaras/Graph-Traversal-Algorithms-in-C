# Makefile for Graph Traversal Project

CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Source files for main and bonus
SRCFILES = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/graph.c \
	$(SRCDIR)/fileInput.c \
	$(SRCDIR)/transversal.c

BONUS_SRC = \
	$(SRCDIR)/01-BONUS.c \
	$(SRCDIR)/graph.c \
	$(SRCDIR)/fileInput.c \
	$(SRCDIR)/transversal.c

# Object file paths
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
BONUS_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(BONUS_SRC))

# Create obj dir if needed
$(shell mkdir -p $(OBJDIR))

# Default
all: main

# Main program
main: $(OBJDIR)/main
	@echo "Main program compiled successfully in $(OBJDIR)/"

$(OBJDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Bonus program
bonus: $(OBJDIR)/bonus
	@echo "Bonus program compiled successfully in $(OBJDIR)/"
	@echo "Running bonus program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/bonus

$(OBJDIR)/bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .c to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run targets
run: main
	@echo "Running main program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/main

run-bonus: bonus
	@echo "Running bonus program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/bonus

# Clean
clean:
	rm -rf $(OBJDIR)
	rm -f $(SRCDIR)/*-SET.TXT
	rm -f $(SRCDIR)/*-DEGREE.TXT
	rm -f $(SRCDIR)/*-LIST.TXT
	rm -f $(SRCDIR)/*-MATRIX.TXT
	rm -f $(SRCDIR)/*-BFS.TXT
	rm -f $(SRCDIR)/*-DFS.TXT
	rm -f $(SRCDIR)/*-SUBGRAPH.TXT
	@echo "Cleaned all object files and outputs."

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Compile the main program (default)"
	@echo "  main       - Compile main program"
	@echo "  bonus      - Compile and run bonus program"
	@echo "  run        - Run main program"
	@echo "  run-bonus  - Run bonus program"
	@echo "  clean      - Remove builds and output files"
	@echo "  help       - Show help message"

.PHONY: all main bonus clean run run-bonus help
