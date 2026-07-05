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

### Bonus

The bonus version extends the function to support **multiple file descriptors simultaneously**. Reading from fd 3, then fd 4, then back to fd 3 does not lose the reading state of any descriptor. It is implemented using a single static array `str[OPEN_MAX]`, where each index corresponds to a file descriptor — preserving the one-static-variable constraint.

---

## Instructions

### Compilation

**Mandatory part** — compile with a custom buffer size using the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Also compiles without the flag — a default value of `42` is defined in the header:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

**Bonus part** — same flags, using the `_bonus` files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
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

**Bonus — multiple file descriptors:**

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    line = get_next_line(fd1); printf("%s", line); free(line);
    line = get_next_line(fd2); printf("%s", line); free(line);
    line = get_next_line(fd1); printf("%s", line); free(line);
    close(fd1);
    close(fd2);
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

### Bonus Algorithm

The bonus version replaces `static char *str` with `static char *str[OPEN_MAX]`. Each position in the array maps directly to a file descriptor number, so the leftover buffer after each `
` is stored and retrieved per fd independently. All internal helper functions (`ft_append`, `cut`, `ft_freethis`) remain identical — only the access pattern changes from `&str` to `&str[fd]`. This satisfies both bonus requirements: one static variable and simultaneous multi-fd support.

---

## Resources

- [`read()` man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [`open()` man page](https://man7.org/linux/man-pages/man2/open.2.html)
- [`malloc()` and `free()` — cppreference](https://en.cppreference.com/w/c/memory/malloc)
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)

### AI Usage

AI was used during this project for the following tasks:

- Structuring and writing this README

All generated code was reviewed, understood, and validated by the author before submission.