# Triangular Solitaire Solver

This project implements an AI-based solution to the **Triangular Peg Solitaire** game using **heuristic search** and **genetic algorithms**. It supports modular heuristics and provides infrastructure for analyzing solver performance.

## 🧩 Game Overview

Triangular Solitaire is a single-player puzzle game where the goal is to eliminate all but one peg by jumping one peg over another into an empty space, similar to checkers. The challenge lies in selecting the right sequence of moves.

## 🚀 Features

- **Heuristic-based search**, multiple heuristic strategies supported (distance to center, number of isolated pegs, etc.)
- **Genetic algorithm solver**, evolves strategies over generations using weighted heuristics.
- **Modular and extensible architecture**, easily add new heuristics or solvers.
- **C++20** standard using CMake for build management.
- **Efficient board representation** uses **bitboards** for compact and fast manipulation of board state.