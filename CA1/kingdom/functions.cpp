#include <iostream>
#include <vector>
#include <fstream>
#include "rsdl.hpp"
#include <time.h>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include "header_king.hpp"
using namespace std;


void initialize_map(Map &map){
  map.money = MAP_MONEY;
  map.life = MAP_LIFE;
  map.win = new Window(WIN_SIZE, WIN_SIZE , WIN_TEXT );
}

void show_life_money(Map &map) {
  string life,money;
  stringstream convert1,convert2;
  convert1 << map.life;
  life = "life    : " + convert1.str();
  convert2 << map.money;
  money = "money   : " + convert2.str();
  map.win -> draw_png(INFO_PNG_ADDRESS , INFO_X , INFO_Y , INFO_WIDTH , INFO_HEIGHT);
  map.win -> show_text(life , LIFE_TEXT_X , LIFE_TEXT_Y , GREEN , FONT_ADDRESS , FONT_SIZE);
  map.win -> show_text(money , MONEY_TEXT_X , MONEY_TEXT_Y , GREEN , FONT_ADDRESS , FONT_SIZE);
}

void show_map(Map &map , string bg_adress) {
  map.win -> draw_png(bg_adress , WIN_START_POINT , WIN_START_POINT , WIN_SIZE,WIN_SIZE);
  show_life_money(map);
  show_towers(map);
  show_enemies(map);
}

vector<string> split(string to_be_splitted , char splitter) {
  vector<string> substrings;
  int char_iterator = 0 ;
  while(char_iterator < to_be_splitted.size()) {
  	string sub;
  	while(to_be_splitted[char_iterator] != splitter && char_iterator < to_be_splitted.size()) {
  		sub.push_back(to_be_splitted[char_iterator]);
  		char_iterator ++;
    }
   	substrings.push_back(sub);
    char_iterator ++;
  }
  return substrings;
 }

Time add_time(string attack_time) {
	vector<string> splittedTime = split(attack_time , ':');
	Time time;
  time.minute = atoi( splittedTime[0].c_str() );
  time.second = atoi( splittedTime[1].c_str() );
  return time;
}

vector<Attacker> add_attackers(vector<string> splitted_new_attack) {
  vector<Attacker> attackers;
  for(int part = 1 ; part < splitted_new_attack.size() ; part++) {
  int number = atoi( split(splitted_new_attack[part],'x')[0].c_str() );
  string type = split(splitted_new_attack[part] , 'x')[1].substr(1);
  type.pop_back();
  Attacker attacker = { number , type };
  attackers.push_back(attacker);
  }
  return attackers;
}

void add_enemy(vector<Wave> &level_wavesList,int wave_number,string newAttack) {
  vector<string>  splitted_new_attack = split ( newAttack , ',');
  Time time = add_time(splitted_new_attack[0]);
  vector<Attacker> attackers = add_attackers(splitted_new_attack);
  Attack new_attack = { time , attackers , 0};
	level_wavesList[wave_number].attacks.push_back(new_attack);
}

void add_new_attack(vector<Wave> &level_wavesList , int wave_number , string newAttack) {
  vector<string>  splitted_new_attack = split ( newAttack , ',');
  Time time = add_time(splitted_new_attack[0]);
  vector<Attacker> attackers = add_attackers(splitted_new_attack);
  Attack new_attack = { time , attackers , 0};
  level_wavesList[wave_number].attacks.push_back(new_attack);
}

void add_wave(vector<Wave> &waves) {
	Wave newWave;
	waves.push_back(newWave);
}

void read_strategic_points( vector<int> &strategic_x , vector<int> &strategic_y , ifstream &inputFile) {
  string line;
  getline(inputFile , line);
  for(int point = 0 ; point < split(line , ',') .size() ; point ++ )
      strategic_x.push_back(atoi(split(line , ',')[point].c_str()));

  getline(inputFile , line);
  for(int point = 0 ; point < split(line , ',').size() ; point ++ )
      strategic_y.push_back(atoi(split(line , ',')[point].c_str()));
}

