LIBS= -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

all:pacman

main.o: main.cpp
	g++ -I src -c main.cpp -o main.o
	
DrawMap.o: DrawMap.cpp
	g++ -I src -c DrawMap.cpp -o DrawMap.o

DrawText.o: DrawText.cpp
	g++ -I src -c DrawText.cpp -o DrawText.o

Ghost.o: Ghost.cpp
	g++ -I src -c Ghost.cpp -o Ghost.o

GhostManager.o: GhostManager.cpp
	g++ -I src -c GhostManager.cpp -o GhostManager.o

Pacman.o: Pacman.cpp
	g++ -I src -c Pacman.cpp -o Pacman.o

ConvertSketch.o: ConvertSketch.cpp
	g++ -I src -c ConvertSketch.cpp -o ConvertSketch.o

MapCollision.o: MapCollision.cpp
	g++ -I src -c MapCollision.cpp -o MapCollision.o

pacman: MapCollision.o ConvertSketch.o Pacman.o GhostManager.o Ghost.o DrawText.o DrawMap.o main.o
	@echo "** Building the game"
	g++ -o pacman MapCollision.o ConvertSketch.o Pacman.o GhostManager.o Ghost.o DrawText.o DrawMap.o main.o $(LIBS)
	
clean:
	@echo "** Removing object files and executable..."
	rm -f pacman *.o

install:
	@echo '** Installing...'
	cp pacman /usr/bin

uninstall:
	@echo '** Uninstalling...'
	rm -f /usr/bin/pacman