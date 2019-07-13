#include <string>
#include "rsdl.hpp"
using namespace std;


#define RETURN 13
#define A      97
#define C      99
#define M      109
#define I      105

#define PI     3.14

#define WIN_START_POINT 0
#define WIN_SIZE 800
#define WIN_TEXT "KINGDOM RUSH"

#define INFO_PNG_ADDRESS "./assets/info.png"
#define INFO_X    5
#define INFO_Y    5
#define INFO_WIDTH   200
#define INFO_HEIGHT   100

#define TOWER_SHOOT_RANGE 85

#define NUM_OF_STRATEGICS 8
#define MAP_MONEY  220
#define MAP_LIFE   15

#define SEC_PER_MIN 60

#define LIFE_TEXT_X  30
#define LIFE_TEXT_Y  20

#define MONEY_TEXT_X 30
#define MONEY_TEXT_Y 45

#define FONT_SIZE 30
#define FONT_ADDRESS "./assets/BLKCHCRY.TTF"

#define BULLET_IMAGE_ADRESS "./assets/bullet.png"
#define BULLET_VELOCITY 200

#define END_WIN_TEXT   "****YOU WIN!****"
#define END_LOOSE_TEXT "****YOU LOOSE!****"
#define END_TEXT_X 300
#define END_TEXT_Y 300

#define DELAY            10 //ms
#define STRATEGIC_RADIUS 30
#define RADIUS           20

#define ARMORED_LIFE      450
#define ARMORED_VELOCITY  21
#define ARMORED_KILLPOINT 8
#define ARMORED_DAMAGE    3

#define ORC_LIFE          200
#define ORC_VELOCITY      42
#define ORC_KILLPOINT     5
#define ORC_DAMAGE        1

#define DEMON_LIFE        400
#define DEMON_VELOCITY    28
#define DEMON_KILLPOINT   8
#define DEMON_DAMAGE      3

#define WOLF_LIFE         100
#define WOLF_VELOCITY     85
#define WOLF_KILLPOINT    4
#define WOLF_DAMAGE       1

#define ARCHER_DAMAGE              50
#define ARCHER_COST                70
#define ARCHER_SHOOT_RATE          700
#define ARCHER_PHYSICAL_ATTACK     1
#define ARCHER_MAGICAL_ATTACK      0

#define CANON_DAMAGE              140
#define CANON_COST                125
#define CANON_SHOOT_RATE          2000
#define CANON_PHYSICAL_ATTACK     1
#define CANON_MAGICAL_ATTACK      0

#define MAGE_DAMAGE              140
#define MAGE_COST                90
#define MAGE_SHOOT_RATE          1500
#define MAGE_PHYSICAL_ATTACK     0
#define MAGE_MAGICAL_ATTACK      1

#define ICY_DAMAGE              30
#define ICY_COST                80
#define ICY_SHOOT_RATE          2000
#define ICY_PHYSICAL_ATTACK     0
#define ICY_MAGICAL_ATTACK      1


#define ARCHER_IMG_ADDRESS "./assets/towers/archer.png"
#define MAGE_IMG_ADDRESS   "./assets/towers/mage.png"
#define CANON_IMG_ADDRESS  "./assets/towers/canon.png"
#define ICY_IMG_ADDRESS    "./assets/towers/icy.png"

#define ENEMY_FOLDER       "./assets/enemies/"

#define ADJUST_X 60
#define ADJUST_Y 70

#define ENEMY_SIZE  50
#define BULLET_SIZE 20
#define TOWER_SIZE  100
#define END_DELAY 5000

#define SOUND_ADDRESS "canberra-gtk-play -f  ./assets/shoot.wav"

struct Enemy{
  string type;
	float x;
	float y;
	int life;
	int velocity;
	int killPoint;
	int damage;
	string direction;
	int segment;
  bool physical_armor;
  bool magical_armor;
  bool arrived_deffence_point;
};

