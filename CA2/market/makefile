all:User.o Store.o Good.o Factor.o Factor_Good.o Request.o Request_Good.o functions.o  main.cpp
	g++ main.cpp User.o Store.o Good.o Factor.o Factor_Good.o Request.o Request_Good.o functions.o
User.o:User.cpp header.h User.h
	g++ User.cpp -c
Store.o:Store.cpp Store.h header.h User.h Good.h Request_Good.h Request.h Factor_Good.h Factor.h functions.h
	g++ Store.cpp -c
Good.o:Good.cpp Good.h header.h
	g++ Good.cpp -c
Factor.o:Factor.cpp Factor.h header.h
	g++ Factor.cpp -c
Factor_Good.o:Factor_Good.cpp Factor_Good.h header.h
	g++ Factor_Good.cpp -c
Request.o:Request.cpp Request.h header.h
	g++ Request.cpp -c
Request_Good.o:Request_Good.cpp Request_Good.h header.h
	g++ Request_Good.cpp -c
functions.o:functions.cpp functions.h header.h Store.h Good.h
	g++ functions.cpp -c
clean:
	rm -f *.o *.out