void read_path_points( vector<int> &path_x , vector<int> &path_y , ifstream &inputFile) {
  string line;
  getline(inputFile , line);
  for(int point = 0 ; point < split(line , ',') .size() ; point ++ )
      path_x.push_back(atoi(split(line , ',')[point].c_str()));
  getline(inputFile , line);
  for(int point = 0 ; point < split(line , ',').size() ; point ++ )
      path_y.push_back(atoi(split(line , ',')[point].c_str()));
}

void read_waves(ifstream &inputFile , Map &map) {
  string line;
  int wave_number = -1;
  while(getline(inputFile,line)) {
        if(line == "\r")
          continue;
        if(line.substr(0,4) == "wave" ) {
          wave_number ++;
  		   	add_wave(map.waves);
  		   }
  		else {
  			 string newAttack = line;
  			 add_new_attack(map.waves , wave_number , newAttack);
  		}
  }
}

void readLevelInfo (string filename , Map &map , string &bg_adress) {
  ifstream inputFile(filename.c_str());
  read_strategic_points(map.strategic_x , map.strategic_y , inputFile);
  read_path_points(map.path_x , map.path_y , inputFile);
  inputFile >> bg_adress;
  inputFile >> map.initial_direction;
  read_waves(inputFile , map);
}

void process_events(Map &map , bool &exit , int &chosen_strategic) {
  Event last_event = map.win -> pollForEvent();
  if(last_event.type() == KEY_PRESS) {
    if(last_event.pressedKey() == RETURN )
       exit = true;
    else if(last_event.pressedKey() == A || last_event.pressedKey() == M ||
            last_event.pressedKey() == C || last_event.pressedKey() == I){
           if(chosen_strategic != -1)
             add_tower(map , last_event.pressedKey() , chosen_strategic);
         }
  }
  if(last_event.type() == LCLICK) {
    chosen_strategic = which_strategic(last_event.mouseX() , last_event.mouseY() , map.strategic_x , map.strategic_y);
  }
}

void add_enemies(Map &map , int begin_time) {
  int elapssed_time = static_cast<double>(time(NULL)) - begin_time;
  for(int wave_num = 0 ; wave_num < map.waves.size() ; wave_num ++) {
    for(int attack_num = 0 ; attack_num < map.waves[wave_num].attacks.size() ; attack_num++) {
      if(elapssed_time >= convert_to_second(map.waves[wave_num].attacks[attack_num].time)) {
        if(!map.waves[wave_num].attacks[attack_num].happened) {
          for(int attacker_num = 0 ; attacker_num < map.waves[wave_num].attacks[attack_num].attackers.size() ; attacker_num ++ )
             add_enemy(map , map.waves[wave_num].attacks[attack_num].attackers[attacker_num]);
        map.waves[wave_num].attacks[attack_num].happened = 1;
        }
      }
    }
  }
}

void add_enemy(Map &map ,Attacker attacker) {
  string type = attacker.type;
  for(int number = 0 ; number < attacker.number ; number ++) {
      Enemy enemy;
      if(type == "armored")
        enemy = make_armored(map.path_x[0] , map.path_y[0] , map.initial_direction);
      else if(type == "orc")
        enemy = make_orc(map.path_x[0] , map.path_y[0] , map.initial_direction);
      else if(type == "demon")
        enemy = make_demon(map.path_x[0] , map.path_y[0] , map.initial_direction);
      else if(type == "wolf")
        enemy = make_wolf(map.path_x[0] , map.path_y[0] , map.initial_direction);

      map.enemies.push_back(enemy);
  }
}

Enemy make_armored(int initial__x , int initial_y , string initial_direction) {
  Enemy enemy = { "armored" , float(initial__x) , float(initial_y) , ARMORED_LIFE ,
  ARMORED_VELOCITY , ARMORED_KILLPOINT , ARMORED_DAMAGE , initial_direction , 0 , 1 , 0 , 0};
  return enemy;
}

