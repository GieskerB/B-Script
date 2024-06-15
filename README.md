# B-Scrip

## Idea

My idea is to create my own programming language with my own interpreter.\
I'll use the internet to get detailed information on how to build an interpreter since I never habe build anything like that.

### Features of B-Script

I got hooked on creating a fixedpoint class from one of my computer science courses at university. In that context, we were only supposed to write a simple implementation of it.\
My goal and special for this language is us use these FixedPoint numbers instead of floating point numbers like float or double.

An example of how this might look:
´´´
dec32:8 x = 2.275; // A 32 Bit number with 8 Bits for the fraction part.
dec8:2 y = 4.5; // A smaller Bit-Size and a smaller fraction part.
dec64:60 = 0.34262334; // The very other extrem: Many Bits but most for fraction part.
´´´

With large fraction parts like this I should have way better accuracy the float or double in both directions!

### Status

Im currently done with the simple 4 arithmetic operators for int and dec as well as print.

### Design

Currently I haven't started at all with the interpreter but since i like languages like C/C++ and Java my language will be more similar to them than Python or JavaScript.
