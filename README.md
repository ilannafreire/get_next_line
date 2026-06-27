*This project has been created as part of the 42 curriculum by ifreire.*

# get_next_line

## Description

**get_next_line** is a C function that reads a line from a file descriptor, one line at a time. Repeated calls to the function allow reading through an entire file sequentially. It is a core utility project in the 42 curriculum, designed to teach the concept of **static variables** in C and efficient file reading.

The function works with any valid file descriptor — regular files or standard input — and returns each line including its terminating `\n` character (except for the last line if the file does not end with `\n`).

**Prototype:**
```c
char *get_next_line(int fd);
```

| | |
|---|---|
| **Return value** | The line read, or `NULL` if there is nothing left to read or an error occurred |
| **Allowed functions** | `read`, `malloc`, `free` |
| **Forbidden** | `lseek()`, global variables, `libft` |

---

## Files

| File | Description |
|---|---|
| `get_next_line.c` | Main function implementation |
| `get_next_line_utils.c` | Helper functions |
| `get_next_line.h` | Header file with function prototype |

---

## Instructions

### Compilation

Compile with a custom buffer size using the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The project must also compile without the flag (a default value is set in the header):

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

The function uses a **static variable** to persist a "remainder" buffer between calls. Here's how it works:

1. **Read into buffer** — `read()` fills a temporary buffer of `BUFFER_SIZE` bytes.
2. **Append to remainder** — Each read chunk is appended to the static `remainder` string, which survives between calls.
3. **Check for newline** — After each read, the remainder is scanned for a `\n` character.
4. **Extract the line** — Once a `\n` is found (or EOF is reached), the content up to and including `\n` is extracted and returned.
5. **Update remainder** — Whatever comes after the `\n` is kept in the static variable for the next call.

**Why this approach?**

- It avoids reading the entire file into memory at once.
- It reads only as much as needed per call, respecting the `BUFFER_SIZE` constraint.
- Using a static variable is the natural solution: it retains state between calls without relying on global variables or passing extra parameters.
- The algorithm works correctly regardless of `BUFFER_SIZE` — whether it is `1`, `9999`, or `10000000` — because excess data is always stored in the remainder.

---


## Resources

- [`read()` man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [`open()` man page](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)

### AI Usage

AI was used to assist with: reviewing README structure and wording. No code was generated or copied from AI tools. All logic and implementation were developed independently following the 42 peer-learning methodology.
