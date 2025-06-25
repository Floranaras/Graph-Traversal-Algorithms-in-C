# Graph Algorithms Implementation

A C99 implementation of undirected graph data structures with breadth-first search (BFS) and depth-first search (DFS) traversal algorithms.

## Overview

This project implements a graph processing system that reads adjacency list data from text files, stores it using adjacency matrix representation, and performs various graph operations including traversals and analysis.

## Features

- **Graph Representation**: Adjacency matrix implementation for undirected graphs
- **Graph Traversals**: BFS and DFS algorithms with deterministic vertex ordering
- **Multiple Output Formats**: Vertex sets, edge sets, degree lists, adjacency representations
- **Subgraph Detection**: Bonus functionality to check if one graph is a subgraph of another
- **Strict C99 Compliance**: Follows procedural programming standards with Hungarian notation

## File Structure

```
project/
├── include/
│   └── graph.h          # Graph data structure and function declarations
├── src/
│   ├── main.c           # Main program implementation
│   ├── graph.c          # Graph operations and algorithms
│   ├── 01-BONUS.c       # Subgraph detection program
│   └── *.txt            # Input graph files (G.txt, H.txt, etc.)
├── obj/                 # Compiled executables (auto-generated)
├── specs/               # Project specifications
├── Makefile             # Build automation
├── README.md            # This file
└── .gitignore           # Version control exclusions
```

## Input Format

Graph data is stored in text files with the following format:

```
<number_of_vertices>
<vertex1> <adjacent_vertex1> <adjacent_vertex2> ... -1
<vertex2> <adjacent_vertex1> <adjacent_vertex2> ... -1
...
```

### Example (G.txt):
```
4
Diana Hal Bruce Clark -1
Bruce Diana -1
Hal Clark Diana -1
Clark Hal Diana -1
```

## Output Files

The program generates six output files for each input graph:

1. **`<name>-SET.TXT`**: Vertex set V(G) and edge set E(G)
2. **`<name>-DEGREE.TXT`**: Vertices with their degrees
3. **`<name>-LIST.TXT`**: Adjacency list representation
4. **`<name>-MATRIX.TXT`**: Adjacency matrix representation
5. **`<name>-BFS.TXT`**: Breadth-first search traversal
6. **`<name>-DFS.TXT`**: Depth-first search traversal

### Sample Output Format:

**G-SET.TXT**:
```
V(G)={Bruce,Clark,Diana,Hal}
E(G)={(Bruce,Diana),(Clark,Diana),(Clark,Hal),(Diana,Hal)}
```

**G-BFS.TXT** (starting from Clark):
```
Clark Diana Hal Bruce
```

## Quick Start

### Prerequisites
- GCC compiler with C99 support
- Make utility
- Git (for version control)

### Setup and Run

```bash
# Clone the repository
git clone <repository-url>
cd graph-traversal-algorithms

# Build and run main program
make run

# Build and run bonus program (automatically executes)
make bonus

# Clean compiled files
make clean

# Show all available commands
make help
```

## Compilation and Usage

### Using Makefile (Recommended):

```bash
# Build and run main program from src/ directory
make run

# Build main program only
make main

# Build and automatically run bonus program
make bonus

# Run bonus program only (if already compiled)
make run-bonus

# Clean all compiled executables
make clean

# Show help with all available targets
make help
```

The Makefile automatically:
- Creates the `obj/` directory for executables
- Compiles with proper flags (`-Wall -std=c99`)
- Runs programs from the `src/` directory where input files are located
- Handles include paths correctly

### Manual Compilation:

```bash
# Main program
gcc -Wall -std=c99 -Iinclude src/main.c src/graph.c -o obj/main

# Bonus program  
gcc -Wall -std=c99 -Iinclude src/01-BONUS.c src/graph.c -o obj/bonus
```

### Running Programs:

**Main Program:**
```bash
make run
# Input filename: G.txt
# Input start vertex for the traversal: Clark
```

**Bonus Program:**
```bash
make bonus
# Input first graph filename: G.txt
# Input second graph filename: H.txt
```

## Algorithm Details

### Breadth-First Search (BFS)
- Uses queue-based implementation
- When multiple unvisited neighbors exist, visits them in alphabetical order
- Guarantees shortest path discovery in unweighted graphs
- Time complexity: O(V + E)

### Depth-First Search (DFS)
- Uses recursive implementation
- When multiple unvisited neighbors exist, visits them in alphabetical order
- Explores as far as possible along each branch before backtracking
- Time complexity: O(V + E)

### Vertex Ordering Rules
- **Input Order**: Adjacency list and matrix outputs preserve original file order
- **Alphabetical Order**: Set outputs, degree lists, and traversal tie-breaking use lexicographic ordering

## Programming Constraints

This implementation follows strict procedural programming guidelines:

- **C99 Standard**: Compatible with `gcc -Wall -std=c99`
- **Hungarian Notation**: `nCount`, `strName`, `pPointer`
- **No Global Variables**: All data passed through function parameters
- **Static Memory**: No dynamic allocation (`malloc`/`free`)
- **No Early Returns/Breaks**: Functions use conditional logic and flags instead
- **No Ternary Operators**: Uses explicit if-else statements
- **Standard Library Only**: Uses `stdio.h`, `string.h`, limited `stdlib.h`
- **Void Functions**: Use pointer parameters for returning values

