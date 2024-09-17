# 42-Get-Next-Line

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation](#implementation)

## Introduction

A [42 School](https://www.42network.org/) project to retrieve the next line from a given file descriptor.

## Installation

Git clone the repository:

```shell
https://github.com/TimHopg/42-Get-Next-Line.git
```

A `main.c` is included with various tests and edge cases as well as a variety of `txt` files.

## Usage

No `makefile` with this project. The function can be utilised within your own project.

Compile as follows:  
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=n [files].c`

Where `n` can be a buffer size of your choice. If not `BUFFER-SIZE` is set, the value in the header file is used.

## Implementation

Initially I utilised linked lists to undertake this project but it's both unnecessary and not an optimal solution. The single allowed static variable is sufficient to store the buffer string and a dynamically allocated string can be used to read from the file. A secondary logic has been adapted in `logic2` based on Laher Wenceslau Payot Maciel's work, which is more streamlined but has some limitations when sending invalid file descriptors.
