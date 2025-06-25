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
│   └── *.txt            # Input graph files
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

## Compilation and Usage

### Using Makefile:

```bash
# Build and run main program
make run

# Build and run bonus program
make run-bonus

# Clean compiled files
make clean

# Show help
make help
```

### Manual Compilation:

```bash
# Main program
gcc -Wall -std=c99 -Iinclude src/main.c src/graph.c -o src/main

# Bonus program
gcc -Wall -std=c99 -Iinclude src/01-BONUS.c src/graph.c -o src/bonus
```

### Running:

```bash
cd src
./main
# Input filename: G.txt
# Input start vertex for the traversal: Clark

./bonus
# Input first graph filename: G.txt
# Input second graph filename: H.txt
```

## Algorithm Details

### Breadth-First Search (BFS)
- Uses queue-based implementation
- When multiple unvisited neighbors exist, visits them in alphabetical order
- Guarantees shortest path discovery in unweighted graphs

### Depth-First Search (DFS)
- Uses recursive implementation
- When multiple unvisited neighbors exist, visits them in alphabetical order
- Explores as far as possible along each branch before backtracking

### Vertex Ordering Rules
- **Input Order**: Adjacency list and matrix outputs preserve original file order
- **Alphabetical Order**: Set outputs, degree lists, and traversal tie-breaking use lexicographic ordering

## Programming Constraints

This implementation follows strict procedural programming guidelines:

- **C99 Standard**: Compatible with `gcc -Wall -std=c99`
- **Hungarian Notation**: `nCount`, `strName`, `pPointer`
- **No Global Variables**: All data passed through function parameters
- **Static Memory**: No dynamic allocation (`malloc`/`free`)
- **No Early Returns**: Functions use conditional logic instead of multiple returns
- **Standard Library Only**: Uses `stdio.h`, `string.h`, `stdlib.h`

## Data Structure

```c
struct graphTag {
    char vertices[20][10];              // Vertex names (max 8 chars + null)
    int nVertices;                      // Number of vertices
    int adjMatrix[20][20];              // Adjacency matrix
    char adjList[20][20][10];           // Adjacency list (preserves input order)
    int adjCount[20];                   // Adjacent vertex counts
};
```

## Error Handling

The program handles various error conditions:

- **File Not Found**: `File <filename> not found.`
- **Vertex Not Found**: `Vertex <vertex> not found.`
- **Invalid Input**: Graceful handling of malformed input files

## Bonus Feature: Subgraph Detection

The bonus program checks if graph H is a subgraph of graph G:

```bash
./bonus
# Input: G.txt H.txt
# Output: G-H-SUBGRAPH.TXT
```

Output format shows each vertex and edge with `+` (present in G) or `-` (not present):
```
Bruce +
Diana +
Hal +
(Bruce,Diana) +
(Diana,Hal) +
H is a subgraph of G.
```

## Testing

Test with various graph types:
- Single vertex graphs
- Disconnected components
- Complete graphs
- Trees and forests
- Edge cases (empty graphs, isolated vertices)

## Performance

- **Time Complexity**: O(V²) for matrix operations, O(V+E) for traversals
- **Space Complexity**: O(V²) for adjacency matrix storage
- **Maximum Capacity**: 20 vertices, 8-character vertex names

## Contributing

When contributing to this project:

1. Maintain C99 compliance and coding standards
2. Follow Hungarian notation consistently
3. Include comprehensive test cases
4. Update documentation for new features
5. Ensure all functions have proper error handling

### Commit Message Guidelines

This project uses [Conventional Commits](https://www.conventionalcommits.org/) for clear and standardized commit messages:

| **Type**       | **Purpose** |
|----------------|-------------|
| **`feat`**     | Add a new feature (functions, logic) |
| **`fix`**      | Fix a bug (incorrect output, logic errors) |
| **`refactor`** | Improve code without changing behavior |
| **`perf`**     | Optimize performance (faster loops, better memory usage) |
| **`style`**    | Formatting changes (indentation, comments) |
| **`test`**     | Add or update test cases |
| **`build`**    | Modify Makefile or compilation setup |
| **`docs`**     | Update README, specs, or comments |
| **`chore`**    | Non-code maintenance (renaming files, updating `.gitignore`) |

#### Examples:
```bash
feat: add BFS traversal algorithm
fix: correct adjacency matrix initialization
refactor: optimize vertex sorting function
perf: improve memory usage in graph structure
style: fix indentation in graph.c
test: add edge case tests for single vertex graphs
build: update Makefile with new compiler flags
docs: update README with installation instructions
chore: update .gitignore for IDE files
```

#### Format:
```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

**Examples with scope:**
```bash
feat(graph): implement depth-first search algorithm
fix(io): handle file not found errors properly
refactor(traversal): simplify BFS queue implementation
```

## License

This project is for educational purposes. See course guidelines for usage restrictions.

---

**Note**: This implementation prioritizes code clarity and educational value over optimal performance. For production use, consider more efficient graph representations like adjacency lists for sparse graphs.