# Arcade

## Overview

Arcade is an Epitech project whose goal is emulate an arcade using display and game dynamic libaries

Contributors: Pierrick Simon, Antoine Leroy, and Ariel Amriou.

This project is compatible with other dynamic libraries who share the same architechture (Sandes Savarimuthu, Philibert Gentien, Andriamirado Ravelonahina, Maxime Kournikov, Alen Sarsen and Alex Huang).

videos

## Features

This project present the next features:
- Library modularity: it is possible to use any game library with any display library as long as it is compatible with our architecture.
- Runtime libraries changes: in the Arcade, you can change libraries at runtime with builtins commands (commands handled neither by the game nor the graphical library)

## Getting Started

### Prerequisites

This project requires the following dependencies:

- **Programming Language:** C++
- **Package Manager:** Cmake
- **Graphical Libraries:** Sfml, SDL2, NCRUSES

### Installation

Build Arcade and install dependencies:

1. **Clone the repository:**

```sh
git clone https://github.com/ArielAmriou/Arcade
```

2. **Navigate to the project directory:**

```sh
cd Arcade
```

3. **Compile:**

```sh
./cbuild setup && ./cbuild
```

### Usage

Usage:

```sh
./Arcade [.so graphical library path]
```
For exemple:

```sh
./Arcade lib/arcade_sdl2.so
```

In any game, beside game commands, the Arcade handles basics commands for any game.

- TAB: change to next graphical library
- F1: go back to menu
- F2: restart current game
- F3:  change to next game library
- F4: exit program

### Testing
Run the tests with:

```sh
./cbuild setup && ./cbuild tests_run
```
## Project organisation

```
└── 📁Arcade
    ├── 📁assets
    │   ├── 📁menu
    │   ├── 📁minesweeper
    │   ├── 📁SDL2
    │   ├── 📁SFML
    │   └── 📁snake
    ├── 📁doc
    ├── 📁include
    │   └── 📁Shared
    ├── 📁lib
    │   ├── 📁games
    │   │   ├── 📁arcade_menu
    │   │   ├── 📁arcade_minesweeper
    │   │   ├── 📁arcade_snake
    │   │   ├── 📁shared
    │   │   └── CMakeLists.txt
    │   └── 📁graphicals
    │       ├── 📁arcade_ncurses
    │       ├── 📁arcade_sdl2
    │       ├── 📁arcade_sfml
    │       └── CMakeLists.txt
    ├── 📁score
    │   └── score.csv
    ├── 📁src
    ├── 📁tests
    ├── .gitignore
    ├── cbuild
    └── CMakeLists.txt
```

## Roadmap

- ✅ **`Architechture`**: Implement architechture to accomodate runtime library changes.
- ✅ **`Arcade`**: Handle library loading, changes, and builtins.
- ✅ **`Games`**: Create the 2 required games.
- ✅ **`Menu`**: Create menu game.
- ✅ **`Graphical libraries`**: Create the 3 required graphical libraries.
- ✅ **`Documentation`**: Write developer documentation.

## Contributing

If you want to contribute to this project, you can read the documentation in ./doc/ to better understand the architecture and how to implement the required fonctionnalities for a library to work. It is advised to read ./doc/CoreDocumentation.pdf before reading game or display documentation.

---
