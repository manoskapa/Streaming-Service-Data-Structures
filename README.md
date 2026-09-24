# Streaming Service – Data Structures in C

A simplified movie streaming service written in C. The program reads a file of events (register a user, add a movie, watch it, rate it and so on) and runs each one against hand-written data structures.

University assignment for CS-240 Data Structures, University of Crete. It is built on the course skeleton, which provides the event parser in `main.c` and the function signatures.

## Data structures

| Data | Structure |
|---|---|
| Users | Hash table with chaining |
| New releases | Binary search tree, filled as movies are added |
| Movies by category | One balanced BST per category, built from a sorted array, with a sentinel node for fast search |
| Watch history | Leaf-oriented BST per user |
| Filtering by score | Heap sort over the movies rated at or above a threshold |

## Events

| Event | Format | Action |
|---|---|---|
| `R` | `R <userID>` | Register a user |
| `U` | `U <userID>` | Unregister a user |
| `A` | `A <movieID> <category> <year>` | Add a new release |
| `D` | `D` | Distribute new releases into their category trees |
| `W` | `W <userID> <category> <movieID> <score>` | Watch and rate a movie |
| `F` | `F <userID> <score>` | List movies rated at or above a score, sorted by rating |
| `Q` | `Q <userID>` | Show a user's average score |
| `I` | `I <movieID> <category>` | Search for a movie |
| `M` | `M` | Print all movies by category |
| `P` | `P` | Print the users hash table |

## Build and run

Requires `gcc` and `make` (Linux or WSL).

```sh
cd main-phase02
make
./cs240StreamingServicePhaseb testfiles-phase02/u10_a_50_all_events.txt
```

The `testfiles-phase02` folder contains event files of different sizes, from 5 to 400 users.
