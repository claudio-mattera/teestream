TeeStream
====

A C++ library for streams that output both on screen and on a file.

The code is adapted from http://wordaligned.org/articles/cpp-streambufs, with some minor modifications.


Example
----

In the following example, the string `Hello world!` is printed both on the console output and in the file `data.log`.

~~~~c++
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <teestream.h>

int main()
{
    std::ofstream log("data.log");
    teestream stream(std::cout, log);

    stream << "Hello world!" << '\n';

    return EXIT_SUCCESS;
}
~~~~


Installation
----

This library consists of a single header file [`teestream.h`](./lib/include/teestream.h).
It can also be imported as a CMake library.