Enemy make_orc(int initial__x , int initial_y , string initial_direction) {
  Enemy enemy = { "orc" , float(initial__x) , float(initial_y) , ORC_LIFE ,
  ORC_VELOCITY , ORC_KILLPOINT , ORC_DAMAGE , initial_direction , 0 , 0 , 0 , 0};
  return enemy;
}

Enemy make_demon(int initial__x , int initial_y , string initial_direction) {
  Enemy enemy = { "demon" , float(initial__x) , float(initial_y) , DEMON_LIFE ,
    DEMON_VELOCITY , DEMON_KILLPOINT , DEMON_DAMAGE, initial_direction , 0 , 0 , 1 , 0};
  return enemy;
}

Enemy make_wolf(int initial__x , int initial_y , string initial_direction) {
  Enemy enemy = { "wolf" , float(initial__x) , float(initial_y) , WOLF_LIFE ,
   WOLF_VELOCITY , WOLF_KILLPOINT , WOLF_DAMAGE , initial_direction , 0 , 0 , 0 , 0};
  return enemy;
}

int which_strategic(int x , int y , vector<int> strategic_x ,vector<int> strategic_y) {
  for(int point_num = 0 ; point_num < NUM_OF_STRATEGICS ; point_num ++) {
    if(distance(x , y , strategic_x[point_num] , strategic_y[point_num] ) < STRATEGIC_RADIUS)
      return point_num;
  }
  return -1;
}

void initialize_archer(Tower &tower , int x , int y) {
  tower.type = "archer";
  tower.x = x;
  tower.y = y;
  tower.damage = ARCHER_DAMAGE;
  tower.cost = ARCHER_COST;
  tower.shoot_rate = ARCHER_SHOOT_RATE;
  tower.physical_attack = ARCHER_PHYSICAL_ATTACK ;
  tower.magical_attack =  ARCHER_MAGICAL_ATTACK;
  tower.locked_enemy = NULL;
}

void initialize_canon(Tower &tower , int x , int y) {
  tower.type = "canon";
  tower.x = x;
  tower.y = y;
  tower.damage = CANON_DAMAGE;
  tower.cost = CANON_COST;
  tower.shoot_rate = CANON_SHOOT_RATE;
  tower.physical_attack = CANON_PHYSICAL_ATTACK ;
  tower.magical_attack =  CANON_MAGICAL_ATTACK;
  tower.locked_enemy = NULL;
}

void initialize_mage(Tower &tower , int x , int y) {
  tower.type = "mage";
  tower.x = x;
  tower.y = y;
  tower.damage = MAGE_DAMAGE;
  tower.cost = MAGE_COST;
  tower.shoot_rate = MAGE_SHOOT_RATE;
  tower.physical_attack = MAGE_PHYSICAL_ATTACK ;
  tower.magical_attack =  MAGE_MAGICAL_ATTACK;
  tower.locked_enemy = NULL;
}

void initialize_icy(Tower &tower , int x , int y) {
  tower.type = "icy";
  tower.x = x;
  tower.y = y;
  tower.damage = ICY_DAMAGE;
  tower.cost = ICY_COST;
  tower.shoot_rate = ICY_SHOOT_RATE;
  tower.physical_attack = ICY_PHYSICAL_ATTACK ;
  tower.magical_attack =  ICY_MAGICAL_ATTACK;
  tower.locked_enemy = NULL;
}

void add_tower(Map &map , int pressedKey ,int strategic_num) {
  Tower new_tower;
  if(pressedKey == A)
    initialize_archer(new_tower , map.strategic_x[strategic_num] , map.strategic_y[strategic_num]);

  else if(pressedKey == C)
    initialize_canon(new_tower , map.strategic_x[strategic_num] , map.strategic_y[strategic_num]);

  else if(pressedKey == M)
    initialize_mage(new_tower , map.strategic_x[strategic_num] , map.strategic_y[strategic_num]);

  else if(pressedKey == I)
    initialize_icy(new_tower , map.strategic_x[strategic_num] , map.strategic_y[strategic_num]);

  if(map.money >= new_tower.cost) {
    map.towers.push_back(new_tower);
    map.money -= new_tower.cost;
  }
}

