C = gcc
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
OBJS = tool/AsciiArtTool.o RLEList.o tool/main.o

AsciiArtTool : $(OBJS)
	$(CC) $(OBJS) -o $@
tool/main.o : tool/main.c tool/AsciiArtTool.h RLEList.h tool/AsciiArtTool.c 
	$(CC) -c -I. $(COMP_FLAG) $*.c -o $*.o
tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h RLEList.c
	$(CC) -c -I. $(COMP_FLAG) $*.c -o $*.o
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) AsciiArtTool
