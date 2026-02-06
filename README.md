\# CS240 Streaming Service (C)

A simplified streaming service backend implemented in C.  

The project simulates user registration, movie management, and watch history using hash tables and binary search trees.

Developed as a university programming assignment.

\# Features

1)User registration via hash table
2)Movie storage per category using BSTs
3)Personal watch history per user (BST)
4)Event-driven execution through input files
5)Sentinel nodes for efficient searching

\# Project Structure

.

main.c # Input parsing and event handling
Movie.c # Core implementation
Movie.h # Data structures \& prototypes
Makefile
README.md

\## Build
```bash

make

Produces:

cs240StreamingServicePhaseb

Run

./cs240StreamingServicePhaseb input.txt

Example:

./cs240StreamingServicePhaseb tests.txt

Clean

make clean

Input Format

Each line represents an event:

R <userID> //Register

A <category> <movieID> //Add

W <userID> <category> <movieID> <score> //Watch

U <userID> //User stats
P //Print all

Implementation Notes

Users stored in a hash table with chaining

Movies organized per category using binary search trees

Each user maintains a BST-based watch history

Technologies

C,(GCC),Make,Linux

Author:Manousos Kymionis
