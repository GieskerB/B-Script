# B-Script

__B-Script is my own programming language. It is interpreted via this C++26 program.__

## Background story

Back in spring 2024 I had to create a "Fixed-Point" class for one of my computer science courses at university. After
I got hooked and expanded the class to not only support the __+__, __-__ and __*__ operator with a fixed scaling-factor
with was set at compile time.\
Now the class supports lex_all default arithmetic operations with their assignment operator as well (e.g.: __+__
\rightarrow __+=__). Also, the scaling factor is now set at runtime, the size of a given Fixed-Point variable in Bytes
can also be chosen at runtime and these different FixedPoint object can be used in one arithmetic expression.

## Features

### Special Feature

Because of the motivation the _special feature_ of B-Script is the usage of this Fixed-Point class \underline{instead 
of} floats or double! 

### Datatypes

As a simple name for the Fixed-Point variable I chose 'dec' as in decimal number. Not to be confused with decimal as a 
base 10 number also that is true, too.

In addition to the Fixed-Point class, I have created a custom Integer class to make if easier for me to implement lex_all
the different operators. Since floats and doubles are missing, currently only two datatypes exists: int, dec (bool, str
and maybe char may follow)\
But both int and dec can be stored as a 1, 2, 4 or 8 Byte variable. This will be set by the variable type. In addition,
as written earlier, the scaling factor for the Fixed-Point class can be chosen as well.


An example of how this might look:

``` c++
    int32 a = 12345; // 
    dec32:8 x = 2.275; // A 32 Bit number with 8 Bits for the fraction part.
    dec8:2 y = 4.5; // A smaller Bit-Size and a smaller fraction part.
    dec64:60 = 0.34262334; // The very other extrem: Many Bits but most for fraction part.
```

With large fraction parts like this, dec should have way better accuracy the float or double in both directions at the
compromise of having to choose the accuracy yourself!

## Grammar

``` c++

condition   : 'if' BOOL '{' (assignment | expression) '}'

assignment  : VAR_KEYWORD[int/dec/...] IDENTIFIER '=' expression
            : IDENTIFIER '=' expression

expression  : comp-expr (('&&'|'||')comp-expr)*

comp-expr   : '!' comp_expr
              arith-expr (('=='|'!='|'<'|'<='|'>'|'>=') arith-expr)*

arith-expr  : term (('+'|'-') term)*

term        : factor (('*'|'/') factor)*

factor      : INT | DEC | BOOL | STR | IDENTIFIER
              ('+'/'-') factor
              '(' expression ')'
```