int convert_to_second(Time time) {
  int seconds = time.minute * SEC_PER_MIN + time.second;
  return seconds;
}

void show_towers(Map &map) {
  for(int tower_num = 0 ; tower_num < map.towers.size() ; tower_num ++){
    if(map.towers[tower_num].type == "archer")
      map.win -> draw_png(ARCHER_IMG_ADDRESS , map.towers[tower_num].x -ADJUST_X  ,
      map.towers[tower_num].y -ADJUST_Y , TOWER_SIZE , TOWER_SIZE);
    else if(map.towers[tower_num].type == "mage")
      map.win -> draw_png(MAGE_IMG_ADDRESS , map.towers[tower_num].x -ADJUST_X ,
      map.towers[tower_num].y -ADJUST_Y , TOWER_SIZE , TOWER_SIZE);
    else if(map.towers[tower_num].type == "canon")
      map.win -> draw_png(CANON_IMG_ADDRESS , map.towers[tower_num].x -ADJUST_X ,
      map.towers[tower_num].y -ADJUST_Y , TOWER_SIZE , TOWER_SIZE);
    else if(map.towers[tower_num].type == "icy")
      map.win -> draw_png(ICY_IMG_ADDRESS , map.towers[tower_num].x -ADJUST_X ,
      map.towers[tower_num].y -ADJUST_Y , TOWER_SIZE , TOWER_SIZE);
  }

}

void show_enemies(Map &map) {
 for(int enemy_num = 0 ; enemy_num < map.enemies.size(); enemy_num ++) {
    if(map.enemies[enemy_num].life > 0 && !map.enemies[enemy_num].arrived_deffence_point) {
       string image_address = ENEMY_FOLDER + map.enemies[enemy_num].type + "/" + map.enemies[enemy_num].direction + ".png";
       map.win -> draw_png(image_address , map.enemies[enemy_num].x -ENEMY_SIZE /2 ,
          map.enemies[enemy_num].y -ENEMY_SIZE /2 , ENEMY_SIZE , ENEMY_SIZE);
    }
 }
}

void move_enemies(Map & map) {
  for(int enemy_num = 0 ; enemy_num < map.enemies.size() ; enemy_num ++) {
     if(map.enemies[enemy_num].life > 0 && !map.enemies[enemy_num].arrived_deffence_point) {
     move_in_segment(map.enemies[enemy_num] , map );
     }
  }
}

void move_in_curves(Enemy &enemy , Map &map , float randomized_x , float randomized_y) {
  enemy.x = randomized_x;
  enemy.y = randomized_y;
  enemy.segment ++;
  turn_enemy(enemy , map.path_x[enemy.segment + 1] - enemy.x ,
     map.path_y[enemy.segment + 1] - enemy.y);
}

void move_in_lines(Enemy &enemy , Map &map , float randomized_x , float randomized_y) {
  float dx = randomized_x - enemy.x;
  float dy = randomized_y - enemy.y;
  float angle;
  if(dx != 0)
    angle = atan2(dy,dx);
  else if(dx == 0)
    angle = PI / 2;
  enemy.x = enemy.x + DELAY * 0.001 * enemy.velocity * cos(angle);
  enemy.y = enemy.y + DELAY * 0.001 * enemy.velocity * sin(angle);
}

void move_in_segment(Enemy &enemy , Map &map){
  if(enemy.arrived_deffence_point)
     return;
  if(enemy.segment == map.path_x.size()-1) {
    enemy.arrived_deffence_point = 1;
    map.life -= enemy.damage;
    return;
  }
  float random_angle = -PI + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ ( 2 * PI )));
  float randomized_x = map.path_x[enemy.segment + 1] + RADIUS * cos(random_angle);
  float randomized_y = map.path_y[enemy.segment + 1] + RADIUS * sin(random_angle);
  move_in_lines(enemy , map , randomized_x , randomized_y);
  if(distance(enemy.x , enemy.y , randomized_x , randomized_y) < enemy.velocity )
     move_in_curves(enemy , map , randomized_x , randomized_y);
}

