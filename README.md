# OiAK
This repository is used to publish the code I made for _Organisation and Computer Architecture_ classes.

Each catalogue is another task I had to prepare. Every `.s` file contains Assembly code in AT&T notation.

**DISCLAIMER**. These codes **might not work** nor shall be treated as a model to follow, especially those mentioned in _Previous codes_ section.

## Apr 25, 2019
Using x87 FPU. [Read more… [PL]](using-x87)
- x87-exception [[C code]](using-x87/x87-exception.c), [[asm code]](using-x87/functions.s) — raise 2 exceptions, at least one different than _divide-by-zero_ / _inv_.
- (**NOT DONE**) x87-precision [[C code]](using-x87/x87-precision.c), [[asm code]](using-x87/functions.s) — change calculations precision and show it's working on an example.
- x87-round-mode [[C code]](using-x87/x87-round-mode.c), [[asm code]](using-x87/functions.s) — change rounding mode and present it's working (explain what were the bits used to round the result (**THIS PART IS NOT DONE**)).
- (**NOT DONE**) [x87-instruction-level-parallelism](using-x87/x87-ilp.s) — write two sets of instructions such that one has many dependencies on previous results and the other has them a few. Check times.

## Apr 15, 2019
Using asm and C. [Read more… [PL]](using-asm-and-c)
- [asm-scanf-printf](using-asm-and-c/scanf-printf.s) — create an asm function that uses `scanf` and `printf` functions from C Standard Library, reading from standard input two values of types `int` and `char *`, and writing them back to stdout.
- [asm-rdtsc](using-asm-and-c/rdtsc.s), [c-rdtsc](using-asm-and-c/rdtsc.c) — create an asm function returning value returned by `rdtsc`; write a C program that will use the function and print out to standard output its output.
- (**NOT DONE**) Create C program that will use variables defined in an asm code (`short`, `char []`) and an asm program that will use C variables (`int`, `char *`).
- [asm-rdtsc-measurement](using-asm-and-c/measurement.s), [c-rdtsc-measurement](using-asm-and-c/measurement.c) — measure CPU ticks using [`rdtsc`](using-asm-and-c/rdtsc.s) for: (1) a registry operation, (2) a memory operation, (3) `write` function, (4) `printf` function.


## Apr 4, 2019
- [ascii-dec-to-bin](ascii-dec-to-bin) — (**NOT COMPLETED**) read unknown amount of unknown length records of ASCII chars representing decimal numbers, splitted by `\n`, and convert them to 255&times;8 bits (**NOT ASCII CHARS**).


## Mar 21, 2019
- [reverse-bits](reverse-bits) — read unknown amount of bytes from STDIN, reverse bits in each byte and print them on STDOUT.


## Previous codes
- [arithmetic-exceptions](arithmetic-exceptions) — create assembly functions to control ALU exceptions register (control word) and a C program to test if setting the register gives a result.
- [cpuid-cache](cpuid-cache) — check Intel processor's cache levels, its type, size and so on.
- [taylor-series-approx](taylor-series-approx) — create an assembly function approximating $log(1+x)$ with Taylor series.
- [using-sse-mmx](using-sse-mmx) — create a C and an assembly function (using SSE/MMX) that will do the same operation on two long vectors (adding, multiplying by const.); compare resulting vectors. Compare time using `rdtsc`.
