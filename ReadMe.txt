Problem statement:
The puzzle has 9 tiles, each tile has a number assigned to it, starting from 1-8. However, the 9th tile has 0 assigned to it indicating a blank tile. Given the start state and the end state the blank tile can be moved in 4 directions (up, down, left, right) one tile at a time and can be used to swap with another tile. This project uses A* algorithm which is a path finding algorithm, used to find a path with least cost to the end state.
In this project, I have used Manhattan distance to be the heuristic function. Based on the f(n) value, the algorithm finds the best possible path to the end state. The advantage of using A* is that, it has the capability to backtrack to the parent of the generated node. While, maintaining the cost of the path as well.

Program description:
I have written the code using CodeBlocks IDE.
The program takes integers to denote tiles.
The user is required to specify inputs for start and end state on command line interface.


Below is the command for compiling and executing the cpp source code in linux environment.

Compiling: gcc Krishna_assignment1.cpp
Execution: ./a.out
