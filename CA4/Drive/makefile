CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/Handler.o: Handler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp system/System.hpp
	$(CC) $(CF) -c Handler.cpp -o $(BUILD_DIR)/Handler.o

$(BUILD_DIR)/my_server.o: ./my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c ./my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: ./main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp system/System.hpp Handler.hpp
	$(CC) $(CF) -c ./main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/System.o: system/System.cpp system/System.hpp system/User.h system/Tools.h system/Group.h system/File.h system/Directory.h system/FileSystem.h
	$(CC) -c system/System.cpp -o $(BUILD_DIR)/System.o

$(BUILD_DIR)/User.o: system/User.cpp system/User.h system/File.h system/Directory.h system/FileSystem.h
	$(CC) -c system/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Tools.o: system/Tools.cpp system/Tools.h
	$(CC) -c system/Tools.cpp -o $(BUILD_DIR)/Tools.o

$(BUILD_DIR)/Group.o: system/Group.cpp system/Group.h system/User.h
	$(CC) -c system/Group.cpp -o $(BUILD_DIR)/Group.o

$(BUILD_DIR)/File.o: system/File.cpp system/File.h system/FileSystem.h system/Directory.h
	$(CC) -c system/File.cpp -o $(BUILD_DIR)/File.o

$(BUILD_DIR)/Directory.o: system/Directory.cpp system/Directory.h system/FileSystem.h system/File.h
	g++ -c system/Directory.cpp -o $(BUILD_DIR)/Directory.o

$(BUILD_DIR)/FileSystem.o: system/FileSystem.cpp system/FileSystem.h system/Directory.h system/File.h
	g++ -c system/FileSystem.cpp -o $(BUILD_DIR)/FileSystem.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/Handler.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/System.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Tools.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Directory.o $(BUILD_DIR)/FileSystem.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/Handler.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/System.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Tools.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Directory.o $(BUILD_DIR)/FileSystem.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
