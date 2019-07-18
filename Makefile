# Makefile

CC = g++
LD = g++
CCFLAGS =
LDFLAGS =
OBJ = main.o grid.o game.o controls.o player.o save.o
.SUFFIXES = .cpp .o

snake: $(OBJ)
	$(LD) $(LDFLAGS) -o snake $(OBJ)

main.cpp: main.h game.h save.h

grid.cpp: grid.h types.h

game.cpp: game.h

controls.cpp: controls.h

player.cpp: player.h

save.cpp: save.h

.cpp.o:
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f *o snake