### Code Style Requirements:
- All variables declared at function beginning
- Function names: camelCase starting with lowercase verb-noun
- Constants: ALL_CAPS
- No `goto`, `continue`, early `break` statements
- File operations use pattern: `if ((pFile = fopen(filename, "w")) != NULL)`

## Data Structure

```c
struct graphTag {
    String10 vertices[MAX_VERTICES];    // Vertex names (max 8 chars + null)
    int nVertices;                      // Number of vertices
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix
    String10 adjList[MAX_VERTICES][MAX_VERTICES]; // Adjacency list (preserves input order)
    int adjCount[MAX_VERTICES];         // Adjacent vertex counts
};
typedef struct graphTag graphType;

// Type definitions
typedef char String10[10];
typedef char String50[50];
#define MAX_VERTICES 20
```

## Error Handling

The program handles various error conditions gracefully:

- **File Not Found**: `File <filename> not found.`
- **Vertex Not Found**: `Vertex <vertex> not found.`
- **Invalid Input**: Graceful handling of malformed input files
- **No Early Termination**: Uses flag-based control flow

## Bonus Feature: Subgraph Detection

The bonus program (`01-BONUS.c`) checks if graph H is a subgraph of graph G:

```bash
make bonus
# Input first graph filename: G.txt
# Input second graph filename: H.txt
# Output: G-H-SUBGRAPH.TXT
```

**Output format** shows each vertex and edge with `+` (present in G) or `-` (not present):
```
Bruce +
Diana +
Hal +
(Bruce,Diana) +
(Diana,Hal) +
H is a subgraph of G.
```

The subgraph check verifies:
1. All vertices of H exist in G
2. All edges of H exist in G
3. Outputs results in alphabetical order

## Testing

Test with various graph types:
- **Single vertex graphs**: Minimal test cases
- **Disconnected components**: Multiple isolated subgraphs  
- **Complete graphs**: All vertices connected to all others
- **Trees and forests**: Acyclic connected components
- **Edge cases**: Empty graphs, isolated vertices
- **Different sizes**: 1, 5, 10, 20 vertices (maximum)

### Test Files Included:
- `G.txt` - Sample 4-vertex graph
- `H.txt` - Sample 3-vertex subgraph
- Additional test files for comprehensive testing

## Performance

- **Time Complexity**: 
  - Matrix operations: O(V²)
  - Traversals: O(V + E)
  - File I/O: O(V + E)
- **Space Complexity**: O(V²) for adjacency matrix storage
- **Maximum Capacity**: 20 vertices, 8-character vertex names
- **Memory**: Static allocation only, no dynamic memory management

## Project Structure Details

### Build System:
- **Makefile**: Automated compilation and execution
- **obj/ directory**: Contains all compiled executables
- **Automatic directory creation**: `obj/` created if not exists
- **Clean builds**: `make clean` removes all executables

### Version Control:
- **.gitignore**: Excludes executables, output files, IDE files
- **Organized structure**: Source, headers, and outputs separated
- **Documentation**: Comprehensive README and inline comments

## Contributing

When contributing to this project:

1. **Maintain C99 compliance** and coding standards
2. **Follow Hungarian notation** consistently
3. **Include comprehensive test cases** for new features
4. **Update documentation** for any changes
5. **Ensure proper error handling** without early returns
6. **Test thoroughly** with various graph configurations

### Commit Message Guidelines

This project uses [Conventional Commits](https://www.conventionalcommits.org/) for clear and standardized commit messages:

| **Type**       | **Purpose** |
|----------------|-------------|
| **`feat`**     | Add a new feature (functions, algorithms) |
| **`fix`**      | Fix a bug (incorrect output, logic errors) |
| **`refactor`** | Improve code without changing behavior |
| **`perf`**     | Optimize performance (algorithms, memory) |
| **`style`**    | Formatting changes (indentation, naming) |
| **`test`**     | Add or update test cases |
| **`build`**    | Modify Makefile or compilation setup |
| **`docs`**     | Update README, specs, or comments |
| **`chore`**    | Maintenance (files, .gitignore updates) |

#### Examples:
```bash
feat: add BFS traversal algorithm
fix: correct adjacency matrix initialization  
refactor: optimize vertex sorting with flags
perf: improve memory usage in graph structure
style: fix Hungarian notation consistency
test: add edge case tests for isolated vertices
build: update Makefile with obj/ directory
docs: update README with new build instructions
chore: update .gitignore for output files
```

#### Format:
```
<type>(<scope>): <description>

[optional body explaining the change]

[optional footer with breaking changes]
```

**Examples with scope:**
```bash
feat(graph): implement depth-first search algorithm
fix(io): handle file not found with proper flags
refactor(traversal): simplify BFS queue using procedural style
build(makefile): add automatic execution for bonus target
```

## Development Notes

### Known Limitations:
- Maximum 20 vertices per graph
- Vertex names limited to 8 characters
- Static memory allocation only
- Procedural programming constraints limit some optimizations

### Future Enhancements:
- Support for directed graphs
- Weighted edge support
- Additional traversal algorithms
- Enhanced error reporting

## License

This project is for educational purposes as part of CCDSALG coursework. See course guidelines for usage restrictions and academic integrity policies.

---

**Note**: This implementation prioritizes code clarity, educational value, and strict procedural programming compliance over optimal performance. The design follows academic requirements for demonstrating fundamental graph algorithms and C programming principles.