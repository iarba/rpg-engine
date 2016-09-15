CC = g++

CFLAGS = -pthread

EVENTLOCATION = $(game)/events.cpp

all: rpg.run
	cp rpg.run $(game)/

rpg.run: game.o savestates.o render.o events.o
	$(CC) $(CFLAGS) -o rpg.run game.o savestates.o render.o event.o

game.o: game.cpp meta game.h savestates.h render.h events.h
	$(CC) $(CFLAGS) -c game.cpp

savestates.o: savestates.cpp meta savestates.h
	$(CC) $(CFLAGS) -c savestates.cpp

render.o: render.cpp meta render.h
	$(CC) $(CFLAGS) -c render.cpp

events.o: $(EVENTLOCATION) meta events.h
	$(CC) $(CFLAGS) -c $(EVENTLOCATION)

meta: libraries.h defines.h resource.h

clean:
	rm *.o
	rm rpg.run
