ROSE's Graphs
=============

This tool aims at extracting a variety of graphs from source codes using the ROSE Compiler.
The graphs can be Abstract Syntax Tree (AST), Call Graph (CG), Control Flow Graph (CFG), and Data Flow Graph (DFG).
Outputs can be generated in GraphViz format or a Numpy format.

## Goals

The goal of this tool is to build datasets of graphs for machine-learning research.

## Licence

I give myself until the end of the first sprint to figure it out.
Probably going to be MIT Licence, CNPY code used to save Numpy array is distributed under MIT Licence.

## Outputs

### GraphViz

To permits people to visualize the structure of the generated graphs.
The nodes will contain minimal information.

### Numpy

Edges are stored as adjacency list with source, sink, weight (3 x |E| matrix of floats -- Scipy COO format for sparce matrix).
Multiple edges relationships can be captured.
Nodes are stored as list of vectors of size K which depends on the type of graphs (|N| x K matrix of floats).
Multiple node representation might be generated for each graph, hence multiple files.

## Work-plan

For the first milestone, we will focus on static property of the code.
Indeed the first application is to look into similarities between test codes in ROSE Compiler.
This could help identifying the source of regression when new features are added.

### 1st sprint

The focus is put on AST.

#### Primary AST structure

This AST will be generated through a simple traversal of ROSE's Internal Representation (IR).
The resulting graph will represent the code's (tree) structure.
Edges will be directed from childrens to parents.

#### Nodes as bit-vector

The value associated with each node will be a bit vector representing the type of node.

#### Symbol edges

Additionnal edges from symbols.

#### Type edges

Additionnal edges from types.

### 2nd sprint

At this point, I will have nodes connected by three relationships: syntax, type, and symbol.
What is the best way to express similarities using these various representations.

#### Apply to ROSE test specimens

Extracting graphs for all of ROSE test specimens.

#### Build first similarity algorithm

Given the three edges type, we need to build a graph similarity algorithm that can handle that.

## Acknowledgment

### ROSE Compiler

This graph extraction tool relies on the ROSE Compiler.
ROSE is a free, open-source (BSD Licence) framework for source-to-source compilation.
ROSE enables to write tools that leverage Abstract Syntax Tree (AST -- Internal Representation of source-code).

I have been a long time user of the ROSE Compiler.

### CNPY

[A library to read/write .npy and .npz files in C/C++.](https://github.com/rogersce/cnpy)

I have used CNPY for multiple projects where fast C/C++ is used to extract data that have to process in Python later (usually Python is used for Machine Learning).

