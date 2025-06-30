# Simple Bash Utils (cat & grep in C)

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
| `make`         | Build only the implementation (in current folder) |
| `make test`    | Run the test suite (in current folder)            |
| `make clean`   | Remove all build artifacts  (in current folder)   |


## How to use

### Prerequisites
- GCC compiler (≥ 9.3.0 recommended)
- GNU Make (≥ 4.3)
- PCRE2 library (for grep functionality)
- Git (for cloning repository)

### Important Notes for macOS Users
❗ **40+ test failures expected** on macOS due to behavior differences between:
- GNU `cat` (Linux default)
- BSD `cat` (macOS default)

**Solution**: Install GNU coreutils first:
```bash
brew install coreutils
# Use gcat for testing reference
make test TEST_CMD=gcat
```
### Installation Steps

1. Clone the repository:
```bash
   git clone https://github.com/dv-stepurina/Cat_Grep.git
   cd simple-bash-utils
```

2. Navigate to and build each utility:
``` bash
# For cat utility
cd src/cat/
make s21_cat

# For grep utility
cd ../grep/
make s21_grep
```

3. Run the test suite:
```bash
   make test 
 ```

4. Clean build artifacts:
```bash
   make clean 
 ```