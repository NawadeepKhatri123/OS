#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Function declarations
void simpletron_loadfromuser();
void simpletron_readfromuser();
void simpletron_executeprogram();
void Dumpcore();

const int MEMORY_SIZE = 10000;
const int WORD_MIN = -999999;
const int WORD_MAX = 999999;

// OPERATION CODES FOR SIMPLETRON V2
enum codes {
    READ = 10,
    WRITE = 11,
    LOAD = 20,
    LOADIM = 21,
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
    HALT = 45
};

int memory[MEMORY_SIZE] = {}; // Allocating memory locations
int accumulator = 0;           // Used to store and test values
int instruction_counter = 0;   // Holds the address of the next instruction
int index_register = 0;        // Contains the instruction
int instruction_register = 0;  // For stepping through instructions

// Main method

int main() {
    char ans;                                                                // ans is a initialized char
    std::cout << "*** Welcome to SimpleTron V2! *** \n" << std::endl;
    std::cout << "*** Do you have a file that contains your SML program (Y/N) ***  :";
    std::cin >> ans;                                                         // stores the response in char
    if (ans == 'y' || ans == 'Y') {
        simpletron_readfromuser();                                            // reads from a file if ans = y
    }else{
        simpletron_loadfromuser();                                           // read from the console
    }
    simpletron_executeprogram();
}


// this method reads if the user wishes to procced with a .sml file

void simpletron_readfromuser(){
  std::string filename;                                    // declare a variable to store filename
  std::cout<<" Please enter your file name : ";
  std::cin >> filename;

  std::ifstream MyFile(filename);                       //ifstream apprently reads the file

  if (!MyFile){
       std::cout<<"File does not exist!\n";            // this if statement is supposed to check whether the file has been opened properly or not
       return;
  }

  int count {0};                                      // this count is used for travesing  through the meomory locations

  while (MyFile >> memory[count]){                    // stores the contents of the file in the memory
    count++;
  }
}

// this method is initalized if the user wishes to enter the sml program through his own hands
void simpletron_loadfromuser() {
    std::string input;
    int address = 0;
    std::cout << "*** Please enter your program one instruction. \n" << std::endl;

    while (true) {
        std::cout << "000" << address << "  ?    "; // Prints the memory location
        std::cin >> input;
        if (input == "GO") {
            break;
        }

        int instruction = atoi(input.c_str());

        // Check if address is valid and instruction is in range
        if (address >= 0 && address < MEMORY_SIZE && instruction >= WORD_MIN && instruction <= WORD_MAX) {
            memory[address++] = instruction; // Store instruction

        } else {
            std::cout << "Invalid input. Please try again.\n";                             // Handle invalid input
        }
    }
}

void simpletron_executeprogram() {
    bool halted = false;

    while (!halted) {
        instruction_register = memory[instruction_counter++];
        int opcode = instruction_register / 10000;
        int operand = instruction_register % 10000;



        switch (opcode) {
            case READ:
                std::cout << "Enter a word: ";
                std::cin >> memory[operand];
                break;

            case WRITE:
                std::cout << "Word: " << memory[operand] << std::endl;
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
                if (memory[operand] == 0) {
                    std::cout << "Error: Division by zero.\n";
                    Dumpcore();
                    halted = true;
                } else {
                    accumulator /= memory[operand];
                }
                break;

            case DIVIDEX:
                if (memory[index_register] == 0) {
                    std::cout << "Error: Division by zero.\n";
                    Dumpcore();
                    halted = true;
                } else {
                    accumulator /= memory[index_register];
                }
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
                break;

            case BRANCHNEG:
                if (accumulator < 0) {
                    instruction_counter = operand;
                }
                break;

            case BRANCHZERO:
                if (accumulator == 0) {
                    instruction_counter = operand;
                }
                break;

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

void Dumpcore() {
    std::cout << "REGISTERS:\n";
    std::cout << "Accumulator: " << accumulator << "\n";
    std::cout << "In struction Counter: " << instruction_counter << "\n";
    std::cout << "Index Register: " << index_register << "\n";
    std::cout << "Instruction Register: " << instruction_register << "\n";
    std::cout << "\nMEMORY:\n";

    for (int i = 0; i < 30; ++i) {
        std::cout << "000" << i << ": " << memory[i];
    }
}