float distance(float x0 , float y0 , float x1 , float y1) {

  return sqrt(pow(x1-x0 , 2) + pow(y1-y0 , 2));
}

void turn_dx_pos(Enemy &enemy , float dx ,float dy) {
  if(dy > 0){
    if(abs(dx) > dy)
       enemy.direction = "left";
    else
    if(abs(dx) < dy)
       enemy.direction = "front";
  }
  else{
  if(dy < 0)
    if(abs(dx) > abs(dy))
       enemy.direction = "left";
    else
    if(abs(dx) < abs(dy))
       enemy.direction = "back";
  }
}

void turn_dx_neg(Enemy &enemy , float dx ,float dy) {
  if(dy > 0){
    if(dx > dy)
      enemy.direction = "right";
    else
    if(dx < dy)
      enemy.direction = "front";
  }
  else{
  if(dy < 0)
    if(dx > abs(dy))
      enemy.direction = "right";
    else
    if(dx < abs(dy))
      enemy.direction = "back";
  }
}

void turn_enemy(Enemy &enemy , float dx ,float dy) {
  if(dx < 0){
    turn_dx_pos(enemy , dx , dy);
  }
  else
  if(dx > 0){
    turn_dx_neg(enemy , dx , dy);
  }
}

void towers_shoot(Map &map , int number_of_loops) {

  for(int tower_num = 0 ; tower_num < map.towers.size() ; tower_num ++)
    tower_shoot(map.towers[tower_num] , map , number_of_loops);

  for(int i = 0 ; i < map.towers.size() ; i++) {
   move_bullets(map.towers[i] , map );
   show_bullets(map.towers[i].bullets , map);
  }

}

void tower_shoot(Tower &tower , Map &map , int number_of_loops) {
  for(int target_num = 0 ; target_num < map.enemies.size() ; target_num++)
        if(map.enemies[target_num].life > 0 && !map.enemies[target_num].arrived_deffence_point) {
          if(distance(tower.x , tower.y , map.enemies[target_num].x , map.enemies[target_num].y) < TOWER_SHOOT_RANGE){
           tower.locked_enemy = &map.enemies[target_num];
           break;
          }
       }
  if(tower.locked_enemy != NULL)
    shoot_bullet(tower, map , number_of_loops);
}

void shoot_bullet(Tower &tower , Map &map , int number_of_loops) {
    if(((number_of_loops * DELAY) % tower.shoot_rate) == 0) {
      if(distance(tower.x , tower.y , tower.locked_enemy -> x , tower.locked_enemy -> y ) < TOWER_SHOOT_RANGE){
      Bullet bullet = { float(tower.x) , float(tower.y) , false};
      tower.bullets.push_back(bullet);
      //playsound();
    }
  }
}

void playsound() {
  system(SOUND_ADDRESS);
}

void individual_damage(int damage , Enemy *enemy , Tower tower) {
  if((enemy -> physical_armor && tower.physical_attack) || (enemy -> magical_armor && tower.magical_attack))
     enemy -> life  -= damage * 0.5;
  else
  enemy -> life  -= damage;
}

void group_damage(Tower &tower , vector<Enemy> &enemies) {
  for(int enemy_num = 0 ; enemy_num < enemies.size() ; enemy_num ++)
     if(distance(tower.locked_enemy -> x ,tower.locked_enemy -> y , enemies[enemy_num].x , enemies[enemy_num].y) <= 50)
       enemies[enemy_num].life -= tower.damage;
}

void make_damage(Enemy *enemy , Tower &tower ,Map &map) {
  if(tower.locked_enemy == NULL)
    return;
  if(tower.type == "archer" || tower.type == "mage") {
    individual_damage(tower.damage , enemy , tower);
  }
  else
  group_damage(tower , map.enemies);

  if(tower.locked_enemy -> life <= 0) {
    map.money += tower.locked_enemy -> killPoint;
    tower.locked_enemy = NULL;
  }
}

