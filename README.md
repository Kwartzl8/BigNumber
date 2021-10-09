# BigNumber

A class that allows creation of and operations on integers with arbitrary length (maximum 36 billion digits).
For now, only positive integers are supported, and the operations are limited to addition, multiplication and exponentiation.

## How is it different from other BigNumber classes?

The number itself is a vector of components, which are 9 digit `int`s. The advantage of this approach (as opposed to storing one digit at a time), is that every operation is theoretically 9 times faster.
This is especially apparent in multiplication, where the class takes advantage of the very fast built-in multiplication algorithms for `long long` integers, and doesn't waste time cycling through individual digits.

It can find `5000!` in `36ms` and `50000!` in `3682ms` (Release, x64, Ryzen5 4600H @3.00GHz).

It also supports operations between BigNumber type objects and other (positive) integer types.

## Files included

`BigNumber.h` contains the class, `BigNumber.cpp` has the defintions of most of the functions and `BigNumberConsole.cpp` contains some code that calculates the factorial of a given number.
