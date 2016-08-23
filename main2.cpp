#include "kino74.hpp"
#include <bitset>
#include <curses.h>
#include <unistd.h>

void update_register_vis(kino74 k, WINDOW * win);
void draw_4bitword(unsigned char w, int y, int x, WINDOW * win);
void draw_8bitword(unsigned char w, int y, int x, WINDOW * win);

int main(int argc, char ** argv){

    kino74 myKino74;

    std::string prog_file(argv[1]);

    myKino74.initialize();
    myKino74.load_program(prog_file);

    // Initialize visualization
    WINDOW *mainwin, *viswin, *ramwin;
    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }

    //noecho();
    //keypad(mainwin, TRUE);

    // Create our subwindows
    // Register visualization
    int height=12;
    int width=22;
    viswin=subwin(mainwin,height,width,0,0);
 
    box(viswin, 0, 0);
    mvwaddstr(viswin, 1, 1, "PC:");
    mvwaddstr(viswin, 3, 1, "ACC:");
    mvwaddstr(viswin, 3, 11,"MAR:");
    mvwaddstr(viswin, 6, 1, "B:");
    mvwaddstr(viswin, 6, 11,"IR:");
    mvwaddstr(viswin, 9, 6, "Out:");

    refresh();

    int hlt=0;
    while (!hlt){
        hlt=myKino74.exec_cycle();
        //myKino74.print_state();
        update_register_vis(myKino74,viswin);
        //wrefresh(viswin);
        sleep(2);
    }

    delwin(ramwin);
    delwin(viswin);
    delwin(mainwin);
    endwin();
    refresh();
}

void update_register_vis(kino74 k,WINDOW * viswin){
    // Update program counter
    draw_4bitword(k.PC,1,5,viswin);
    draw_8bitword(k.ACC,4,2,viswin);
    draw_8bitword(k.B,7,2,viswin);
    draw_8bitword(k.OUT,10,7,viswin);
    draw_4bitword(k.MAR,4,14,viswin);
    draw_8bitword(k.IR,7,12,viswin);
    wrefresh(viswin);
}

void draw_4bitword(unsigned char w,int y,int x,WINDOW * win){
    // Part to be draw should be in the lower four bits of our char
    std::bitset<8> bits(w);
    std::string s=bits.to_string().substr(4);
    mvwaddstr(win,y,x,s.c_str());
    //mvwaddstr(win,y,x,bits.to_string().c_str());
}
void draw_8bitword(unsigned char w,int y,int x,WINDOW * win){
    std::bitset<8> bits(w);
    mvwaddstr(win,y,x,bits.to_string().c_str());    
}
