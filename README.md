# Get Next Line 📄✏️

## Project Overview 🛠️

This project is about creating a C function named `get_next_line` that reads from any file or input stream **line by line** — making file reading easier, cleaner, and more efficient.

The core idea is simple but powerful: given a **file descriptor**, `get_next_line` will return **one line of text** every time it’s called. It keeps returning lines sequentially until there are no more lines left to read.

---

The function reads data **incrementally** from the provided file descriptor and returns exactly one line on each call. A “line” here means a sequence of characters that ends either with a newline character (`\n`) or the end of the file.
If the newline is present, it’s included in the returned string.

Unlike reading the entire file into memory at once — which can be inefficient or even impossible for very large files — `get_next_line` reads only as much as needed to return the current line.
This behavior makes it memory-friendly and ideal for reading large files or streams, such as logs, network inputs, or user input.

For example, if you write a loop that calls `get_next_line(fd)`, each iteration returns the next line in the file, until the function returns `NULL`.
This `NULL` indicates either the end of the file has been reached or an error occurred during reading.

---

## What is a File Descriptor? 🧩

A **file descriptor** is a low-level integer identifier used by the operating system to manage and access files and other I/O resources (like pipes or terminals).

When you open a file or receive input, the OS assigns a file descriptor to that resource. Programs don’t usually interact with files by name internally; instead, they use these descriptors to perform operations such as reading, writing, or closing.

Commonly, file descriptors 0, 1, and 2 correspond to **standard input** (`stdin`), **standard output** (`stdout`), and **standard error** (`stderr`), respectively.

In this project, the `get_next_line` function reads data from whatever file descriptor is passed to it — whether that’s a file on disk, input from the keyboard, or data coming through a pipe or socket.

---

## Key Aspects ✨

- **Use of Static Variables 🔄:**  
  The function cleverly uses static variables to keep track of leftover data from previous reads. This means that if a line is partially read in one call, the remaining part is saved for the next call, ensuring no data is lost between calls.

- **Dynamic Memory Management 💾:**  
  Each line returned is dynamically allocated with just enough space to hold the characters read. Proper memory handling is essential to avoid leaks and ensure that memory is freed once the data is no longer needed.

- **Direct File Descriptor Handling 🖥️:**  
  The function interfaces directly with the `read` system call, giving low-level control over reading files, pipes, or standard input streams. This helps to efficiently manage how much data is read at a time.

- **Configurable Buffer Size ⚙️:**  
  The size of the internal read buffer is controlled via a compile-time macro called `BUFFER_SIZE`. This allows adjusting the buffer size for performance tuning depending on the environment or file size.

- **Robustness and Error Handling 🚧:**  
  The implementation gracefully handles edge cases like empty lines, end-of-file detection, and possible read errors, preventing crashes or undefined behavior.

- **Modular Design 🧩:**  
  The code is organized clearly, separating the main function and helper utilities into different files. This promotes maintainability, readability, and reuse.

- **Versatility 🌍:**  
  Works with any file descriptor, whether reading from normal files, standard input, or other input sources — making it a highly flexible function for many different applications.
