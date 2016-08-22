#include <iostream>
#include <cstdlib>

class kino74{
    
    // Registers:
    unsigned char ACC;
    unsigned char B;
    unsigned char MAR;
    unsigned char IR;
    unsigned char OUT;

    // Counters:
    unsigned char PC;
    unsigned char RING;

    // Memory:
    unsigned char RAM[16];

public:
    void initialize();
    void exec_cycle();
    void print_state();
};

void kino74::initialize(){
    // Clear memory
    for (int i=0; i<16; i++){
        RAM[i]=0;
    }
    
    // Reset Program and Ring Counter
    PC=0;
    RING=0;
}

void kino74::exec_cycle(){
    // Fetch Cycle (T1-T3)
    // (1) Address State (Load MAR with PC)
    MAR=PC;

    // (2) Increment state (Increment the PC)
    PC+=1;

    // (3) Memory State (load IR with RAM[MAR])
    IR=RAM[MAR];

    // Execution Cycle (T4-T6)
    // Exract op code
    unsigned char op_code=(IR >> 4);
    switch (IR){
    // LDA
    case 0x0:
        break;
    // ADD
    case 0x1:
        break;
    // SUB
    case 0x2:
        break;        
    // OUT
    case 0xe:
        break;        
    // HLT
    case 0xf:
        break;

    default:
        std::cout << "Op code not found" << std::endl;
        exit(1);            
    }
}

using namespace std;

void kino74::print_state(){

    // Registers:
    unsigned char ACC;
    unsigned char B;
    unsigned char MAR;
    unsigned char IR;
    unsigned char OUT;

    // Counters:
    unsigned char PC;
    unsigned char RING;

    // Memory:
    unsigned char RAM[16];

    std::cout << "PC: " << (unsigned int)IR << std::endl;
    std::cout << "MAR: " << (unsigned int)MAR << std::endl;
    std::cout << "IR: " << (unsigned int)IR << std::endl;
    std::cout << std::endl;
    std::cout << "Accumulator: " << (unsigned int)ACC << std::endl;
    std::cout << "B: " <<  (unsigned int) B << std::endl;



    

}
