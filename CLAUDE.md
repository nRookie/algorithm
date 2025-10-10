# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a competitive programming practice repository containing solutions to problems from multiple online judges:
- **AtCoder** (abc, arc, agc contests)
- **Codeforces** (organized by algorithm type)
- **AcWing** (organized by algorithm category)
- **LeetCode** (minimal)

The repository is primarily C++ based, with a few Python solutions.

## Repository Structure

```
algorithm/
├── acwing/          # AcWing problems organized by topic
│   ├── graph/       # Graph algorithms (Floyd, Dijkstra, SPFA, Tarjan, etc.)
│   ├── dp/          # Dynamic programming
│   ├── math/        # Mathematical algorithms
│   ├── DFS/         # Depth-first search problems
│   ├── datastructure/
│   ├── greedy/
│   ├── jinjie/      # Advanced algorithms
│   └── zalgorithm/
├── atcoder/         # AtCoder contests (abc, arc, agc)
│   ├── abc###/      # AtCoder Beginner Contest solutions
│   ├── arc###/      # AtCoder Regular Contest solutions
│   └── practice/    # Practice problems by type
├── codeforces/      # Codeforces problems by algorithm type
│   ├── binarysearch/
│   ├── dp/
│   ├── greedy/
│   ├── implementation/
│   ├── constructivealgorithm/
│   └── ...          # Many more categories
├── numberTheory/
├── leetcode/
└── template/        # Template file with common code snippets
```

## Development Commands

### Compiling and Running C++ Files

The standard approach for competitive programming in this repository:

```bash
# Compile a single file (no optimization flags)
g++ -o solution problem.cpp

# Compile with debugging symbols
g++ -g -o solution problem.cpp

# Run the compiled binary
./solution

# Or compile and run in one command
g++ problem.cpp && ./a.out
```

**Note**: This repository doesn't use build systems (no Makefile, CMake, etc.). Each problem is a standalone C++ file that can be compiled individually.

### Testing

No automated test framework is used. Problems are tested manually by:
1. Compiling the solution
2. Running with sample inputs from the problem statement
3. Verifying output matches expected results

Input is typically provided via stdin (redirecting from a file or typing directly).

## Code Architecture

### Template Structure

The `template/template.cpp` file contains common code snippets used across solutions:

- **Graph representation**: Adjacency list using arrays (`h[]`, `ne[]`, `e[]`, `w[]`, `idx`)
- **Graph algorithms**: `add()` function for adding edges
- **Number theory**: Extended Euclidean algorithm (`exgcd`)
- **Common typedefs**: `PII` for `pair<int,int>`, `ll` for `long long`
- **Constants**: `N`, `M` array size definitions

### Common Patterns

**Graph templates** (see `acwing/graph/single-source-shortest-path/template.cpp`):
- SPFA (Bellman-Ford optimization) using manual queue
- Dijkstra (naive O(n²) version)
- Dijkstra with priority queue (heap optimization)
- Adjacency list representation with static arrays

**File naming conventions**:
- Problem files named by problem number: `1172.cpp`, `abc334_b.cpp`, etc.
- Some files have suffixes: `-ok.cpp`, `-retry.cpp`, `-1.cpp` for different attempts
- Tutorial implementations: `*-tutorial.cpp`

### Algorithm Categories in AcWing

The `acwing/graph/` directory contains implementations organized by graph algorithm type:
- `basic/`: Floyd-Warshall, Kruskal, Prim, Tarjan, SPFA
- `single-source-shortest-path/`: Various shortest path problems
- `SCC/`: Strongly Connected Components
- `LCA/`: Lowest Common Ancestor (including Tarjan's offline algorithm)
- `DifferenceConstraints/`: System of difference constraints
- `negative-circle/`: Negative cycle detection
- `floyd/`: All-pairs shortest path problems

### Markdown Files

- `good-one.md`: Contains links to particularly challenging or interesting problems
- `spent-alot-of-time.md`: Problems that required significant time investment

## Working with Solutions

When creating new solutions:
1. Navigate to the appropriate directory based on the online judge and problem category
2. Create a new `.cpp` file named after the problem number/ID
3. Use template code from `template/template.cpp` as needed
4. Compile and test manually with sample inputs
5. For graph problems, use the adjacency list structure from existing solutions

When reading existing solutions:
- Problem numbers in filenames correspond to the online judge's problem ID
- Check `-ok.cpp` or similar suffixes for working versions if multiple attempts exist
- Graph problems follow consistent adjacency list patterns across the repository
