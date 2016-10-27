ROSE's Graphs
=============

This tool aims at extracting a variety of graphs from source codes using the ROSE Compiler.
The graphs can be Abstract Syntax Tree (AST), Call Graph (CG), Control Flow Graph (CFG), and Data Flow Graph (DFG).
Outputs can be generated in GraphViz format or a Numpy format.

## Goals

The goal of this tool is to build datasets of graphs for machine-learning research.

## Outputs

### GraphViz

To permits people to visualize the structure of the generated graphs.
The nodes will contain minimal information.

### Numpy

Edges are stored as adjacency list with source, sink, weight (3 x |E| matrix of floats -- Scipy COO format for sparce matrix).
Nodes are stored as list of vectors of size K which depends on the type of graphs (|N| x K matrix of floats).
Multiple node representation might be generated for each graph, hence multiple files.

## Status

At the begining, we will focus on static property of the code.
Indeed the first application is to look into similarities between test codes in ROSE Compiler.
This could help identifying the source of regression when new features are added.

### First iteration

For the first iteration, the focus is put on ASTs.
The nodes are **all possible nodes** in ROSE's Internal Representation (IR).
The edges contain **any relation** between IR nodes.

### Second iteration

For the second iteration, I will various filters when generating the AST graphs.
This will enable to look more closely into different aspect of the AST:
 * code structure
 * type hierarchy
 * declaration & scope
 * ...

### Third iteration

...

