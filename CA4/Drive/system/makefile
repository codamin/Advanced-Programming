all: main.cpp System.o Tools.o User.o Group.o File.o Directory.o FileSystem.o
	g++ main.cpp System.o Tools.o User.o Group.o File.o Directory.o FileSystem.o

System.o: System.cpp System.h User.h Tools.h Group.h File.h Directory.h FileSystem.h
	g++ System.cpp -c

User.o: User.cpp User.h File.h Directory.h FileSystem.h
	g++ User.cpp -c

Tools.o: Tools.cpp Tools.h
	g++ Tools.cpp -c

Group.o: Group.cpp Group.h User.h
	g++ Group.cpp -c

File.o: File.cpp File.h FileSystem.h Directory.h
	g++ File.cpp -c

Directory.o: Directory.cpp Directory.h FileSystem.h File.h
	g++ Directory.cpp -c

FileSystem.o: FileSystem.cpp FileSystem.h Directory.h File.h
	g++ FileSystem.cpp -c

clean:
	rm -f *.o *.out
