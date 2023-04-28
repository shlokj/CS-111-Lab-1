## UID: XXXXXXXXX

## Pipe Up

This program replicates the functionality of the pipe operator (|). It pipes the output of the first program into the second, the output of the second into the third, and so on until the last one.

## Building

To build the executable, simply run `make` in the folder where the Makefile and all other files are present.

## Running

This program produces output identical to that of the the pipe operator. To run this program, run `./pipe` followed by all the arguments (Linux commands you want to pipe).

Example 1: `./pipe ls cat wc`

<img width="537" alt="image" src="https://user-images.githubusercontent.com/34567765/235278919-5a5fb37c-08af-4751-adab-3157fa3e9765.png">

This checks out, because there are 8 lines printed, each with one filename, totaling 75 characters. The `cat` simply propagates the output forward in this case.

Example 2: `./pipe cal echo pwd`

<img width="577" alt="image" src="https://user-images.githubusercontent.com/34567765/235279447-070006fa-44e4-4457-9042-d25aba03f72f.png">

The `cal` output, which is `echo`'d is ignored by `pwd` since its job is to print the current working directory.

Similarly, you can pipe any (reasonable) number of arguments together.

## Cleaning up

To clean up all binary files, run `make clean`.
