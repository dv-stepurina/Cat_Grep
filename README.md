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

### ✔️ s21_grep
**Functionality:**
- `-e` - Pattern matching
- `-i` - Case insensitive search
- `-v` - Invert match
- `-c` - Count matching lines
- `-l` - Print matching files only
- `-n` - Show line numbers
- `-h` - Suppress filenames
- `-s` - Silent mode (suppress errors)
- `-f` - Get patterns from file
- `-o` - Print only matched parts
- Combined flags support (`-ivn`, etc.)

## Usage 
``` bash
# Cat examples
./s21_cat -n file.txt
./s21_cat -e file1.txt file2.txt

# Grep examples
./s21_grep -i "pattern" file.txt
./s21_grep -ivn "error" *.log
```

## How to use

### Important Notes for macOS Users
❗ **40+ test failures expected** on macOS due to behavior differences between:
- GNU `cat` (Linux default)
- BSD `cat` (macOS default)

**Solution**: Install GNU coreutils first:
```bash
brew install coreutils
```
### Build Instructions

1. Navigate to and build each utility:
``` bash
# For cat utility
cd src/cat/
make s21_cat

# For grep utility
cd ../grep/
make s21_grep
```

2. Run the test suite:
```bash
   make test 
 ```

3. Clean build artifacts:
```bash
   make clean 
 ```