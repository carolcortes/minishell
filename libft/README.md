# Libft 📚

> This is my very first project as a 42 student!
>
> Libft is all about creating my own C library, a foundational tool I will rely on throughout my journey at 42.

<details>
<summary>
  <b> Description</b>
</summary>
  This project focuses on building a strong foundation in C programming by understanding and recreating essential functions of the standard C library, as well as implementing additional utility functions. The main goals include:

- Learn how the standard library functions work under the hood.
- Build a reusable library for future projects.
- Follow strict coding norms and guidelines.
</details>
<details>
<summary>
<b>Part 1: Libc Functions</b>
</summary>

[ft_isalpha](https://github.com/carolcortes/libft/blob/main/libft/ft_isalpha.c): Checks if a character is an alphabetic letter (a-z, A-Z).

[ft_isdigit](https://github.com/carolcortes/libft/blob/main/libft/ft_isdigit.c): Checks if a character is a numeric digit (0-9).

[ft_isalnum](https://github.com/carolcortes/libft/blob/main/libft/ft_isalnum.c): Checks if a character is alphanumeric (a-z, A-Z, 0-9).

[ft_isascii](https://github.com/carolcortes/libft/blob/main/libft/ft_isascii.c): Checks if a character is part of the ASCII set (0-127).

[ft_isprint](https://github.com/carolcortes/libft/blob/main/libft/ft_isprint.c): Checks if a character is printable (includes space).

[ft_strlen](https://github.com/carolcortes/libft/blob/main/libft/ft_strlen.c): Calculates the length of a string.

[ft_memset](https://github.com/carolcortes/libft/blob/main/libft/ft_memset.c): Fills a block of memory with a specified value.

[ft_bzero](https://github.com/carolcortes/libft/blob/main/libft/ft_bzero.c): Sets a block of memory to zero.

[ft_memcpy](https://github.com/carolcortes/libft/blob/main/libft/ft_memcpy.c): Copies memory from one location to another.

[ft_memmove](https://github.com/carolcortes/libft/blob/main/libft/ft_memmove.c): Safely copies memory, allowing overlapping regions.

[ft_strlcpy](https://github.com/carolcortes/libft/blob/main/libft/ft_strlcpy.c): Copies a string to a buffer, ensuring null-termination.

[ft_strlcat](https://github.com/carolcortes/libft/blob/main/libft/ft_strlcat.c): Appends a string to a buffer, ensuring null-termination.

[ft_toupper](https://github.com/carolcortes/libft/blob/main/libft/ft_toupper.c): Converts a lowercase character to uppercase.

[ft_tolower](https://github.com/carolcortes/libft/blob/main/libft/ft_tolower.c): Converts an uppercase character to lowercase.

[ft_strchr](https://github.com/carolcortes/libft/blob/main/libft/ft_strchr.c): Finds the first occurrence of a character in a string.

[ft_strrchr](https://github.com/carolcortes/libft/blob/main/libft/ft_strrchr.c): Finds the last occurrence of a character in a string.

[ft_strncmp](https://github.com/carolcortes/libft/blob/main/libft/ft_strncmp.c): Compares two strings up to a specified length.

[ft_memchr](https://github.com/carolcortes/libft/blob/main/libft/ft_memchr.c): Finds the first occurrence of a byte in a memory block.

[ft_memcmp](https://github.com/carolcortes/libft/blob/main/libft/ft_memcmp.c): Compares two memory blocks byte by byte.

[ft_strnstr](https://github.com/carolcortes/libft/blob/main/libft/ft_strnstr.c): Locates a substring within a string, with a length limit.

[ft_atoi](https://github.com/carolcortes/libft/blob/main/libft/ft_atoi.c): Converts a string to an integer.

</details>
<details>
<summary>
<b>Part 2: Additional Functions</b>
</summary>

[ft_substr](https://github.com/carolcortes/libft/blob/main/libft/ft_substr.c): Extracts a substring from a given string.

[ft_strjoin](https://github.com/carolcortes/libft/blob/main/libft/ft_strjoin.c): Concatenates two strings into a new string.

[ft_strtrim](https://github.com/carolcortes/libft/blob/main/libft/ft_strtrim.c): Removes specified characters from the beginning and end of a string.

[ft_split](https://github.com/carolcortes/libft/blob/main/libft/ft_split.c): Splits a string into an array of substrings using a delimiter.

[ft_itoa](https://github.com/carolcortes/libft/blob/main/libft/ft_itoa.c): Converts an integer to a string.

[ft_strmapi](https://github.com/carolcortes/libft/blob/main/libft/ft_strmapi.c): Applies a function to each character of a string, creating a new string.

[ft_striteri](https://github.com/carolcortes/libft/blob/main/libft/ft_striteri.c): Applies a function to each character of a string (modifies the original string).

[ft_putchar_fd](https://github.com/carolcortes/libft/blob/main/libft/ft_putchar_fd.c): Outputs a character to a specified file descriptor.

[ft_putstr_fd](https://github.com/carolcortes/libft/blob/main/libft/ft_putstr_fd.c): Outputs a string to a specified file descriptor.

[ft_putendl_fd](https://github.com/carolcortes/libft/blob/main/libft/ft_putendl_fd.c): Outputs a string followed by a newline to a specified file descriptor.

[ft_putnbr_fd](https://github.com/carolcortes/libft/blob/main/libft/ft_putnbr_fd.c): Outputs an integer to a specified file descriptor.

</details>
<details>
<summary>
<b>Bonus: Linked List Utilities</b>
</summary>

[ft_lstnew](https://github.com/carolcortes/libft/blob/main/libft/ft_lstnew.c): Creates a new linked list node.

[ft_lstadd_front](https://github.com/carolcortes/libft/blob/main/libft/ft_lstadd_front.c): Adds a new node to the beginning of a linked list.

[ft_lstsize](https://github.com/carolcortes/libft/blob/main/libft/ft_lstsize.c): Counts the number of nodes in a linked list.

[ft_lstlast](https://github.com/carolcortes/libft/blob/main/libft/ft_lstlast.c): Returns the last node of a linked list.

[ft_lstadd_back](https://github.com/carolcortes/libft/blob/main/libft/ft_lstadd_back.c): Adds a new node to the end of a linked list.

[ft_lstdelone](https://github.com/carolcortes/libft/blob/main/libft/ft_lstdelone.c): Deletes a single node from a linked list.

[ft_lstclear](https://github.com/carolcortes/libft/blob/main/libft/ft_lstclear.c): Deletes all nodes from a linked list.

[ft_lstiter](https://github.com/carolcortes/libft/blob/main/libft/ft_lstiter.c): Iterates through a linked list and applies a function to each node.

[ft_lstmap](https://github.com/carolcortes/libft/blob/main/libft/ft_lstmap.c): Creates a new linked list by applying a function to each node of an existing list.

</details>

---

## 🚀 Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/libft.git
   cd libft
   ```
2. Build the library:
   ```bash
   make
   ```
3. Include libft.a in your C projects:
   ```c
   #include "libft.h"
   ```
4. Compile your project with the library:

   ```bash
   cc -o your_program your_program.c libft.a
   ```

   ###### Project developed by: [Carol Cortes](https://github.com/carolcortes)

   <a href = "mailto:caroline.ocortes@gmail.com"><img src="https://img.shields.io/badge/-Gmail-%23333?style=for-the-badge&logo=gmail&logoColor=white" target="_blank"></a>
   <a href="https://www.linkedin.com/in/carolinecortess/" target="_blank"><img src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white"></a>
   <div style="text-align: center;">
     <img style="width: 180px;" src="https://github.com/user-attachments/assets/213ed2f5-a2f1-4819-92e0-4346112753cb" alt="Evaluation">
   </div>
