all: main.cpp Game.o functions.o Room.o Player.o Detective.o Doctor.o Vote.o Joker.o Godfather.o Silencer.o RouinTan.o Simple_villager.o Simple_mafia.o 
	g++ main.cpp Game.o functions.o Room.o Player.o Detective.o Doctor.o Joker.o Godfather.o RouinTan.o Silencer.o Simple_villager.o Simple_mafia.o Vote.o

Game.o: Game.cpp Game.h Room.h functions.h Detective.h Doctor.h Joker.h Godfather.h Silencer.h RouinTan.h Simple_villager.h Simple_mafia.h Player.h
	g++ Game.cpp -c

Room.o: Room.cpp Room.h Player.h Detective.h Doctor.h Joker.h RouinTan.h Godfather.h Silencer.h Simple_villager.h Simple_mafia.h Player.h Vote.h
	g++ Room.cpp -c

Player.o: Player.cpp Player.h
	g++ Player.cpp -c

Detective.o: Detective.cpp Detective.h Player.h
	g++ Detective.cpp -c

Doctor.o: Doctor.cpp Doctor.h Player.h
	g++ Doctor.cpp -c

Joker.o: Joker.cpp Joker.h Player.h
	g++ Joker.cpp -c

Silencer.o: Silencer.cpp Silencer.h Player.h
	g++ Silencer.cpp -c

RouinTan.o: RouinTan.cpp RouinTan.h Player.h
	g++ RouinTan.cpp -c

Godfather.o: Godfather.cpp Godfather.h Player.h
	g++ Godfather.cpp -c

Simple_villager.o: Simple_villager.cpp Simple_villager.h Player.h
	g++ Simple_villager.cpp -c

Simple_mafia: Simple_mafia.cpp Simple_mafia.h Player.h
	g++ Simple_mafia.cpp -c 

functions.o: functions.cpp functions.h Game.h Room.h
	g++ functions.cpp -c

Vote.o: Vote.cpp Vote.h
	g++ Vote.cpp -c

clean:
	rm -f *.o *.out
