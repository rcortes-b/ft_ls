# ft_ls

> A recreation of the Unix `ls` command in C

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Resources](#resources)

## 🎯 About

**ft_ls** is a project that reimplements the classic Unix `ls` command. This project provides deep insight into file system interactions, directory traversal, and data structure management in C programming.

The goal is to recreate the behavior of `ls` with several of its most commonly used options, while maintaining identical output formatting to the original command.

## ✨ Features

### Mandatory Options

- **`-l`** - Long format listing (detailed file information)
- **`-R`** - Recursive listing of subdirectories
- **`-a`** - Show hidden files (entries starting with `.`)
- **`-r`** - Reverse order while sorting
- **`-t`** - Sort by modification time (newest first)

### Bonus Options (Optional)

- **`-u`** - Use time of last access instead of modification
- **`-f`** - Do not sort; enable `-a` option
- **`-g`** - Long format without owner name
- **`-d`** - List directories themselves, not their contents
- **`-G`** - Colorized output
- ACL and extended attributes support
- Multi-column format without `-l`
- Performance optimization for large directories

## 🛠️ Requirements

- **Language**: C
- **Compiler**: gcc or clang
- **Make**: GNU Make
- **OS**: Unix-based system (Linux, macOS)

### Allowed Functions

```c
write()
opendir()
readdir()
closedir()
stat()
lstat()
getpwuid()
getgrgid()
listxattr()
getxattr()
time()
ctime()
readlink()
malloc()
free()
perror()
strerror()
exit()
```

## 🚀 Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd ft_ls
```

2. Compile the project:
```bash
make
```

3. (Optional) Clean object files:
```bash
make clean
```

4. (Optional) Remove all generated files:
```bash
make fclean
```

5. (Optional) Recompile everything:
```bash
make re
```

## 💻 Usage

### Basic Usage

```bash
./ft_ls [options] [file ...]
```

### Examples

List files in current directory:
```bash
./ft_ls
```

Long format listing:
```bash
./ft_ls -l
```

Show hidden files:
```bash
./ft_ls -a
```

Recursive listing:
```bash
./ft_ls -R
```

Sort by modification time in reverse:
```bash
./ft_ls -ltr
```

Multiple directories:
```bash
./ft_ls -la /etc /var /tmp
```

## 🏗️ Implementation Details

### Key Concepts

1. **File System Interaction**
   - Understanding directory structures
   - Reading file metadata using `stat()` and `lstat()`
   - Handling symbolic links with `readlink()`

2. **Data Structures**
   - Efficient storage of file information
   - Linked lists or arrays for file entries
   - Sorting algorithms (merge sort, quick sort recommended)

3. **Memory Management**
   - Dynamic memory allocation for file entries
   - Proper cleanup to prevent memory leaks
   - Valgrind testing for leak detection

4. **Formatting**
   - Column alignment for long format
   - Date formatting with `ctime()`
   - Permissions parsing and display
   - User/group name resolution

### Important Considerations

- **Recursive Design**: The `-R` option requires careful planning from the start
- **Error Handling**: Match `ls` behavior for error cases
- **Sorting**: Implement stable sorting for multiple criteria
- **Performance**: Optimize for large directories (bonus)

## 📁 Project Structure

```
ft_ls/
├── Makefile
├── README.md
├── includes/
│   └── ft_ls.h
├── srcs/
│   ├── main.c
│   ├── parsing.c
│   ├── display.c
│   ├── sorting.c
│   ├── file_info.c
│   └── utils.c
├── libft/
│   ├── Makefile
│   ├── libft.h
│   └── ...
└── ft_ls (executable)
```

## 🧪 Testing

### Basic Tests

```bash
# Compare with system ls
ls -l > system_output.txt
./ft_ls -l > my_output.txt
diff system_output.txt my_output.txt

# Test various combinations
./ft_ls -laRt
./ft_ls -lR /usr/include
./ft_ls -la /etc /var /tmp
```

### Edge Cases

- Empty directories
- Files without read permissions
- Symbolic links
- Very large directories
- Special files (devices, sockets, pipes)
- Files with unusual characters in names

### Memory Testing

```bash
# Check for memory leaks
valgrind --leak-check=full ./ft_ls -lRa /path/to/directory

# Check for errors
valgrind --track-origins=yes ./ft_ls -l
```

## 📚 Resources

### Manual Pages

```bash
man ls
man opendir
man readdir
man stat
man lstat
man getpwuid
man getgrgid
```

### Useful Links

- [GNU Coreutils - ls](https://www.gnu.org/software/coreutils/manual/html_node/ls-invocation.html)
- [File permissions in Unix](https://en.wikipedia.org/wiki/File-system_permissions)
- [Understanding stat structure](https://linux.die.net/man/2/stat)

## 📝 Notes

- The project emphasizes proper code structure and organization
- Consider edge cases and error handling from the beginning
- Test thoroughly against the system `ls` command
- Use your libft to make implementation easier (especially `ft_printf`)

## ⚠️ Common Pitfalls

1. **Not planning for `-R` early**: Recursive functionality needs careful design
2. **Memory leaks**: Always free allocated memory, especially in recursive calls
3. **Incorrect sorting**: Multiple sort criteria (time + alphabetical) must work together
4. **Formatting issues**: Padding and alignment must match system `ls`
5. **Error handling**: Must handle invalid paths, permission errors gracefully

## 🎓 Learning Outcomes

- Deep understanding of Unix file systems
- System programming in C
- Working with system calls and library functions
- Memory management and optimization
- Code organization and project structure
- Algorithm implementation (sorting, traversal)

## This README is AI generted :)