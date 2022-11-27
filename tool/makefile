CC = gcc
COMP_FLAG = -std=c99 -Wall -Werror
OBJS = AsciiArtTool.o ../RLEList.o

AsciiArtTool : $(OBJS)
	$(CC) $(OBJS) -o $@
main.o : main.c AsciiArtTool.h ../RLEList.h AsciiArtTool.c AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h ../RLEList.h ../RLEList.c
	$(CC) -c $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(COMP_FLAG) $*.c
