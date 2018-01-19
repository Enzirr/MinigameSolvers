#Mini-Game Solvers


I often play games, when I have some free time. These games are often simple, but as a programmer, I often start thinking about it in terms of rules and how to solve it all. It's inspiration and need to relax a bit differently, that drives me to write these solvers.
I will try to use only C++11, so they should be compilable under different OS, but I use linux and g++, so you probably need to create a new project from source under Windows (Visual Studio).


##BlockSolver - WIP

Solver for a game, where goal is to fit a set of blocks into a space. Game space is in format of uniform integer grid.
Method: Backtracking/Space Search

###Input text file format:
x y
[x times y numbers; 0 for free space -1 for blocked]
#n-of-blocks
[x y dimensions of block
x times y numbers; 0 for block body, -1 otherwise]

Program is a bit older, I'm not entirely sure about the input file or intended usage.
