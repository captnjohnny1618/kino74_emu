#include "kino74.hpp"

int main(int argc, char ** argv){

    kino74 myKino74;

    std::string prog_file(argv[1]);

    myKino74.initialize();
    
    myKino74.load_program(prog_file);
    
    myKino74.dump_ram();

    int pc=0;
    while (pc<16){

        myKino74.exec_cycle();
        myKino74.print_state();
        pc++;
    }
    
}
