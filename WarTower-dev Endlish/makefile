WarTower.exe:main.o launcher.o game.o my_rand.o
	g++ main.o launcher.o game.o my_rand.o -o WarTower
main.o:main.cpp console.h launcher.h my_rand.h
	g++ -c main.cpp -std=c++11
launcher.o:launcher.cpp launcher.h console.h game.h my_rand.h
	g++ -c launcher.cpp -std=c++11
game.o:game.cpp game.h console.h my_rand.h
	g++ -c game.cpp -std=c++11
my_rand.o:my_rand.cpp my_rand.h
	g++ -c my_rand.cpp -std=c++11