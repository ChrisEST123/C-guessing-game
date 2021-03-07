Main: Main.o encryption.o Gamer.o Manager.o Person.o
	g++ Main.o encryption.o Gamer.o Manager.o Person.o -o Main
Main.o:Main.cpp
	g++ -c Main.cpp
encryption.o:encryption.cpp
	g++ -c encryption.cpp
Gamer.o:Gamer.cpp
	g++ -c Gamer.cpp
Manager.o:Manager.cpp
	g++ -c Manager.cpp
Person.o:Person.cpp
	g++ -c Person.cpp

clean:
	rm *.o Main