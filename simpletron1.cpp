#include <iostream>

//functions
void simpletron_loadfromuser();
void simpletron_loadfromfile();
void simpletron_executeprogram();
void Dumpcore();

//OPERATION CODES FOR SIMPLETRON V2
int READ = 10 ,
    WRITE = 11,
    LOAD = 20,
    LOADIM=21,
    LOADX = 22,
    LOADIDX = 23,
    STORE = 25,
    STOREIDX = 26,
    ADD = 30,
    ADDX = 31,
    SUBTRACT = 32,
    SUBTRACTX = 33,
    DIVIDE = 34,
    DIVIDEX = 35,
    MULTIPLY = 36,
    MULTIPLYX = 37,
    INC = 38,
    DEC = 39,
    BRANCH = 40,
    BRANCHNEG = 41,
    BRANCHZERO = 42,
    SWAP = 43,
    HALT = 45;

int memory[10000];			// allocating 10000 memory locations
int accumulator {};         // used to store and test values
int instruction_counter {}; // holds the address of the next instruction
int index_register {};		// contains the instruction
int instruction_register {};// for stepping through strings and arrays


// main method

int main(){
	  std::cout<< "*** Welcome to SimpleTron V2! *** \n"<< std::endl;
      std::cout<< "*** Do you have a file that conatins your SML program (Y/N) *** \n"<< std::endl;
      simpletron_loadfromuser();
}



void simletron_loadfromuser(){

}

