# OS
# Nawadeep Khatri (5086950)

SimpleTron V2
---------------------------------------------------------------------------------------------------------------------
Overview

SimpleTron V2 is a simulator interpreter for the programs written in a language called Simpletron Machine language.
It allows users to load and execute programs using a specific set of operations.
---------------------------------------------------------------------------------------------------------------------
Features
Load programs from user input or .sml files.
Memory consists of 10000 words broken up into 100 pages each holding 100 words.
Execute various operations including arithmetic, branching, and I/O.
Display register and memory states during execution.
---------------------------------------------------------------------------------------------------------------------
How I built a executable .sml file

The first .sml file is to find the greatest common divisor given two positive integer using the Euclidean algorithm.
-First you input 2 integers using the READ operation code and specifiy which memory location you would want it to be 
 stored at.
-Then you load the first input into the accumulator using the LOAD operation code then using the SUBTRACT operation
code subtract the second input from the accumulator and store it in the accumulator.
-After subtraction using the BRANCHZERO operation code which checks if the accumulator is zero and if TRUE branches 
to line 16 in the code.
-If the condition is FALSE then the program continues and using the value in the accumulator and the BRANCHNEG
operation code we find out if a is smaller than b . If it is true then the program branches to line 12 . 
-If the value is a non-negative then the value from the accumulator is put into the first memory location and returns 
back to line 4 which subtracts the first and the second input.
-In the case where the second input is larger than the first input, the second input is loaded into the accumulator
and using the SUBTRACT operation code the value is stored in accumulator and the second inputs value is changed to 
that in the accumulator.
-The process repeats until the first and the second variable subtracted is zero.
-When the result is zero it branches to line 16 where the value of a or the first input is displayed in the terminal.
-The program is then finally halted.

*** Do you have a file that contains your SML program (Y/N) ***  :y
Please enter your file name : first1.sml
Enter a word: 48
Enter a word: 18
Word: 6
Program halted.

*** DUMP CORE ***

REGISTERS:
---------------------------------
Accumulator          : 0
Instruction Counter   : 18
Index Register        : 0
Operation Code        : 45
Operand               : 0
---------------------------------


MEMORY:
0      1      2      3      4      5      6      7      8      9
0 100020 110020 100021 110021 200020 320021 420016 200020 320021 410012
10 250020 400004 200021 320020 250021 400004 110020 450000 000000 000000
20 000006 000006 000000 000000 000000 000000 000000 000000 000000 000000
30 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
40 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
50 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
60 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
70 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
80 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000
90 000000 000000 000000 000000 000000 000000 000000 000000 000000 000000


---------------------------------------------------------------------------------------------------------------------
Execute the program.

To execute the program you first have to compile the .cpp code. If you are using a Console you can type in the 
following command :

$ g++ -o simpletron simpletron.cpp

and after to execute the file or if you already hold the executable file type the following command :

$ ./simpletron.cpp

After the program runs you will be promted with:

Indicate if you have a .sml file (Y/N).
If yes, enter 'y' or 'Y' and enter the filename. 
If no, enter instructions manually and type GO to finish.
--------------------------------------------------------------------------------------------------------------------



Error Handling
The program checks for invalid inputs, file errors, and division by zero, providing feedback and dumping the current 
state for debugging.

