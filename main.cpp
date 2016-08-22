#include "kino74.hpp"

int main(int argc, char ** argv){

    kino74 myKino74;

    myKino74.initialize();

    while (1){

        myKino74.exec_cycle();
        myKino74.print_state();
    }
    
}
