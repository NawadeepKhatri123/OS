#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>


// Function declarations
void simpletron_loadfromuser();
void simpletron_readfromuser();
void simpletron_executeprogram();
void Dumpcore();

const int MEMORY_SIZE = 10000;
const int WORD_MIN = -999999;
const int WORD_MAX = 999999;
int opcode;
int operand;

// OPERATION CODES FOR SIMPLETRON V2//set of named constants
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
        opcode = instruction_register / 10000;                                // retrives the first 2 digits of the input
        operand = instruction_register % 10000;                               // retrives the last 2 digits of the input



        switch (opcode) {
            case READ:
                std::cout << "Enter a word: ";
                std::cin >> memory[operand];                            // store the input entered in the terminal to memory location specified by the operand
                break;

            case WRITE:
                std::cout << "Word: " << memory[operand] << std::endl;        // displays the output in the console from the memory location specified by the operand
                break;

            case LOAD:
                accumulator = memory[operand];                                // acc holds the value in the memory location specified by the operand
                break;

            case LOADIM:
                accumulator = operand;                                        // acc points at the address of the operand
                break;

            case LOADX:
                index_register = memory[operand];                               // the index register holds the value in the memory location specified by the operand
                break;

            case LOADIDX:
                accumulator = memory[index_register];                            // accumulator holds the value from the memory location specified by the index register
                break;

            case STORE:
                memory[operand] = accumulator;                                    // memory holds the value of the accumulator in the location specified by the operator
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
                if (memory[operand] == 0) {                                        // checks if the divisor is 0 if it is 0, then the core is dumped
                    std::cout << "Error: Division by zero.\n";
                    Dumpcore();
                    halted = true;
                } else {
                    accumulator /= memory[operand];
                }
                break;

            case DIVIDEX:
                if (memory[index_register] == 0) {
                    std::cout << "Cannot divide by zero.\n";
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
                index_register++;                            //increase the index register by one
                break;

            case DEC:
                index_register--;                            //decrease the index register by one
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
            default:
                std::cerr << "Error: Invalid operation code " << opcode << ".\n";
                Dumpcore();
                exit(1);

        }
    }
}

void Dumpcore() {
    std::cout << "\n*** DUMP CORE ***\n\n";

    // Display registers
    std::cout << "REGISTERS:\n";
    std::cout << "---------------------------------\n";
    std::cout << "Accumulator          : " << accumulator << "\n";
    std::cout << "Instruction Counter   : " << instruction_counter << "\n";
    std::cout << "Index Register        : " << index_register << "\n";
    std::cout << "Operation Code        : " << opcode << "\n";
    std::cout << "Operand               : " << operand << "\n";
    std::cout << "---------------------------------\n";

    std::cout << "\n\nMEMORY:\n";

    // print coulumn
    for(int col = 0; col < 10;col++){
           std::cout<<std::setw(7) << col;
    }
    std::cout<<'\n';
    // Display memory
    for (int row = 0; row < 10; row++) { // 10 rows for 100 memory locations
        std::cout << (row * 10); // Row index
        std::cout << " "; // Space after row index

        for (int col = 0; col < 10; col++) {
            int index = row * 10 + col;

            // Ensure we only display up to the first 100 locations
            if (index >= 100) {
                break;
            }

            // Format memory value as a zero-padded string
            std::string value = std::to_string(memory[index]);
            while (value.length() < 6) { // Ensure it's at least 6 characters long
                value = "0" + value; // Prepend zeros
            }

            std::cout << value; // Output the formatted memory value
            std::cout << " "; // Space between values
        }

        std::cout << "\n";
    }
}