struct Bullet{
	float x;
	float y;
  bool is_hit;
};

struct Tower{
  string type;
  int damage;
  int cost;
	int x;
	int y;
	Enemy *locked_enemy;
  int shoot_rate;  //ms
  bool physical_attack;
  bool magical_attack;
	vector<Bullet> bullets;
};

struct Time{
	int minute;
	int second;
};

struct Attacker
{
 int number;
 string type;
};

struct Attack{
Time time;
vector<Attacker> attackers;
bool happened;
};

struct Wave{
vector<Attack> attacks;
};

struct Map{
  int money;
  int life;
	Window *win;
  string initial_direction;
	vector<Wave> waves;
	vector<Tower> towers;
	vector<Enemy> enemies;
	vector<int> path_x;
	vector<int> path_y;
  vector<int> strategic_x;
  vector<int> strategic_y;
};

void initialize_map(Map &map);
void show_life_money(Map &map);
void show_map(Map &map , string bg_adress);
void add_new_attack(vector<Wave> &level_wavesList,int wave_number,string newAttack);
void read_strategic_points( vector<int> &strategic_x , vector<int> &strategic_y , ifstream& inputFile);
void readLevelInfo (string filename , Map &map , string &bg_adress);
void read_waves(ifstream &inputFile , Map &map);
void add_wave(vector<Wave> &level_wavesList);
vector<string> split(string newAttack , char splitter );
Time add_time(string attack_time);
vector<Attacker> add_attackers(vector<string> splitted_new_attack);
void initialize_archer(Tower &tower , int x , int y);
void initialize_canon(Tower &tower , int x , int y);
void initialize_mage(Tower &tower , int x , int y);
void initialize_icy(Tower &tower , int x , int y);
void process_events(Map &map , bool &exit , int &chosen_strategic);
void add_enemies(Map &map , int begin_time);
void add_enemy(Map &map ,Attacker attacker);
Enemy make_armored(int initial__x , int initial_y , string initial_direction);
Enemy make_orc(int initial__x , int initial_y , string initial_direction);
Enemy make_demon(int initial__x , int initial_y , string initial_direction);
Enemy make_wolf(int initial__x , int initial_y , string initial_direction);
void add_tower(Map &map , int pressedKey , int strategic_num);
int which_strategic(int x , int y , vector<int> strategic_x ,vector<int> strategic_y );
int convert_to_second(Time time);
void show_towers(Map &map);
void show_enemies(Map &map);
void move_enemies(Map &map);
void move_in_lines(Enemy &enemy , Map &map , float randomized_x , float randomized_y);
void move_in_curves(Enemy &enemy , Map &map , float randomized_x , float randomized_y);
float calculate_angle(float dy , float dx );
void increase( float &x , float &y , float dx , float dy);
float calculate_movement(float dt , float velocity); // dt in ms
void hit_bullet(Enemy *enemy , Bullet &bullet , Tower &tower , Map &map , int last_bullet_idx);
void move_in_segment(Enemy &enemy , Map &map);
float distance(float x0 , float y0 , float x1 , float y1);
void turn_enemy(Enemy &enemy, float dx ,float dy);
void turn_dx_pos(Enemy &enemy, float dx ,float dy);
void turn_dx_neg(Enemy &enemy, float dx ,float dy);
void show_bullets(vector<Bullet> bullets , Map &map);
void move_bullets(Tower &tower, Map &map);
void shoot_bullet(Tower &tower , Map &map , int number_of_loops);
void playsound();
void towers_shoot(Map &map , int number_of_loops);
void tower_shoot(Tower &tower , Map &map , int number_of_loops);
void individual_damage(int damage , Enemy *enemy , Tower tower);
void group_damage(Tower &tower , vector<Enemy> &enemies);
void make_damage(Enemy *enemy , Tower &tower , Map &map);
bool waves_finished(Map map);
int total_enemies(Map map);
void show_end_text(Map &map);