float calculate_angle(float dy , float dx ) {

  float angle;
  if(dx != 0)
    angle = atan2(dy,dx);
  else if(dx == 0)
    angle = PI / 2;
  return angle;
}

void increase( float &x , float &y , float dx , float dy) {

  x += dx;
  y += dy;
}

float calculate_movement(float dt , float velocity) {   //ms

  return dt/1000 * velocity;
}

void hit_bullet(Enemy *enemy , Bullet &bullet , Tower &tower , Map &map , int last_bullet_idx) {

  bullet.x = enemy -> x;
  bullet.y = enemy -> y;
  bullet.is_hit = true;
  make_damage(enemy , tower , map);
  if(enemy == NULL) {
    for(int bullet_num = last_bullet_idx + 1 ; bullet_num < tower.bullets.size() ; bullet_num ++)
      tower.bullets[bullet_num].is_hit = 1;
  }
}

void move_bullets(Tower &tower, Map &map) {

    for(int i =0 ; i < tower.bullets.size() ; i++) {
       if(tower.locked_enemy != NULL && !tower.bullets[i].is_hit) {
         int dx = tower.locked_enemy -> x - tower.bullets[i].x;
         int dy = tower.locked_enemy -> y - tower.bullets[i].y;
         float angle = calculate_angle(dy , dx);
         float movement_x = calculate_movement (DELAY , BULLET_VELOCITY * cos(angle));
         float movement_y = calculate_movement (DELAY , BULLET_VELOCITY * sin(angle));
         increase(tower.bullets[i].x , tower.bullets[i].y , movement_x , movement_y);

         if(distance(tower.bullets[i].x , tower.bullets[i].y , tower.locked_enemy -> x , tower.locked_enemy -> y) <  BULLET_VELOCITY /10.0)
            hit_bullet(tower.locked_enemy , tower.bullets[i] , tower , map , i);
      }
   }
 }

int total_enemies(Map map) {
  int num = 0;
    for(int wave_num = 0 ; wave_num < map.waves.size() ; wave_num ++) {
      for(int attack_num = 0 ; attack_num < map.waves[wave_num].attacks.size() ; attack_num++) {
        for(int attacker_num = 0 ; attacker_num < map.waves[wave_num].attacks[attack_num].attackers.size() ; attacker_num ++ )
          num += map.waves[wave_num].attacks[attack_num].attackers[attacker_num].number;
          }
        }
        return num;
      }

void show_bullets(vector<Bullet> bullets , Map &map) {
  for(int i = 0 ; i < bullets.size() ; i++) {
    if(!bullets[i].is_hit){
    map.win -> draw_png(BULLET_IMAGE_ADRESS , bullets[i].x -BULLET_SIZE / 2 ,
       bullets[i].y -BULLET_SIZE / 2 , BULLET_SIZE , BULLET_SIZE);
    }
  }
}

bool waves_finished(Map map) {

  if(map.enemies.size() != total_enemies(map))
    return false;
  for(int enemy_num = 0 ; enemy_num < map.enemies.size() ; enemy_num ++) {
    if(!map.enemies[enemy_num].arrived_deffence_point &&
       map.enemies[enemy_num].life > 0){
      return false;
    }
  }
  return true;
}

void show_end_text(Map &map) {
  if(map.life <= 0) {
     map.win -> show_text(END_LOOSE_TEXT , END_TEXT_X , END_TEXT_Y , RED , FONT_ADDRESS , FONT_SIZE);
     map.win -> update_screen();
     Delay(END_DELAY);
   }
  else if(waves_finished(map)) {
     map.win -> show_text(END_WIN_TEXT , END_TEXT_X , END_TEXT_Y , BLUE , FONT_ADDRESS , FONT_SIZE);
     map.win -> update_screen();
     Delay(END_DELAY);
   }
}
