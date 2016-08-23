CC=g++
CFLAGS=-g

kino74_emu: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

kino74_emu_curses: main2.cpp
	$(CC) $(CFLAGS) -o $@ $< -lncurses

.PHONY: clean

clean:
	rm -f kino74_emu
