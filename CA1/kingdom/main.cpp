#include <iostream>
#include <string>
#include <vector>
#include "rsdl.hpp"
#include "header_king.hpp"
using namespace std;

int main(int argc , char *argv[]) {

	int number_of_loops = 0;
	bool exit = false ;
	int begin_time = static_cast<double>(time(NULL));
  string filename = argv[1];
	string bg_adress;
	int chosen_strategic = -1;
	Map map;
	initialize_map(map);
  readLevelInfo(filename, map , bg_adress);

	while(!exit && map.life > 0) {
		process_events(map , exit , chosen_strategic);
		show_map(map , bg_adress);
    add_enemies(map , begin_time);
    move_enemies(map);
		towers_shoot(map , number_of_loops);
   	map.win -> update_screen();
		Delay(10);
		number_of_loops ++;
		if(waves_finished(map))
		  exit = true;
	}
	show_end_text(map);
}
