# OS

SimpleTron V2
Overview
SimpleTron V2 is an educational interpreter for a fictional assembly language. It allows users to load and execute programs using a specific set of operations.

Features
Load programs from user input or .sml files.
Execute various operations including arithmetic, branching, and I/O.
Display register and memory states during execution.
Usage
Run the Program:


Execute the program.
Input Options:

Indicate if you have a .sml file (Y/N).
If yes, enter the filename. If no, enter instructions manually and type GO to finish.
Operation Codes

Code	Operation	Description
10	READ	  Input a word into memory
11	WRITE	  Output a word from memory
20	LOAD	  Load a value into the accumulator
30	ADD	    Add a value from memory
45	HALT	  Stop program execution

Error Handling
The program checks for invalid inputs, file errors, and division by zero, providing feedback and dumping the current state for debugging.

