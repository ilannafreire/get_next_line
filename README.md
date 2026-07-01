*This project has been created as part of the 42 curriculum by ifreire.*

# get_next_line

## Description

**get_next_line** is a C function that reads and returns one line at a time from a file descriptor. Repeated calls allow sequential reading through an entire file or standard input.

The function returns each line including its terminating `\n` character, except when the end of file is reached and the file does not end with `\n`. It returns `NULL` when there is nothing left to read or when an error occurs.

This project introduces the concept of **static variables** in C — variables that retain their value between function calls — which is the key mechanism that makes `get_next_line` possible.

**Prototype:**
```c
char *get_next_line(int fd);
```

| | |
|---|---|
| **Return value** | The line read, or `NULL` on EOF or error |
| **Allowed functions** | `read`, `malloc`, `free` |
| **Forbidden** | `lseek()`, global variables, `libft` |

---

## Instructions

### Compilation

Compile with a custom buffer size using the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The project also compiles without the flag — a default value of `42` is defined in the header:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Algorithm

### Description

The algorithm is based on a **single static string** (`stash`) that accumulates data read from the file descriptor across multiple calls.

On each call:
1. `fill_stash` reads `BUFFER_SIZE` bytes at a time with `read()`, appending each chunk to `stash`, until a `\n` is found or EOF is reached.
2. `extract_line` copies from `stash` up to and including the first `\n` (or the entire remainder if no `\n` exists), and returns it as the line.
3. `update_stash` moves whatever comes after the `\n` to a new allocation, which becomes the new `stash` for the next call. If there is nothing left, `stash` is set to `NULL`.

### Justification

This approach was chosen for the following reasons:

- **Simplicity** — a single `static char *` is enough to track state between calls. No structs, no linked lists, no extra complexity.
- **Memory efficiency** — only `BUFFER_SIZE` bytes are read per `read()` call. The file is not loaded into memory all at once.
- **Correctness at any buffer size** — because excess data is always saved in `stash`, the function works identically whether `BUFFER_SIZE` is `1`, `42`, or `10000000`.
- **No forbidden constructs** — no global variables, no `lseek()`, no `libft`.

---

## Resources

- [`read()` man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [`open()` man page](https://man7.org/linux/man-pages/man2/open.2.html)
- [`malloc()` and `free()` — cppreference](https://en.cppreference.com/w/c/memory/malloc)
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)
- [42 Norm v4 — en.norm.pdf](en.norm.pdf)

### AI Usage

AI was used during this project for the following tasks:

- Structuring and writing this README

All generated code was reviewed, understood, and validated by the author before submission.