# Simple Bash Utils (cat & grep in C)

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![License](https://img.shields.io/badge/license-MIT-blue)]()

POSIX-compliant implementations of `cat` and `grep` utilities written in C.

## Features

### ✔️ s21_cat
- Supports all standard and GNU flags:
  - `-b`/`--number-nonblank` - Number non-empty lines
  - `-e` - Display `$` at end of lines
  - `-n`/`--number` - Number all output lines
  - `-s`/`--squeeze-blank` - Suppress repeated empty lines
  - `-t` - Display tabs as `^I`
- Multiple file input support
- Binary-safe file handling

### ✔️ s21_grep
**Core functionality:**
- `-e` - Pattern matching
- `-i` - Case insensitive search
- `-v` - Invert match
- `-c` - Count matching lines
- `-l` - Print matching files only
- `-n` - Show line numbers

**Extended features:**
- `-h` - Suppress filenames
- `-s` - Silent mode (suppress errors)
- `-f` - Get patterns from file
- `-o` - Print only matched parts
- Combined flags support (`-ivn`, etc.)

## Installation

```bash
git clone https://github.com/yourusername/simple-bash-utils.git
cd simple-bash-utils
make
```
## Usage 
``` bash
# Cat examples
./s21_cat -n file.txt
./s21_cat -e file1.txt file2.txt

# Grep examples
./s21_grep -i "pattern" file.txt
./s21_grep -ivn "error" *.log
```
## Build Commands

### Available Make Targets

| Command          | Description                          |
|------------------|--------------------------------------|
| `make s21_cat`   | Build only the `cat` implementation  |
| `make s21_grep`  | Build only the `grep` implementation |
| `make all`       | Build both utilities                 |
| `make test`      | Run the test suite                   |
| `make clean`     | Remove all build artifacts           |

## Project Structure
src/
├── cat/        # Cat implementation
├── common/     # Shared utilities
├── grep/       # Grep implementation
tests/          # Test cases
Makefile        # Build configuration

## How to use

### Prerequisites
- GCC compiler (≥ 9.3.0 recommended)
- GNU Make (≥ 4.3)
- PCRE2 library (for grep functionality)
- Git (for cloning repository)

### Installation Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/dv-stepurina/Cat_Grep.git
   cd simple-bash-utils
   ```
2. Build the utilities:
```bash
   make all
 ```
3. Run the test suite:
```bash
   test 
 ```
4. Clean build artifacts:
```bash
   clean 
 ```