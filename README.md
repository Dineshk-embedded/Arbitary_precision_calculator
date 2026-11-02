# APC – Arbitrary Precision Calculator

A command-line calculator in C that performs **addition, subtraction, multiplication and division on integers of any size**, far beyond the range of `int` or `long long`. Each number is stored digit by digit in a **doubly linked list**, and the arithmetic is done the way you do it on paper.

## Features

- Add, subtract, multiply and divide numbers with no fixed digit limit
- Supports negative operands (`-99 - 1`, `-5 x 4`, `+7 + 3`)
- Leading zeros are handled (`007` is read as `7`), and `-0` is treated as `0`
- Input validation (non-digit characters, empty operands) and division-by-zero detection
- All dynamically allocated memory is freed after every operation
- Runs repeatedly: asks `Want to continue?` after each calculation

## Build

Requires `gcc` and `make`.

```bash
make          # builds APC.out
make clean    # removes object files and binary
```

## Usage

```bash
./APC.out <operand1> <operator> <operand2>
```

| Operator | Operation      |
|----------|----------------|
| `+`      | Addition       |
| `-`      | Subtraction    |
| `x` / `X`| Multiplication |
| `/`      | Division (integer quotient) |

> Use `x` for multiplication, because `*` is expanded by the shell. Operands are plain digit strings with an optional leading `+` or `-`.

### Examples

```
$ ./APC.out 123 + 456
Operand 1 = 123
Operand 2 = 456

      Addition
Result = 579

$ ./APC.out 99999999999999999999 x 99999999999999999999
Result = 9999999999999999999800000000000000000001

$ ./APC.out -99 - 1
Result = -100

$ ./APC.out 1000 / 7
Result = 142

$ ./APC.out 5 / 0
ERROR : Division by zero
```

## How it works

Each digit is a node in a doubly linked list:

```c
typedef struct node {
    struct node *prev;
    int data;           // one digit, 0-9
    struct node *next;
} Dlist;
```

| Operation | Approach |
|-----------|----------|
| Addition | Walk both lists from the tail (least significant digit), add digit by digit with carry |
| Subtraction | Digit-wise subtraction with borrow; the larger magnitude is always placed first |
| Multiplication | Multiply by each digit of operand 2, shift, and accumulate partial products |
| Division | Long division: bring down one digit at a time and repeatedly subtract the divisor from the running remainder (max 9 times per digit) |
| Signs | `main.c` strips the sign, runs the operation on magnitudes, then works out the result sign. `a - b` is computed as `a + (-b)` |

## Project structure

```
APC/
├── main.c            # driver: argument parsing, sign handling, menu loop
├── apc.h             # Dlist definition and function prototypes
├── function.c        # list helpers: create, print, insert, compare, free, strip zeros
├── addition.c
├── subtraction.c
├── multiplication.c
├── division.c
└── Makefile
```

## Limitations

- Integers only; division returns the **quotient** (truncated), not a decimal result
- Division is repeated subtraction, so it is slower on very large inputs than an optimized algorithm
- Requires exactly three command-line arguments

## Concepts demonstrated

Doubly linked lists, dynamic memory management, pointer-to-pointer parameters, modular multi-file C projects, Makefiles, and input validation.

## Author

Dinesh (DK) – Embedded Systems student, Bangalore
