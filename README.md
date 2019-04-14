# OiAK
This repository is used to publish the code I made for _Organisation and Computer Architecture_ classes.

Each catalogue is another task I had to prepare. Every `.s` file contains Assembly code in AT&T notation.

**DISCLAIMER**. These codes **might not work** nor shall be treated as a model to follow, especially those mentioned in _Previous codes_ section.

## Apr 4, 2019
- [ascii-dec-to-bin](ascii-dec-to-bin) — (**NOT COMPLETED**) read unknown amount of unknown length records of ASCII chars representing decimal numbers, splitted by `\n`, and convert them to 255&times;8 bits (**NOT ASCII CHARS**).


## Mar 21, 2019
- [reverse-bits](reverse-bits) — read unknown amount of bytes from STDIN, reverse bits in each byte and print them on STDOUT.


## Previous codes
- [arithmetic-exceptions](arithmetic-exceptions) — create assembly functions to control ALU exceptions register (control word) and a C program to test if setting the register gives a result.
- [cpuid-cache](cpuid-cache) — check Intel processor's cache levels, its type, size and so on.
- [taylor-series-approx](taylor-series-approx) — create an assembly function approximating $log(1+x)$ with Taylor series.
- [using-sse-mmx](using-sse-mmx) — create a C and an assembly function (using SSE/MMX) that will do the same operation on two long vectors (adding, multiplying by const.); compare resulting vectors. Compare time using `rdtsc`.