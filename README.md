<a id="top"></a>

<div align="center">
    <h3>find_path</h3>
</div>

---

### Table of Contents

- [Description](#description)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [find_path](#find_path)
    - [Valid Grid](#valid-grid)
  - [gen_grid](#gen_grid)
- [Contributing](#contributing)
- [License](#license)

---

## Description

`find_path` is a program that, given a 2D Grid composed of a starting point, an ending point, spaces and obstacles, find the shortest path between the starting point and the ending point, avoiding obstacles.

A second program, `gen_grid`, is also provided. This program generates a grid that can be used as an argument to the `find_path` program.

### Built With

[![C](https://skillicons.dev/icons?i=c&theme=light)](https://www.c-language.org/)

## Getting Started

### Installation

1. Fork the [Project repository](https://github.com/NestorNebula/find-path)
2. Clone the forked repository to your local machine
   ```
   git clone git@github.com:<your username>/<repo name>.git
   ```
3. Update remote URL

   ```
   # SSH:
   git remote add upstream git@github.com:NestorNebula/find-path.git

   # HTTPS:
   git remote add upstream https://github.com/NestorNebula/find-path.git
   ```

4. Build the programs from the project's root directory (you can precise the program's name if you only want to build one of the two programs)
   ```
   make (program)
   ```
5. Run the programs
   ```
   ./find_path (filename)
   ./gen_grid filename
   ```

## Usage

### find_path

The `find_path` program can be called with or without a filename argument.

If a filename argument is provided, the program expects that the filename exists and contains a [valid](#valid-grid) 2D Grid.

If no filename argument is provided, the program will prompt the user to enter a [valid](#valid-grid) 2D Grid.

#### Valid Grid

For a Grid to be considered valid, is must meet all the following conditions:

- Start with a `(`
- Every row must be terminated by exactly one newline character (`\n`), except for the last one, that must be terminated by a `)`
- Every other character must be a character used in one of the macros defined in the `grid.h` header.
- The START character and END character must appear exactly once in the grid.

Any grid that will not match one of these conditions will be considered as an invalid grid and rejected by the program.

A grid that is considered valid isn't necessarily a grid that can be solved. If there is no path between the starting and ending squares, the program will inform the user that the grid can't be solved.

### gen_grid

The `gen_grid` program generates a [valid grid](#valid-grid) and write it into the file given as argument. This file can then safely be used as an argument to the `find_path` program.

The program will prompt for a number of rows and cols and a percentage of obstacles.

The number of rows and cols must be between 1 and 100. They can't be both set to 1. The percentage of obstacles must be between 0 and 100.

The percentage of obstacles will have an impact on the number of obstacles that will be in the grid, but won't exactly correspond to the percentage of obstacles in the grid.

## Contributing

If you find any issue while using the program or want to contribute, please [open an issue](https://github.com/NestorNebula/find-path/issues).

## License

[![MIT License](https://img.shields.io/badge/License-MIT-darkcyan.svg?style=for-the-badge)](https://github.com/NestorNebula/find-path/blob/main/LICENSE)

© Noa Houssier - 2025

<p align='right'>(<a href='#top'>go back to the top</a>)</p>
