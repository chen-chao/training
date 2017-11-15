# coursera

## INTRO

coursera contains the programming assignments of classes(not
restricted to coursera, though), including:

* [C程序设计](https://www.coursera.org/learn/c-chengxu-sheji/)

Introduction to C programming in Chinese on coursera, held by 
[Ge Li](https://www.coursera.org/instructor/ligechina).  However, the
assignment is compiled with `g++`. Assignment descriptions are in the
source file or in another seperated file.

* [The C Programming Language](http://clc-wiki.net/wiki/K%26R2_solutions) 

K&M's *The C Programming Language* exercises. At most times 
[the answers on the clc-wiki](http://clc-wiki.net/wiki/K%26R2_solutions)
are refered when the exercise is finished, and useful hints or code
snippets are jotted down. Though the book obeys the ansi C standard,
the exercises use gcc default standard, except sometimes(like 
[Chapter 4](./tcpl/chapter_4)), where "-ansi" option must be specified when
compiling, to avoid conflict function name `getline` defined in
`stdio.h`. At most time, if there are more than one source file, a
makefile will be provided.

