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
    std::cout << "RAM contents for loaded program:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    for (int i=0;i<16;i++){
        //        std::cout << (int)RAM[i] << std::endl;
        int op_code=RAM[i] >> 4;
        int address=RAM[i] & 0x0F;

        std::cout << i << ": " << (int)op_code << "   " << (int)address <<  std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void kino74::exec_cycle(){
    // Fetch Cycle (T1-T3)
    // ----------------------------------------
    // (1) Address State (Load MAR with PC)
    MAR=PC;

    // (2) Increment state (Increment the PC)
    PC=(PC+1)%16;

    // (3) Memory State (load IR with RAM[MAR])
    IR=RAM[MAR];
    
    // Execution Cycle (T4-T6)
    // ----------------------------------------
    // Extract op code
    unsigned char op_code=(IR >> 4);
    // Extract second half of instruction (Address target if used)
    unsigned char address=IR & 0x0F;
    
    switch (op_code){
    // LDA
    case 0x00:
        //T4 (Mem address from IR to MAR)
        MAR=address;
        //T5 (Grab data from RAM, store in ACC)
        ACC=RAM[MAR];
        //T6 (NoOp)        
        break;
    // ADD
    case 0x01:
        //T4 (Mem address from IR to MAR)
        MAR=address;
        //T5 (Grab data from RAM, store in B reg.)
        B=RAM[MAR];
        //T6 (Add contents of ACC and B and store in ACC)
        ACC=ACC+B;
        break;
    // SUB
    case 0x02:
        //T4 (Mem address from IR to MAR)
        MAR=address;
        //T5 (Grab data from RAM, store in B reg.)
        B=RAM[MAR];
        //T6 (Subtract contents of B from ACC and store in ACC)
        ACC=ACC-B;
        break;        
    // OUT
    case 0x0e:
        //T4 (Put contents of ACC on OUT)
        OUT=ACC;
        //T5 (NoOp)
        //T6 (NoOp)
        break;        
    // HLT
    case 0x0f:
        //No execution cyle
        //HLT stops clock, so here we'll just exit
        exit(0);
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
