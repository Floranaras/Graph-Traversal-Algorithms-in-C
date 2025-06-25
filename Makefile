# Makefile for Graph Traversal Project
CC = gcc
CFLAGS = -Wall -std=c99
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Main program
main: $(OBJDIR)/main
	@echo "Main program compiled successfully in $(OBJDIR)/"

$(OBJDIR)/main: $(SRCDIR)/main.c $(SRCDIR)/graph.c
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCDIR)/main.c $(SRCDIR)/graph.c -o $(OBJDIR)/main

# Bonus program - compiles and runs automatically
bonus: $(OBJDIR)/bonus
	@echo "Bonus program compiled successfully in $(OBJDIR)/"
	@echo "Running bonus program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/bonus

$(OBJDIR)/bonus: $(SRCDIR)/01-BONUS.c $(SRCDIR)/graph.c
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCDIR)/01-BONUS.c $(SRCDIR)/graph.c -o $(OBJDIR)/bonus

# Clean target
clean:
	rm -rf $(OBJDIR)
	rm -f $(SRCDIR)/*-SET.TXT
	rm -f $(SRCDIR)/*-DEGREE.TXT
	rm -f $(SRCDIR)/*-LIST.TXT
	rm -f $(SRCDIR)/*-MATRIX.TXT
	rm -f $(SRCDIR)/*-BFS.TXT
	rm -f $(SRCDIR)/*-DFS.TXT
	rm -f $(SRCDIR)/*-SUBGRAPH.TXT
	@echo "Cleaned all executables from $(OBJDIR)/"
	@echo "Cleaned all generated output files from $(SRCDIR)/"


# Run main program
run: $(OBJDIR)/main
	@echo "Running main program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/main

# Run bonus program
run-bonus: $(OBJDIR)/bonus
	@echo "Running bonus program from src/ directory..."
	@cd $(SRCDIR) && ../$(OBJDIR)/bonus

# Help target
help:
	@echo "Available targets:"
	@echo "  main      - Compile main program to $(OBJDIR)/main"
	@echo "  bonus     - Compile and automatically run bonus program"
	@echo "  run       - Run the main program"
	@echo "  run-bonus - Run the bonus program"
	@echo "  clean     - Remove all executables from $(OBJDIR)/"
	@echo "  help      - Show this help message"

.PHONY: main bonus clean run run-bonus help