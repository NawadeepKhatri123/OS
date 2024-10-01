#include <iostream>  // use for basic I/O functionality
#include <cstdlib>   // imports atoi
#include <string>    // to use a string


//functions
void simpletron_loadfromuser();
void simpletron_loadfromfile();
void simpletron_executeprogram();
void Dumpcore();

const int MEMORY_SIZE = 10000;
const int PAGE_SIZE = 100;
const int WORD_MIN = -999999;
const int WORD_MAX = 999999;

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



void simpletron_loadfromuser(){
    std::string input;					// input is a string while loading from the user to check whether it's GO or not ?
    int address {0};					// used for adding to memory location
    std::cout << "*** Please enter your program one instruction. \n " << std::endl;     // starts the input
    while (true){
        std::cout << address << "?" << std::endl;
        std::cin >> input;				// input basically stores the input
        if (input == "GO"){
          break;						// exit the loop if the input is GO
        }
        if (atoi(input.c_str()) < 999999 && atoi(input.c_str()) > -999999){  // atoi changes the strings to an int , and the if statement checks whether the number is in the range
           memory[address++] = atoi(input.c_str());							 // if all the conditions are met then the input is added to the sepcific meomry location
        }else{
          std::cout <<"Invalid input. Please try again.\n";					// else this
      }
    }
}

void simpletron_executeprogram(){
  bool halted = false;
  while (!halted){
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
             if (memory[operand] == 0){
               Dumpcore();
               return;
             }
             accumulator /= memory[operand];
             break;

           case DIVIDEX:
             if (memory[operand] == 0){
               Dumpcore();
               return;
             }
             accumulator /= memory[operand];
             break;

           case MULTIPLY:
             accumulator *= memory[operand];
             break;

           case MULTIPLYX:
             accumulator *= memory[index_register];
             break;

           case INC:
               index_register++;
               break;

           case DEC:
               index_register--;
               break;

           case BRANCH:
                instruction_counter = operand;


           case BRANCHNEG:
              if (accumulator < 0)
              instruction_counter = operand;

           case BRANCHZERO:
            if (accumulator == 0)
              instruction_counter = operand;

           case SWAP:
             std::swap(accumulator, index_register);
             break;

           case HALT:
             std::cout << "Program halted.\n";
                    Dumpcore();
                    halted = true;
                    break;



       }


  }
}

 void DumpCore() {
        std::cout << "REGISTERS:\n";
        std::cout << "Accumulator: " << accumulator << "\n";
        std::cout << "Instruction Counter: " << instruction_counter << "\n";
        std::cout << "Index Register: " << index_register << "\n";
        std::cout << "Instruction Register: " << instruction_register << "\n";
        std::cout << "\nMEMORY:\n";

 }