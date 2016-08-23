CC=g++
CFLAGS=-g

kino74_emu: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f kino74_emu
