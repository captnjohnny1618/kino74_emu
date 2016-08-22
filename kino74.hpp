#include <iostream>
#include <fstream>
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

    // Memory:
    unsigned char RAM[16];

public:
    void initialize();
    void exec_cycle();
    void print_state();
    void load_program(std::string);
    void dump_ram();    
};

void kino74::initialize(){
    // Clear memory
    for (int i=0; i<16; i++){
        RAM[i]=0;
    }
    
    // Reset all registers
    PC=0;
    ACC=0;
    B=0;
    MAR=0;
    IR=0;
    OUT=0;
}

void kino74::load_program(std::string filepath){
    std::ifstream file (filepath.c_str(),std::ios::binary);    
    if (file){
        file.read((char*)RAM,16L);
    }
    else{
        std::cerr << "Program file not found." << std::endl;
        exit(1);
    }
}

void kino74::dump_ram(){
    for (int i=0;i<16;i++){
        std::cout << (int)RAM[i] << std::endl;
    }
}

void kino74::exec_cycle(){
    // Fetch Cycle (T1-T3)
    // (1) Address State (Load MAR with PC)
    MAR=PC;

    // (2) Increment state (Increment the PC)
    PC++;

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
        std::cerr << "Op code not found" << std::endl;
        exit(1);            
    }
}

using namespace std;

void kino74::print_state(){

    std::cout << "PC: " << (unsigned int)PC << std::endl;
    std::cout << "MAR: " << (unsigned int)MAR << std::endl;
    std::cout << "IR: " << (unsigned int)IR << std::endl;
    std::cout << "Accumulator: " << (unsigned int)ACC << std::endl;
    std::cout << "B: " <<  (unsigned int) B << std::endl;
    std::cout << "Out: " <<  (unsigned int) OUT << std::endl;
    std::cout << "--------------------------------" << std::endl;
        
}
