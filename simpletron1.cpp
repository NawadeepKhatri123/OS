#include <iostream>  // use for basic I/O functionality
#include <cstdlib>   // imports atoi
#include <string>    // to use a string

//functions
void simpletron_loadfromuser();
void simpletron_loadfromfile();
void simpletron_executeprogram();
void Dumpcore();

//OPERATION CODES FOR SIMPLETRON V2
enum codes{
    READ = 10 ,
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
    HALT = 45};

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
      simpletron_executeprogram();
}



void simletron_loadfromuser(){
    std::string input;
    int address {0};
    std::cout << "*** Please enter your program one instruction. \n " << std::endl;
    while (true){
        std::cout << "Enter your instruction : "<<std::endl;
        std::cin >> input;
        if (input == "GO"){
          break;
        }
        if (atoi(input.c_str()) < 999999 && atoi(input.c_str()) > -999999){
           memory[address++] = atoi(input.c_str());
        }else{
          std::cout <<"Invalid input. Please try again.\n";
      }
    }
}

void simpletron_executeprogram(){
  bool halt = false;
  while (!halt){
      instruction_register = memory[instruction_counter++];
      int opcode = instruction_register / 10000;
      int operand = instruction_register % 10000;

      switch (opcode) {
          case READ:
            std::cout << " Enter a word :  ";
            std::cin >> memory[operand];
            break;

          case WRITE:
            std::cout << "Word" << memory[operand] << std::endl;
            break;

           case LOAD:
             accumulator = memory[operand];
             break;

           case LOADIM:
             accumulator = operand;
             break;

           case LOADX:
             index_register = memory[operand];
             break;

           case LOADIDX:
             accumulator = memory[index_register];
             break;

           case STORE:
            memory[operand] = accumulator;
            break;

           case STOREIDX:
            memory[index_register] = accumulator;
            break;

           case ADD:
             accumulator += memory[operand];
             break;

           case ADDX:
             accumulator += memory[index_register];
             break;

           case SUBTRACT:
             accumulator -= memory[operand];
             break;

           case SUBTRACTX:
            accumulator -= memory[index_register];
            break;

           case DIVIDE:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case DIVIDEX:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case MULTIPLY:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case MULTIPLYX:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case INC:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case DEC:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case BRANCH:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case BRANCHNEG:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case BRANCHZERO:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case SWAP:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;
           case HALT:
            std::cout << " Enter a word ";
            std::cin >> memory[operand];
            break;


       }


  }
}